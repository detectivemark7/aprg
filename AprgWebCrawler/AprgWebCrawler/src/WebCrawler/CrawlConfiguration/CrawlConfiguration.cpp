#include "CrawlConfiguration.hpp"

namespace aprgWebCrawler {

CrawlConfiguration::CrawlConfiguration(CrawlMode const mode) {
    switch (mode) {
        case CrawlMode::ChiaAnime:
            m_isFileToBeDownloadUntilSuccessful = false;
            m_numberOfRetries = 10;
            m_minimumFileSize = 1000000;
            break;
        case CrawlMode::Gehen:
            m_isFileToBeDownloadUntilSuccessful = false;
            m_numberOfRetries = 10;
            m_minimumFileSize = 0;
            m_lowSpeedLimitOptional.emplace();
            m_lowSpeedLimitOptional->m_lowSpeedLimit = 1000;
            m_lowSpeedLimitOptional->m_lowSpeedTime = 10;
            break;
        case CrawlMode::DoujinMoe:
        case CrawlMode::GuroManga:
        case CrawlMode::HBrowse:
        case CrawlMode::Mangafox:
        case CrawlMode::MangafoxWithVolume:
        case CrawlMode::Mangahere:
        case CrawlMode::MangaPark:
        case CrawlMode::Y8:
            m_isFileToBeDownloadUntilSuccessful = true;
            m_numberOfRetries = 0;
            m_minimumFileSize = 1000;
            break;
        case CrawlMode::H2Read:
            m_isFileToBeDownloadUntilSuccessful = false;
            m_numberOfRetries = 0;
            m_minimumFileSize = 1000;
            break;
        case CrawlMode::Youtube:
            m_isFileToBeDownloadUntilSuccessful = true;
            m_numberOfRetries = 0;
            m_minimumFileSize = 1000000;
            break;
        case CrawlMode::Empty:
        case CrawlMode::Unknown:
            break;
    }
}

bool CrawlConfiguration::isFileToBeDownloadUntilSuccessful() const { return m_isFileToBeDownloadUntilSuccessful; }

int CrawlConfiguration::getNumberOfRetries() const { return m_numberOfRetries; }

double CrawlConfiguration::getMinimumFileSize() const { return m_minimumFileSize; }

DownloadLowSpeedLimitConfigurationOptional CrawlConfiguration::getDownloadLowSpeedLimitConfigurationOptional() const {
    return m_lowSpeedLimitOptional;
}

}  // namespace aprgWebCrawler
