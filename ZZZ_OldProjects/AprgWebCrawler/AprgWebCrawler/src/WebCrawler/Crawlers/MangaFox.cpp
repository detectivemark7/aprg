#include <Common/File/AlbaFileReader.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WebCrawler/CrawlHelpers/Downloaders.hpp>
#include <WebCrawler/Crawlers/OneDownloadPerPageCrawler.hpp>

#include <fstream>
#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace aprgWebCrawler::Downloaders;
using namespace std;

namespace aprgWebCrawler {

void OneDownloadPerPageCrawler::retrieveLinksForMangaFox(AlbaWebPathHandler const& webLinkPathHandler) {
    retrieveNextLinkAndImageLinkForMangaFox(webLinkPathHandler);
    AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
    imageWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
    m_localPathForCurrentFileToDownload = m_webCrawler.getDownloadDirectory() +
                                          webLinkPathHandler.getImmediateDirectoryName() + R"(\)" +
                                          imageWebPathHandler.getFile();
}

void OneDownloadPerPageCrawler::retrieveLinksForMangaFoxSaveInVolumeAndChapter(
    AlbaWebPathHandler const& webLinkPathHandler) {
    retrieveNextLinkAndImageLinkForMangaFox(webLinkPathHandler);
    AlbaWebPathHandler webPathForFolderName(webLinkPathHandler);
    string folderName(webPathForFolderName.getImmediateDirectoryName());
    webPathForFolderName.goUp();
    folderName = webPathForFolderName.getImmediateDirectoryName() + "_" + folderName;
    AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
    imageWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
    m_localPathForCurrentFileToDownload =
        m_webCrawler.getDownloadDirectory() + folderName + R"(\)" + imageWebPathHandler.getFile();
}

void OneDownloadPerPageCrawler::retrieveNextLinkAndImageLinkForMangaFox(AlbaWebPathHandler const& webLinkPathHandler) {
    AlbaLocalPathHandler downloadPathHandler(m_webCrawler.getDownloadDirectory() + R"(\temp.html)");
    downloadFileWithDefaultSettings(webLinkPathHandler, downloadPathHandler);
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if (!htmlFileStream.is_open()) {
        cout << "Cannot open html file.\n";
        cout << "File to read:" << downloadPathHandler.getFullPath() << "\n";
    } else {
        string nextPageLink;
        string nextChapterLink;
        string onClickNextPage;
        AlbaFileReader htmlFileReader(htmlFileStream);
        while (htmlFileReader.isNotFinished()) {
            string lineInHtmlFile(htmlFileReader.getLine());
            if (isStringFoundInsideTheOtherStringCaseSensitive(
                    lineInHtmlFile, R"***(onclick="return enlarge()">)***")) {
                string nextLineInHtmlFile(htmlFileReader.getLine());
                if (isStringFoundInsideTheOtherStringCaseSensitive(nextLineInHtmlFile, R"(<img src=")")) {
                    m_linkForCurrentFileToDownload =
                        getStringInBetweenTwoStrings(nextLineInHtmlFile, R"(img src=")", R"(")");
                }
            } else if (isStringFoundInsideTheOtherStringCaseSensitive(
                           lineInHtmlFile, R"(class="btn next_page"><span></span>next page</a>)")) {
                nextPageLink = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
                onClickNextPage = getStringInBetweenTwoStrings(lineInHtmlFile, R"(onclick=")", R"(")");
            } else if (isStringFoundInsideTheOtherStringCaseSensitive(
                           lineInHtmlFile, R"(<p><span>Next Chapter:</span> <a href=")")) {
                nextChapterLink = getStringInBetweenTwoStrings(lineInHtmlFile, R"(<a href=")", R"(")");
            }
        }
        if ("next_chapter()" == onClickNextPage || "javascript:void(0);" == nextPageLink) {
            cout << "New chapter. NextChapterLink :" << nextChapterLink << "\n";
            m_linkForNextHtml = nextChapterLink;
        } else {
            m_linkForNextHtml = nextPageLink;
        }
    }
}

}  // namespace aprgWebCrawler
