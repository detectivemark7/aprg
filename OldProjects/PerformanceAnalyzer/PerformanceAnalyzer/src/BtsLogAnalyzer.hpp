#pragma once

#include <Common/Container/AlbaOptional.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Statistics/DataCollection.hpp>
#include <UserIdentifiers.hpp>
#include <WcdmaToolsBackend/BtsLogPrint.hpp>
#include <WcdmaToolsBackend/BtsLogTime.hpp>

#include <fstream>
#include <map>
#include <string>

namespace alba
{

class BtsLogAnalyzer
{

public:
    enum class LogType
    {
        RlSetup,
        RlDeletion
    };
    struct PrintsAvailable
    {
        PrintsAvailable();
        bool hasBB_2_RL_SETUP_REQ_MSG;
        bool hasBB_2_RL_SETUP_ACK_MSG;
        bool hasTC_TRANSPORT_BEARER_REGISTER_MSG;
        bool hasTC_TRANSPORT_BEARER_REGISTER_RESP_MSG;
    };
    struct DspData
    {
        DspData()
            : boardId(0)
            , cpuId(0)
            , lcgId(0)
            , availableUlCEs(0)
            , availableDlCEs(0)
            , rakeState(0)
            , rachHand(0)
            , rakeLoad(0)
            , hsupaCFs(0)
            , hsRachCFs(0)
            , hsupaUsers(0)
            , nbrOfEnhHsupaUsers(0)
            , dchUsers(0)
        {}
        unsigned int boardId;
        unsigned int cpuId;
        unsigned int lcgId;
        unsigned int availableUlCEs;
        unsigned int availableDlCEs;
        unsigned int rakeState;
        unsigned int rachHand;
        unsigned int rakeLoad;
        unsigned int hsupaCFs;
        unsigned int hsRachCFs;
        unsigned int hsupaUsers;
        unsigned int nbrOfEnhHsupaUsers;
        unsigned int dchUsers;
    };
    using LogTime = alba::AlbaOptional<wcdmaToolsBackend::BtsLogTime>;
    using LogTimePair = std::pair<LogTime, LogTime>;
    using LogTimePairs = std::map<alba::UserIdentifiers, LogTimePair>;
    using UserIdentifierToPrintsAvailablePair = std::pair<alba::UserIdentifiers, PrintsAvailable>;
    using PrintsAvailableMap = std::map<alba::UserIdentifiers, PrintsAvailable>;
    using DspDataPair = std::pair<unsigned int, DspData>;
    using DspDataMap = std::map<unsigned int, DspData>;


    BtsLogAnalyzer();
    void clear();
    void processFileWithSortedPrints(std::string const& pathOfBtsLog);
    void printAllCollectedData() const;

private:
    void initializeMessageQueueingTimeFileStream();
    void initializeRlSetupTimeFileStream();
    void initializeRlDeletionTimeFileStream();
    void initializeRlSetupPerSecondFileStream();
    void saveDspCapacityInformationInGrm(std::string const& lineInLogs);
    void saveDspCapacityInformationInGrmOfOneDsp(std::string const& dspCapacityOfOneDsp, unsigned int const boardId, wcdmaToolsBackend::BtsLogPrint const& logPrint);
    void saveDspCapacityInformationInLrmForR3(std::string const& lineInLogs);
    void saveDspCapacityInformationInLrmOfOneDspForR3(std::string const& dspCapacityOfOneDsp, unsigned int const boardId, wcdmaToolsBackend::BtsLogPrint const& logPrint);
    void saveDspCapacityInformationInLrmForR2(std::string const& lineInLogs);
    void saveDspCapacityInformationInLrmOfOneDspForR2(std::string const& dspCapacityOfOneDsp, unsigned int const boardId, wcdmaToolsBackend::BtsLogPrint const& logPrint);
    void initializeDataDumpOfAllDspsForR3();
    void initializeDataDumpOfAllDspsForR2();
    void initializeDataDumpOfOneDsp(std::string const& dspAddress);
    void initializeTotalUsersAndCfsDump();
    void initializeSaveAllUsersAndCfsDump();
    void saveDataDumpOfOneDsp(std::string const& fileName, DspData const& dspData, wcdmaToolsBackend::BtsLogPrint const& logPrint);
    void saveTotalUsersAndCfs(wcdmaToolsBackend::BtsLogPrint const& logPrint);
    void saveAllUsersAndCfs(wcdmaToolsBackend::BtsLogPrint const& logPrint);
    void saveDspInformation(unsigned int const dspAddress, DspData const& dspData);
    void saveMaxDspInformation(DspData const& dspData);
    void saveQueueingTime(std::string const& lineInLogs);
    void saveRlSetupPerSecond(std::string const& lineInLogs);
    void saveRlhSetupTime(std::string const& lineInLogs, LogTimePairs& rlSetupLogTimePairs);
    void saveRlhDeletionTime(std::string const& lineInLogs, LogTimePairs& rlDeletionLogTimePairs);
    void saveAdditionalPrintsRlSetup(std::string const& lineInLogs, LogTimePairs& rlSetupLogTimePairs);
    void setFirstLogTimeInPair(std::string const& lineInLogs, UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs) const;
    void setSecondLogTimeInPair(std::string const& lineInLogs, UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs) const;
    void computeRlSetupLatencyAndUpdateIfLogTimePairIsValid(UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs);
    void computeRLDeletionLatencyAndUpdateIfLogTimePairIsValid(UserIdentifiers const& userIdentifiers, LogTimePairs& logTimePairs);
    void saveMessageQueueingTimeToCsvFile(std::string const& lineInLogs, unsigned int const messageQueueingTime);
    void saveUserIndentifierAndLatencyToCsvFile(UserIdentifiers const& userIdentifiers, double const latencyInMicroseconds, std::ofstream& csvFileStream) const;
    void savePrintsAvailableToCsvFile(UserIdentifiers const& userIdentifiers, std::ofstream& csvFileStream);
    void setLogTimeIfNeeded(std::string const& lineInLogs, LogTime& logTime) const;
    double getTotalMicroseconds(LogTimePair const& logTimePairOfTheUser) const;
    double getTotalMicroseconds(wcdmaToolsBackend::BtsLogTime const& btsLogTime) const;
    DataCollection<double> m_messageQueueingTime;
    DataCollection<double> m_rlhRlSetupLatency;
    DataCollection<double> m_rlhRlDeletionLatency;
    AlbaLocalPathHandler m_btsLogPathHandler;
    DspData m_maxDspData;
    DspDataMap m_dspDataMap;
    PrintsAvailableMap m_rlSetupPrintsAvailableMap;
    AlbaOptional<std::ofstream> messageQueueingTimeFileStreamOptional;
    AlbaOptional<std::ofstream> rlSetupTimeFileStreamOptional;
    AlbaOptional<std::ofstream> rlDeletionTimeFileStreamOptional;
    AlbaOptional<std::ofstream> rlSetupPerSecondFileStreamOptional;

};

}
