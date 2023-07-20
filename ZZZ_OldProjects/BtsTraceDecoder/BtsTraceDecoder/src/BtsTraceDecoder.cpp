#include "BtsTraceDecoder.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>

using namespace std;
using namespace alba::stringHelper;

namespace alba {

BtsTraceDecoder::BtsTraceDecoder() {}

void BtsTraceDecoder::saveSymbolTableFromObjdump(std::string const& symbolTableFilePath) {
    saveSymbolTable(symbolTableFilePath, SymbolTableFileType::SymbolTableFromObjdump);
}

void BtsTraceDecoder::saveSymbolTableFromMappedFile(std::string const& symbolTableFilePath) {
    saveSymbolTable(symbolTableFilePath, SymbolTableFileType::MappedFile);
}

void BtsTraceDecoder::processInputTraceFile(std::string const& inputTraceFilePath) {
    ifstream traceFile(AlbaLocalPathHandler(inputTraceFilePath).getFullPath());
    if (traceFile.is_open()) {
        AlbaFileReader traceFileReader(traceFile);
        while (traceFileReader.isNotFinished()) {
            string lineInTraceFile(traceFileReader.getLine());
            unsigned int traceAddressValue =
                convertHexStringToNumber<unsigned int>(getStringInBetweenTwoStrings(lineInTraceFile, "[", "]"));
            if (traceAddressValue != 0) {
                cout << "TraceAddressValue: [0x" << std::hex << traceAddressValue << "] NearestSymbol: ["
                     << getNearestLowerSymbol(static_cast<int>(traceAddressValue)) << "]\n";
            }
        }
    }
}

std::string BtsTraceDecoder::getNearestLowerSymbol(int const address, int const offset) {
    string symbol;
    if (!m_symbolMap.empty()) {
        int addressWithOffset(address + offset);
        BtsTraceDecoder::SymbolMapType::iterator symbolIterator = m_symbolMap.lower_bound(addressWithOffset);
        if (static_cast<int>(symbolIterator->first) <= addressWithOffset) {
            symbol = symbolIterator->second;
        } else {
            if (symbolIterator != m_symbolMap.begin()) {
                --symbolIterator;
                symbol = symbolIterator->second;
            }
        }
    }
    return symbol;
}

void BtsTraceDecoder::saveSymbolTable(std::string const& symbolTableFilePath, SymbolTableFileType const filetype) {
    ifstream symbolTableFileStream(AlbaLocalPathHandler(symbolTableFilePath).getFullPath());
    if (symbolTableFileStream.is_open()) {
        cout << "Symbol table file is opened\n";
        AlbaFileReader symbolTableFileReader(symbolTableFileStream);
        while (symbolTableFileReader.isNotFinished()) {
            string lineInFile(symbolTableFileReader.getLineAndIgnoreWhiteSpaces());
            saveLineInSymbolMapIfValid(getAddressFromLineInFile(lineInFile, filetype), lineInFile);
        }
    } else {
        cout << "Symbol table file is not opened\n";
    }
}

int BtsTraceDecoder::getAddressFromLineInFile(string const& lineInFile, SymbolTableFileType const filetype) const {
    int address = 0;
    if (filetype == SymbolTableFileType::SymbolTableFromObjdump) {
        address = convertHexStringToNumber<int>(getStringBeforeThisString(lineInFile, " "));
    } else if (filetype == SymbolTableFileType::MappedFile) {
        address = convertHexStringToNumber<int>(getStringInBetweenTwoStrings(lineInFile, "0x", " "));
    }
    return address;
}

void BtsTraceDecoder::saveLineInSymbolMapIfValid(int const address, std::string const& lineInFile) {
    if (address != 0) {
        m_symbolMap.emplace(address, lineInFile);
    }
}

}  // namespace alba
