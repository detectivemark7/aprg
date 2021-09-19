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

namespace aprgWebCrawler
{

void OneDownloadPerPageCrawler::retrieveLinksForH2Read(AlbaWebPathHandler const& webLinkPathHandler)
{
    AlbaLocalPathHandler downloadPathHandler(m_webCrawler.getDownloadDirectory() + R"(\temp.html)");
    downloadFileWithDefaultSettings(webLinkPathHandler, downloadPathHandler);
    ifstream htmlFileStream(downloadPathHandler.getFullPath());
    if(!htmlFileStream.is_open())
    {
        cout << "Cannot open html file.\n";
        cout << "File to read:" << downloadPathHandler.getFullPath() << "\n";
    }
    else
    {
        AlbaFileReader htmlFileReader(htmlFileStream);
        unsigned int index(0);
        while (htmlFileReader.isNotFinished())
        {
            string lineInHtmlFile(htmlFileReader.getLine());
            if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"(<img id="arf-reader")"))
            {
                m_linkForCurrentFileToDownload = getStringInBetweenTwoStrings(lineInHtmlFile, R"( src=")", R"(")");
            }
            else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"('index' : )"))
            {
                index = convertStringToNumber<unsigned int>(getStringInBetweenTwoStrings(lineInHtmlFile, R"('index' : )", R"(,)"));
            }
            else if(isStringFoundInsideTheOtherStringCaseSensitive(lineInHtmlFile, R"('currentURL' : ')"))
            {
                index++;
                m_linkForNextHtml = getStringInBetweenTwoStrings(lineInHtmlFile, R"('currentURL' : ')", R"(',)")+convertToString(index);
            }
        }
        AlbaWebPathHandler imageWebPathHandler(webLinkPathHandler);
        imageWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
        AlbaWebPathHandler chapterWebPathHandler(webLinkPathHandler);
        m_localPathForCurrentFileToDownload = m_webCrawler.getDownloadDirectory() + R"(chapter)" + chapterWebPathHandler.getImmediateDirectoryName() + R"(\)" + imageWebPathHandler.getFile();
    }
}

}
