#include <Common/File/AlbaFileReader.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <WebCrawler/CrawlConfiguration/CrawlConfiguration.hpp>
#include <WebCrawler/WebCrawler.hpp>

#include <iostream>

using namespace alba;
using namespace alba::stringHelper;
using namespace std;

/*
namespace aprgWebCrawler
{

void WebCrawler::crawlOneHtmlAndOneFileToDownload()
{
    for(string & webLink : m_webLinks)
    {
        crawlOneHtmlAndOneFileToDownload(webLink);
    }
}

void WebCrawler::crawlOneHtmlAndOneFileToDownload(string& webLink)
{
    cout << "WebCrawler::crawlPerHtmlAndDownloadImage\n";

    CrawlConfiguration configuration(m_mode);
    while(!isCrawlStateInvalid())
    {
        AlbaWebPathHandler currentWebLinkPathHandler(webLink);
        AlbaLocalPathHandler downloadPathHandler(m_downloadDirectoryPathHandler.getDirectory() + R"(\temp.html)");
        downloadFileAsText(currentWebLinkPathHandler, downloadPathHandler);
        LinksForHtmlAndFileToDownload links;
        if(links.isInvalid())
        {
            cout << "Links are invalid.\n";
            links.printLinks();
            saveStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        AlbaWebPathHandler fileToDownloadWebPathHandler(currentWebLinkPathHandler);
        fileToDownloadWebPathHandler.gotoLink(links.linkForCurrentFileToDownload);
        if(!fileToDownloadWebPathHandler.isFile())
        {
            cout << "Link is not to a file.\n";
            cout << "Link of file to Download: " << fileToDownloadWebPathHandler.getFullPath() << "\n";
            saveStateToMemoryCard(CrawlState::LinksAreInvalid);
            break;
        }
        downloadPathHandler.input(links.localPathForCurrentFileToDownload);
        downloadPathHandler.createDirectoriesForNonExisitingDirectories();
        downloadBinaryFile(fileToDownloadWebPathHandler, downloadPathHandler);
        if(downloadPathHandler.getFileSizeEstimate() < configuration.getMinimumFileSize())
        {
            cout << "Download file size is less than "<<configuration.getMinimumFileSize()<<". FileSize = "<< downloadPathHandler.getFileSizeEstimate() <<" Invalid file. Retrying from the start\n";
            saveStateToMemoryCard(CrawlState::DownloadedFileSizeIsLessThanExpected);
            continue;
        }
        if(links.linkForNextHtml.empty())
        {
            cout << "Terminating the because next web link is empty.\n";
            saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
            break;
        }
        AlbaWebPathHandler nextWebPathHandler(currentWebLinkPathHandler);
        nextWebPathHandler.gotoLink(links.linkForNextHtml);
        if(currentWebLinkPathHandler.getFullPath() == nextWebPathHandler.getFullPath())
        {
            cout << "Crawler stop because the next web link is the same as previous link.\n";
            saveStateToMemoryCard(CrawlState::NextLinkIsInvalid);
            break;
        }
        webLink = nextWebPathHandler.getFullPath();
        setCrawlState(CrawlState::Active);
        saveMemoryCard();
    }
}

}*/
