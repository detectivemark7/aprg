#include <Common/File/AlbaFileReader.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WebCrawler/CrawlHelpers/Downloaders.hpp>
#include <WebCrawler/Crawlers/OneDownloadPerPageCrawler.hpp>

#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace aprgWebCrawler::Downloaders;
using namespace std;

namespace aprgWebCrawler {

OneDownloadPerPageCrawler::OneDownloadPerPageCrawler(WebCrawler& webCrawler)
    : m_webCrawler(webCrawler), m_configuration(webCrawler.getCrawlMode()), m_mode(webCrawler.getCrawlMode()) {}

void OneDownloadPerPageCrawler::crawl() {
    cout << "OneDownloadPerPageCrawler::crawl\n";
    for (unsigned int webLinkIndex = 0; webLinkIndex < m_webCrawler.getNumberOfWebLinks(); webLinkIndex++) {
        crawl(webLinkIndex);
    }
}

void OneDownloadPerPageCrawler::crawl(unsigned int const webLinkIndex) {
    while (!m_webCrawler.isOnInvalidCrawlState()) {
        m_webCrawler.saveStateToMemoryCard(CrawlState::Active);
        AlbaWebPathHandler webLinkPathHandler(m_webCrawler.getWebLinkAtIndex(webLinkIndex));
        retrieveLinks(webLinkPathHandler);
        if (checkLinks()) {
            downloadFile(webLinkPathHandler);
        }
        if (m_webCrawler.isOnCrawlStatesWhichRetryIsNeeded()) {
            continue;
        }
        if (m_webCrawler.isOnCurrentDownloadFinishedCrawlState()) {
            gotoNextLink(webLinkPathHandler, webLinkIndex);
        }
    }
}

void OneDownloadPerPageCrawler::retrieveLinks(AlbaWebPathHandler const& webLinkPathHandler) {
    clearLinks();
    switch (m_mode) {
        case CrawlMode::Gehen:
            retrieveLinksForGehen(webLinkPathHandler);
            break;
        case CrawlMode::GuroManga:
            retrieveLinksForGuroManga(webLinkPathHandler);
            break;
        case CrawlMode::HBrowse:
            retrieveLinksForHBrowse(webLinkPathHandler);
            break;
        case CrawlMode::H2Read:
            retrieveLinksForH2Read(webLinkPathHandler);
            break;
        case CrawlMode::Mangafox:
            retrieveLinksForMangaFox(webLinkPathHandler);
            break;
        case CrawlMode::MangafoxWithVolume:
            retrieveLinksForMangaFoxSaveInVolumeAndChapter(webLinkPathHandler);
            break;
        case CrawlMode::Mangahere:
            retrieveLinksForMangaHere(webLinkPathHandler);
            break;
        case CrawlMode::MangaPark:
            retrieveLinksForMangaPark(webLinkPathHandler);
            break;
        case CrawlMode::ChiaAnime:
        case CrawlMode::DoujinMoe:
        case CrawlMode::Youtube:
        case CrawlMode::Y8:
            cout << "OneDownloadPerPageCrawler::retrieveLinks | Mode is different\n";
            break;
        case CrawlMode::Empty:
        case CrawlMode::Unknown:
            cout << "OneDownloadPerPageCrawler::retrieveLinks | Mode is not set\n";
            break;
    }
}

bool OneDownloadPerPageCrawler::checkLinks() {
    bool result(true);
    if (areLinksInvalid()) {
        cout << "Links are invalid.\n";
        printLinks();
        m_webCrawler.saveStateToMemoryCard(CrawlState::LinksAreInvalid);
        result = false;
    }
    return result;
}

void OneDownloadPerPageCrawler::downloadFile(AlbaWebPathHandler const& webLinkPathHandler) {
    AlbaWebPathHandler fileToDownloadWebPathHandler(webLinkPathHandler);
    fileToDownloadWebPathHandler.gotoLink(m_linkForCurrentFileToDownload);
    if (!fileToDownloadWebPathHandler.isFile()) {
        cout << "Link is not to a file.\n";
        cout << "Link of file to Download: " << fileToDownloadWebPathHandler.getFullPath() << "\n";
        m_webCrawler.saveStateToMemoryCard(CrawlState::LinksAreInvalid);
    } else {
        AlbaLocalPathHandler downloadPathHandler(m_localPathForCurrentFileToDownload);
        downloadPathHandler.createDirectoriesForNonExisitingDirectories();
        bool isSuccessful =
            downloadBinaryFile(fileToDownloadWebPathHandler, downloadPathHandler, m_webCrawler.getCrawlMode());
        if (!isSuccessful) {
            m_webCrawler.saveImportantLink(fileToDownloadWebPathHandler.getFullPath());
        } else if (downloadPathHandler.getFileSizeEstimate() < m_configuration.getMinimumFileSize()) {
            cout << "Download file size is less than " << m_configuration.getMinimumFileSize()
                 << ". FileSize = " << downloadPathHandler.getFileSizeEstimate()
                 << " Invalid file. Retrying from the start\n";
            m_webCrawler.saveStateToMemoryCard(CrawlState::DownloadedFileSizeIsLessThanExpected);
        } else {
            m_webCrawler.saveStateToMemoryCard(CrawlState::CurrentDownloadIsFinished);
        }
    }
}

void OneDownloadPerPageCrawler::gotoNextLink(
    AlbaWebPathHandler const& webLinkPathHandler, unsigned int const webLinkIndex) {
    if (m_linkForNextHtml.empty()) {
        cout << "Terminating the because next web link is empty.\n";
        m_webCrawler.saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
    } else {
        AlbaWebPathHandler nextWebPathHandler(webLinkPathHandler);
        nextWebPathHandler.gotoLink(m_linkForNextHtml);
        if (webLinkPathHandler.getFullPath() == nextWebPathHandler.getFullPath()) {
            cout << "Crawler stop because the next web link is the same as previous link.\n";
            m_webCrawler.saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
        } else {
            m_webCrawler.modifyWebLink(nextWebPathHandler.getFullPath(), webLinkIndex);
        }
    }
}

void OneDownloadPerPageCrawler::clearLinks() {
    m_linkForNextHtml.clear();
    m_linkForCurrentFileToDownload.clear();
    m_localPathForCurrentFileToDownload.clear();
}

bool OneDownloadPerPageCrawler::areLinksInvalid() const {
    return m_linkForCurrentFileToDownload.empty() || m_localPathForCurrentFileToDownload.empty();
}

void OneDownloadPerPageCrawler::printLinks() const {
    cout << "LinkForNextHtml : " << m_linkForNextHtml << "\n";
    cout << "LinkForCurrentFileToDownload : " << m_linkForCurrentFileToDownload << "\n";
    cout << "LocalPathForCurrentFileToDownload : " << m_localPathForCurrentFileToDownload << "\n";
}

}  // namespace aprgWebCrawler
