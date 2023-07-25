#pragma once

#include <DownloadType.hpp>
#include <OutputFileType.hpp>
#include <curl_easy.h>

#include <fstream>
#include <functional>
#include <string>

namespace curl {

namespace CurlInterface {

extern int lowSpeedLimit;
extern int lowSpeedTime;

typedef std::function<void(curl_easy&)> ConfigurationFunction;
void addLowSpeedLimitToCurlEasy(curl_easy& easy, LONG const lowSpeedLimit, LONG const duration);

template <DownloadType downloadType>
void addToCurlEasy(curl_easy&) {
    static_assert(sizeof(DownloadType) > 0, "DownloadType has no implementation.");
}

template <DownloadType configType1, DownloadType configType2>
void addToCurlEasy(curl_easy& easy) {
    addToCurlEasy<configType1>(easy);
    addToCurlEasy<configType2>(easy);
}

template <DownloadType configType1, DownloadType configType2, DownloadType configType3>
void addToCurlEasy(curl_easy& easy) {
    addToCurlEasy<configType1>(easy);
    addToCurlEasy<configType2, configType3>(easy);
}

template <DownloadType configType1, DownloadType configType2, DownloadType configType3, DownloadType configType4>
void addToCurlEasy(curl_easy& easy) {
    addToCurlEasy<configType1>(easy);
    addToCurlEasy<configType2, configType3, configType4>(easy);
}

template <>
void addToCurlEasy<DownloadType::LowSpeedLimit>(curl_easy& easy);
template <>
void addToCurlEasy<DownloadType::MozillaFireFox>(curl_easy& easy);
template <>
void addToCurlEasy<DownloadType::PrintDownloadProgress>(curl_easy& easy);
template <>
void addToCurlEasy<DownloadType::Ssl>(curl_easy& easy);

void createOutputStream(
    std::unique_ptr<std::ofstream>& outputStream, OutputFileType outputFileType, std::string const& fileLocation);

bool download(std::string url, std::ofstream& outputFile, ConfigurationFunction additionalConfig);
bool downloadFile(
    std::string const& url, std::string const& fileLocation, OutputFileType outputFileType,
    ConfigurationFunction additionalConfig);
bool downloadFileUntilSuccessful(
    std::string const& url, std::string const& fileLocation, OutputFileType outputFileType,
    ConfigurationFunction additionalConfig);
bool downloadFileWithFiniteNumberOfTries(
    std::string const& url, std::string const& fileLocation, OutputFileType outputFileType,
    int const totalNumberOfTries, ConfigurationFunction additionalConfig);
inline void printDownloadErrorMessage(std::string const& errorMessage);

}  // namespace CurlInterface

}  // namespace curl
