#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

#include <iomanip>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace alba::stringHelper {

using strings = std::vector<std::string>;
using StringViews = std::vector<std::string_view>;
using StringPair = std::pair<std::string, std::string>;
using StringPairs = std::vector<StringPair>;

constexpr auto WHITESPACE_STRING = " \t\n\r";

inline bool isWhiteSpace(char const c) { return (' ' == c || '\t' == c || '\n' == c || '\r' == c); }

inline bool isNewline(char const c) { return ('\n' == c || '\r' == c); }

inline bool isNotNpos(int const index) {
    // ToDo: is npos really unsigned? if its then convert to unsigned, do this to all npos functions
    return static_cast<int>(std::string::npos) != index;
}

inline bool isNpos(int const index) { return static_cast<int>(std::string::npos) == index; }

inline bool isValidIndex(int const index, int const stringLength) {
    return isNotNpos(index) && 0 <= index && stringLength >= index;
}

inline bool isCapitalLetter(char const c) { return ('A' <= c && 'Z' >= c); }

inline bool isLetter(char const c) { return ('a' <= c && 'z' >= c) || ('A' <= c && 'Z' >= c); }

inline bool isNumber(char const c) { return ('0' <= c && '9' >= c); }

inline bool isUnderscore(char const c) { return '_' == c; }

inline bool isHexDigit(char const c) { return isNumber(c) || ('a' <= c && 'f' >= c) || ('A' <= c && 'F' >= c); }

inline bool isLetterOrNumber(char const c) { return isLetter(c) || isNumber(c); }

inline bool isLetterOrNumberOrUnderscore(char const c) { return isLetter(c) || isNumber(c) || isUnderscore(c); }

inline bool isSlashCharacter(char const c) { return ('\\' == c || '/' == c); }

inline bool isDisplayableCharacter(char const c) { return (' ' <= c && '~' >= c); }

inline bool isNotEmptyLine(std::string_view mainString) {
    return isNotNpos(static_cast<int>(mainString.find_first_not_of(WHITESPACE_STRING)));
}

inline bool isPeriodOrDoublePeriod(std::string_view mainString) { return ("." == mainString) || (".." == mainString); }

inline bool isLessThanStringLength(std::string_view mainString, int const index) {
    return (index < static_cast<int>(mainString.length()));
}

size_t generateUniqueId(std::string_view mainString);
size_t getLevenshteinDistance(std::string_view otherString, std::string_view basisString);
size_t getHammingDistance(std::string_view string1, std::string_view string2);
size_t getNumberOfSubStrings(std::string_view mainString);
size_t getNumberOfSubsequences(std::string_view mainString);
int getRotationValue(std::string_view mainString, std::string_view rotation);
int getPeriodValue(std::string_view mainString, std::string_view period);

bool isNumber(std::string_view mainString);
bool isWhiteSpace(std::string_view mainString);
bool isNewline(std::string_view mainString);
bool isIdentifier(std::string_view mainString);
bool isOneWord(std::string_view mainString);
bool isPalindrome(std::string_view mainString);
bool isSubstring(std::string_view mainString, std::string_view subString);
bool isSubsequence(std::string_view mainString, std::string_view subsequence);
bool isPrefix(std::string_view mainString, std::string_view prefix);
bool isSuffix(std::string_view mainString, std::string_view suffix);
bool isRotation(std::string_view mainString, std::string_view rotation);
bool isPeriod(std::string_view mainString, std::string_view period);
bool isBorder(std::string_view mainString, std::string_view border);
bool isEqualNotCaseSensitive(std::string_view mainString, std::string_view string2);
bool isEqualWithLowestCommonLength(std::string_view string1, std::string_view string2);
bool isStringFoundInsideTheOtherStringCaseSensitive(std::string_view mainString, std::string_view string2);
bool isStringFoundInsideTheOtherStringNotCaseSensitive(std::string_view mainString, std::string_view string2);
bool isWildcardMatch(
    std::string_view mainString, std::string_view wildcard, size_t const mainStringIndex = 0,
    size_t const wildcardIndex = 0);

// String processing

std::string getStringWithCapitalLetters(std::string_view mainString);
std::string getStringWithFirstNonWhiteSpaceCharacterToCapital(std::string_view mainString);
std::string getStringWithLowerCaseLetters(std::string_view mainString);
std::string getStringWithUrlDecodedString(std::string_view mainString);
std::string getStringThatContainsWhiteSpaceIndention(std::string_view mainString);
std::string getStringWithoutStartingAndTrailingCharacters(std::string_view mainString, std::string_view characters);
std::string getStringWithoutStartingAndTrailingWhiteSpace(std::string_view mainString);
std::string getStringWithoutWhiteSpace(std::string_view mainString);
std::string getStringWithoutRedundantWhiteSpace(std::string_view mainString);
std::string getStringWithoutQuotations(std::string_view mainString);
std::string getStringWithoutCharAtTheStartAndEnd(std::string_view mainString, char const char1);
std::string getStringWithoutCharAtTheStart(std::string_view mainString, char const char1);
std::string getStringWithoutCharAtTheEnd(std::string_view mainString, char const char1);
std::string getStringWithoutOpeningClosingOperators(
    std::string_view mainString, char const openingOperator, char const closingOperator);
std::string getLongestCommonPrefix(std::string_view first, std::string_view second);
void copyBeforeStringAndAfterString(
    std::string_view mainString, std::string_view stringToSearch, std::string& beforeString, std::string& afterString,
    size_t const indexToStartTheSearch = 0);
std::string getStringBeforeThisString(
    std::string_view mainString, std::string_view stringToSearch, size_t const indexToStart = 0);
std::string getStringAfterThisString(
    std::string_view mainString, std::string_view stringToSearch, size_t const indexToStart = 0);
std::string getStringInBetweenTwoStrings(
    std::string_view mainString, std::string_view firstString, std::string_view secondString,
    size_t const indexToStart = 0);
std::string getStringBeforeThisCharacters(
    std::string_view mainString, std::string_view characters, size_t const indexToStart = 0);
std::string getStringAndReplaceNonAlphanumericCharactersToUnderScore(std::string_view path);
std::string getStringByRepeatingUntilDesiredLength(std::string_view stringToRepeat, size_t desiredLength);
std::string getNumberAfterThisString(std::string_view mainString, std::string_view stringToSearch);
std::string getHexNumberAfterThisString(std::string_view mainString, std::string_view stringToSearch);
std::string getHexEquivalentOfCharacters(std::string_view stringToCheck);

// Utilities

std::string constructFileLocator(std::string_view file, int const lineNumber);
std::string getRandomAlphaNumericString(size_t const length);
strings getArgumentsToStringInMain(int const argc, char const* const argv[]);

// Find and replace

bool transformReplaceStringIfFound(std::string& mainString, std::string_view toReplace, std::string_view replaceWith);

// Split and combine

enum class SplitStringType { WithDelimeters, WithoutDelimeters };
template <SplitStringType splitStringType>
void splitToStrings(strings& listOfStrings, std::string_view mainString, std::string_view delimiters);
std::string combineStrings(strings const& strings, std::string_view delimiters);
void splitLinesToAchieveTargetLength(strings& listOfStrings, std::string_view mainString, size_t const targetLength);
void splitToStringsUsingASeriesOfDelimeters(
    strings& listOfStrings, std::string_view mainString, strings const& seriesOfDelimiters);

// basic_string variants
template <typename StringType>
constexpr bool isBasicStringVariant() {
    return typeHelper::areSameTypes<StringType, std::string_view>() ||
           typeHelper::areSameTypes<StringType, std::string>() ||
           typeHelper::areSameTypes<StringType, std::wstring>() ||
           typeHelper::areSameTypes<StringType, std::u16string>() ||
           typeHelper::areSameTypes<StringType, std::u32string>();
}

// basic_string variants
template <typename InputStringType, typename OutputStringType>
OutputStringType convertToAnotherBasicStringVariant(InputStringType const& inputString) {
    static_assert(isBasicStringVariant<InputStringType>(), "Input should be a basic string variant.");
    static_assert(isBasicStringVariant<OutputStringType>(), "Output should be a basic string variant.");
    // static_assert(!typeHelper::areSameTypes<InputStringType, OutputStringType>(), "Input and output should be
    // different types."); // can be UTF8 encoded
    return OutputStringType(inputString.cbegin(), inputString.cend());
}

// Alignments

std::string getStringWithJustifyAlignment(std::string_view mainString, size_t const targetLength);
std::string getStringWithCenterAlignment(std::string_view mainString, size_t const targetLength);
std::string getStringWithRightAlignment(std::string_view mainString, size_t const targetLength);
std::string getStringWithLeftAlignment(std::string_view mainString, size_t const targetLength);

// PathHelpers

std::string getCorrectPathWithoutUrlParameters(std::string_view path);
std::string getUrlParameters(std::string_view path);
std::string getCorrectPathWithReplacedSlashCharacters(std::string_view path, std::string_view slashCharacterString);
std::string getCorrectPathWithoutDoublePeriod(std::string_view mainString, std::string_view slashCharacterString);
std::string getStringBeforeDoublePeriod(std::string_view mainString, std::string_view slashCharacterString);
std::string getImmediateDirectoryName(std::string_view mainString, std::string_view slashCharacterString);
template <char slashCharacterString>
std::string getCorrectPathWithReplacedSlashCharacters(std::string_view path);
template <char slashCharacterString>
std::string getCorrectPathWithoutDoublePeriod(std::string_view path);
template <char slashCharacterString>
std::string getStringBeforeDoublePeriod(std::string_view path);
template <char slashCharacterString>
std::string getImmediateDirectoryName(std::string_view path);

// string to type converters
// NOTE: Consider stoul, stoull, stoi, stol, stoll, stof, stod, stold for this conversions

bool convertStringToBool(std::string_view stringToConvert);
template <typename NumberType>
NumberType convertStringToNumber(std::string_view stringToConvert);
template <typename NumberType>
NumberType convertHexCharacterToNumber(char const character);
template <typename NumberType>
NumberType convertHexStringToNumber(std::string_view stringToConvert);
AlbaNumber convertStringToAlbaNumber(std::string_view stringToConvert);

template <typename NumberType>
NumberType convertStringToNumber(std::string_view stringToConvert) {
    bool isNumberNotYetEncountered(true);
    bool isPeriodNotYetEncountered(true);
    int negative(1);
    int decimalPlacesInPowersOfTen(10);
    NumberType value(0);
    for (char const currentCharacter : stringToConvert) {
        if (isNumber(currentCharacter)) {
            if (isPeriodNotYetEncountered) {
                value = (value * 10) + static_cast<NumberType>(currentCharacter - '0');
                isNumberNotYetEncountered = false;
            } else {
                value = value + ((static_cast<NumberType>(currentCharacter - '0')) /
                                 static_cast<NumberType>(decimalPlacesInPowersOfTen));
                decimalPlacesInPowersOfTen *= 10;
            }
        } else if (currentCharacter == '-' && isNumberNotYetEncountered) {
            negative *= -1;
        } else if (currentCharacter == '.') {
            isPeriodNotYetEncountered = false;
        }
    }
    return value * static_cast<NumberType>(negative);
}

template <typename NumberType>
NumberType convertHexCharacterToNumber(char const character) {
    NumberType value{};
    if (isHexDigit(character)) {
        if (isNumber(character)) {
            value = static_cast<NumberType>(character - '0');
        } else if (isCapitalLetter(character)) {
            value = static_cast<NumberType>(character - 'A' + 0xA);
        } else {
            value = static_cast<NumberType>(character - 'a' + 0xA);
        }
    }
    return value;
}

template <typename NumberType>
NumberType convertHexStringToNumber(std::string_view stringToConvert) {
    NumberType value = 0;
    for (char const currentCharacter : stringToConvert) {
        if (isHexDigit(currentCharacter)) {
            value *= 0x10;
            value += convertHexCharacterToNumber<NumberType>(currentCharacter);
        }
    }
    return value;
}

// type to string converters
// NOTE: Consider std::to_string for this conversions

std::string convertBoolToString(bool const value);

template <typename AnyType>
inline std::string convertToString(AnyType const& object) {
    std::stringstream temporaryStream;
    temporaryStream << object;
    return temporaryStream.str();
}

class StringConverterWithFormatting {
public:
    using IntOptional = std::optional<int>;
    using CharOptional = std::optional<char>;
    using UnsignedIntOptional = std::optional<size_t>;

    StringConverterWithFormatting() = default;

    StringConverterWithFormatting(int const precision)
        : m_precisionOptional(precision),
          m_fieldWidthOptional(),
          m_fillCharacterOptional(),
          m_maximumLengthOptional() {}

    StringConverterWithFormatting(int const fieldWidth, char const fillCharacter)
        : m_precisionOptional(),
          m_fieldWidthOptional(fieldWidth),
          m_fillCharacterOptional(fillCharacter),
          m_maximumLengthOptional() {}

    StringConverterWithFormatting(size_t const maximumLength)
        : m_precisionOptional(),
          m_fieldWidthOptional(),
          m_fillCharacterOptional(),
          m_maximumLengthOptional(maximumLength) {}

    StringConverterWithFormatting(
        int const precision, int const fieldWidth, char const fillCharacter, size_t const maximumLength)
        : m_precisionOptional(precision),
          m_fieldWidthOptional(fieldWidth),
          m_fillCharacterOptional(fillCharacter),
          m_maximumLengthOptional(maximumLength) {}

    template <typename AnyType>
    std::string convertToString(AnyType const& object) const {
        std::stringstream temporaryStream;
        if (m_precisionOptional) {
            temporaryStream.precision(m_precisionOptional.value());
        }
        if (m_fillCharacterOptional) {
            temporaryStream << std::setfill(m_fillCharacterOptional.value());
        }
        if (m_fieldWidthOptional) {
            temporaryStream << std::setw(m_fieldWidthOptional.value());
        }
        temporaryStream << object;
        if (m_maximumLengthOptional) {
            return temporaryStream.str().substr(m_maximumLengthOptional.value());
        } else {
            return temporaryStream.str();
        }
    }

    void setPrecision(int const precision);
    void setFieldWidth(int const fieldWidth);
    void setFillCharacter(char const fillCharacter);
    void setMaximumLength(size_t const maximumLength);

private:
    IntOptional m_precisionOptional;
    IntOptional m_fieldWidthOptional;
    CharOptional m_fillCharacterOptional;
    UnsignedIntOptional m_maximumLengthOptional;
};

}  // namespace alba::stringHelper
