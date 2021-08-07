#pragma once

#include <Common/Container/AlbaOptional.hpp>

#include <windows.h>

#include <fstream>
#include <mutex>
#include <string>

namespace alba
{

namespace chess
{

class ChessEngineHandler
{
public:
    enum class LogType
    {
        FromEngine,
        ToEngine,
        HandlerStatus
    };
    using ProcessAStringFunction = std::function<void(std::string const&)> ;

    ChessEngineHandler(std::string const& enginePath);
    ~ChessEngineHandler();

    void reset();

    void sendStringToEngine(std::string const& stringToEngine);
    void processStringFromEngine(std::string const& stringFromEngine);
    void startMonitoringEngineOutput();

    void setLogFile(std::string const& logFilePath);
    void setAdditionalStepsInProcessingAStringFromEngine(ProcessAStringFunction const& additionalSteps);

private:
    void initializeEngine();
    void shutdownEngine();
    void log(LogType const logtype, std::string const& logString);
    std::string getLogHeader(LogType const logtype) const;
    std::string m_enginePath;
    std::mutex m_readMutex;
    STARTUPINFO m_startupInfo;
    PROCESS_INFORMATION m_processInfo;
    HANDLE m_engineMonitoringThread;
    DWORD m_threadId;
    HANDLE m_inputStreamOnEngineThread, m_outputStreamOnEngineThread;
    HANDLE m_inputStreamOnHandler, m_outputStreamOnHandler;
    AlbaOptional<std::ofstream> m_logFileStreamOptional;
    AlbaOptional<ProcessAStringFunction> m_additionalStepsInProcessingAStringFromEngine;
};

}

}
