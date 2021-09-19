#include "AlbaStringHelper.hpp"

#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/Randomizer/AlbaSimpleRandomizer.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>

#include <algorithm>
#include <cstring>
#include <functional>
#include <numeric>
#include <set>
#include <sstream>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace stringHelper
{

unsigned int generateUniqueId(string const& mainString)
{
    unsigned int uniqueId=1;
    uniqueId = accumulate(mainString.begin(), mainString.end(), uniqueId, [](unsigned int c1, unsigned char c2)
    {
        return (c1*c2)+1;
    });
    return uniqueId;
}

unsigned int getLevenshteinDistance(string const& otherString, string const& basisString)
{
    // The edit distance or Levenshtein distance is the minimum number of editing operations needed to transform a string into another string.
    // The allowed editing operations are as follows:
    // -> insert a character (e.g. ABC ! ABCA)
    // -> remove a character (e.g. ABC ! AC)
    // -> modify a character (e.g. ABC ! ADC)

    using Counts = vector<unsigned int>;

    vector<Counts> previousAndCurrentCounts(2, Counts(basisString.length()+1)); // string1 as basis
    Counts & firstPrevious(previousAndCurrentCounts[0]);
    iota(firstPrevious.begin(), firstPrevious.end(), 0); // first row

    for(unsigned int otherIndex=1; otherIndex<=otherString.length(); otherIndex++)
    {
        Counts & previousCounts(previousAndCurrentCounts[(otherIndex-1)%2]);
        Counts & currentCounts(previousAndCurrentCounts[otherIndex%2]);

        currentCounts[0] = otherIndex; // first column
        for (unsigned int basisIndex=1; basisIndex<=basisString.length(); basisIndex++)
        {
            unsigned int cost = basisString.at(basisIndex-1)==otherString.at(otherIndex-1) ? 0 : 1;
            currentCounts[basisIndex]
                    = min(min(currentCounts.at(basisIndex-1)+1, previousCounts.at(basisIndex)+1), previousCounts.at(basisIndex-1)+cost);
        }
    }

    Counts const& lastCurrent(previousAndCurrentCounts.at(otherString.length()%2));
    return lastCurrent.back();
}

unsigned int getHammingDistance(string const& string1, string const& string2)
{
    // The Hamming distance hamming(a,b) between two strings a and b of equal length is the number of positions where the strings differ.
    unsigned int result(0);
    unsigned int commonLength = min(string1.length(), string2.length());
    for(unsigned int i=0; i<commonLength; i++)
    {
        if(string1.at(i) != string2.at(i))
        {
            result++;
        }
    }
    return result;
}

unsigned int getNumberOfSubStrings(string const& mainString)
{
    // A string of length n has n(n+1)/2 substrings.

    unsigned int n = mainString.length();
    return n*(n+1)/2;
}

unsigned int getNumberOfSubsequences(string const& mainString)
{
    // A string of length n has 2^n - 1 subsequences.

    return static_cast<unsigned int>(get2ToThePowerOf(mainString.length())-1);
}

int getRotationValue(string const& mainString, string const& rotation)
{
    // A rotation can be generated by moving the characters of a string one by one from the beginning to the end (or vice versa).
    // For example, the rotations of ABCD are ABCD, BCDA, CDAB and DABC.

    int result = static_cast<int>(string::npos);
    if(mainString.length() == rotation.length())
    {
        string doubleMainString = mainString + mainString;
        result = static_cast<int>(doubleMainString.find(rotation));
    }
    return result;
}

int getPeriodValue(string const& mainString, string const& period)
{
    // A period is a prefix of a string such that the string can be constructed by repeating the period.
    // The last repetition may be partial and contain only a prefix of the period.
    // For example, the shortest period of ABCABCA is ABC.

    int periodCount(0);
    if(!period.empty())
    {
        for(unsigned int i(0U), j(0U); i<mainString.length(); i++, j++)
        {
            if(j == period.length())
            {
                j=0;
                periodCount++;
            }
            if(mainString.at(i) != period.at(j))
            {
                periodCount = 0;
                break;
            }
        }
    }
    return (periodCount > 0) ? periodCount : static_cast<int>(string::npos);
}

bool isNumber(string const& mainString)
{
    return any_of(mainString.begin(), mainString.end(), [](char const character){ return isNumber(character);});
}

bool isWhiteSpace(string const& mainString)
{
    return all_of(mainString.begin(), mainString.end(), [](char const character){ return isWhiteSpace(character);});
}

bool isNewline(string const& mainString)
{
    return all_of(mainString.begin(), mainString.end(), [](char const character){ return isNewline(character);});
}

bool isIdentifier(string const& mainString)
{
    bool isIdentifier(false);
    if(!mainString.empty())
    {
        char firstCharacter = mainString[0];
        isIdentifier = isLetter(firstCharacter) || isUnderscore(firstCharacter);
    }
    return isIdentifier;
}

bool isOneWord(string const& mainString)
{
    return (!mainString.empty()) && none_of(mainString.begin(), mainString.end(), [](char const character){ return isWhiteSpace(character);});
}

bool isPalindrome(string const& mainString)
{
    bool result(false);
    if(!mainString.empty())
    {
        result=true;
        unsigned int left(0), right(mainString.length()-1);
        while(left<right)
        {
            if(mainString.at(left++) != mainString.at(right--))
            {
                result=false;
                break;
            }
        }
    }
    return result;
}

bool isSubstring(string const& mainString, string const& subString)
{
    // A substring is a sequence of consecutive characters in a string.
    // We use the notation s[a...b] to refer to a substring of s that begins at position a and ends at position b.
    // A string of length n has n(n+1)/2 substrings.
    // For example, the substrings of ABCD are A, B, C, D, AB, BC, CD, ABC, BCD and ABCD.

    return isNotNpos(static_cast<int>(mainString.find(subString)));
}

bool isSubsequence(string const& mainString, string const& subsequence)
{
    // A subsequence is a sequence of (not necessarily consecutive) characters in a string in their original order.
    // A string of length n has 2n-1 subsequences.
    // For example, the subsequences of ABCD are A, B, C, D, AB, AC, AD, BC, BD, CD, ABC, ABD, ACD, BCD and ABCD.

    unsigned int j(0U);
    for(unsigned int i(0U); i<mainString.length() && j<subsequence.length(); i++)
    {
        if(mainString.at(i) == subsequence.at(j))
        {
            j++;
        }
    }
    return j == subsequence.length();
}

bool isPrefix(string const& mainString, string const& prefix)
{
    // A prefix is a substring that starts at the beginning of a string.
    // For example, the prefixes of ABCD are A, AB, ABC and ABCD.

    unsigned int j(0U);
    for(unsigned int i(0U); i<mainString.length() && j<prefix.length(); i++, j++)
    {
        if(mainString.at(i) != prefix.at(j))
        {
            break;
        }
    }
    return j == prefix.length();
}

bool isSuffix(string const& mainString, string const& suffix)
{
    // A suffix is a substring that ends at the end of a string.
    // For example, the suffixes of ABCD are D, CD, BCD and ABCD.

    int j = static_cast<int>(suffix.length()) - 1;
    for(int i = static_cast<int>(mainString.length()) - 1; i>=0 && j>=0; i--, j--)
    {
        if(mainString.at(i) != suffix.at(j))
        {
            break;
        }
    }
    return j == -1;
}

bool isRotation(string const& mainString, string const& rotation)
{
    // A rotation can be generated by moving the characters of a string one by one from the beginning to the end (or vice versa).
    // For example, the rotations of ABCD are ABCD, BCDA, CDAB and DABC.

    return isNotNpos(getRotationValue(mainString, rotation));
}

bool isPeriod(string const& mainString, string const& period)
{
    // A period is a prefix of a string such that the string can be constructed by repeating the period.
    // The last repetition may be partial and contain only a prefix of the period.
    // For example, the shortest period of ABCABCA is ABC.

    return isNotNpos(getPeriodValue(mainString, period));
}

bool isBorder(string const& mainString, string const& border)
{
    // A border is a string that is both a prefix and a suffix of a string.
    // For example, the borders of ABACABA are A, ABA and ABACABA.

    return isPrefix(mainString, border) && isSuffix(mainString, border);
}

bool isEqualNotCaseSensitive(string const& mainString, string const& string2)
{
    return getStringWithCapitalLetters(mainString) == getStringWithCapitalLetters(string2);
}

bool isEqualWithLowestCommonLength(string const& string1, string const& string2)
{
    unsigned int length1 = string1.length();
    unsigned int length2 = string2.length();
    unsigned int lowestLength = (length1>length2) ? length2 : length1;
    return string1.substr(0, lowestLength) == string2.substr(0, lowestLength);
}

bool isStringFoundInsideTheOtherStringCaseSensitive(string const& mainString, string const& string2)
{
    return isNotNpos(static_cast<int>(mainString.find(string2)));
}

bool isStringFoundInsideTheOtherStringNotCaseSensitive(string const& mainString, string const& string2)
{
    return isStringFoundInsideTheOtherStringCaseSensitive(getStringWithCapitalLetters(mainString), getStringWithCapitalLetters(string2));
}

bool isWildcardMatch(string const& mainString, string const& wildcard, unsigned int const mainStringIndex, unsigned int const wildcardIndex)
{
    bool result(false);
    bool isMainStringDone = mainStringIndex >= mainString.size();
    bool isWildcardDone = wildcardIndex >= wildcard.size();
    if(isMainStringDone && isWildcardDone)
    {
        result = true;
    }
    else if(isWildcardDone)
    {
        result = false;
    }
    else if(isMainStringDone)
    {
        bool isWildcardDoneOnNextIndex = wildcardIndex+1 >= wildcard.size();
        result = wildcard[wildcardIndex] == '*' && isWildcardDoneOnNextIndex;
    }
    else if(wildcard[wildcardIndex] == mainString[mainStringIndex])
    {
        result = isWildcardMatch(mainString, wildcard, mainStringIndex+1, wildcardIndex+1);
    }
    else if(wildcard[wildcardIndex] == '?')
    {
        result = isWildcardMatch(mainString, wildcard, mainStringIndex+1, wildcardIndex+1) || isWildcardMatch(mainString, wildcard, mainStringIndex, wildcardIndex+1);
    }
    else if(wildcard[wildcardIndex] == '*')
    {
        result = isWildcardMatch(mainString, wildcard, mainStringIndex, wildcardIndex+1) || isWildcardMatch(mainString, wildcard, mainStringIndex+1, wildcardIndex);
    }
    return result;
}

string getStringWithCapitalLetters(string const& mainString)
{
    string result;
    result.resize(mainString.length());
    transform(mainString.begin(), mainString.end(), result.begin(), ::toupper);
    return result;
}

string getStringWithFirstNonWhiteSpaceCharacterToCapital(string const& mainString)
{
    string result;
    result = mainString;
    unsigned int resultLength = result.length();
    for (unsigned int i = 0; i < resultLength; ++i)
    {
        if(!isWhiteSpace(result[i]))
        {
            result[i] = static_cast<char>(::toupper(result[i]));
            break;
        }
    }
    return result;
}

string getStringWithLowerCaseLetters(string const& mainString)
{
    string result;
    result.resize(mainString.length());
    transform(mainString.begin(), mainString.end(), result.begin(), ::tolower);
    return result;
}

string getStringWithUrlDecodedString(string const& mainString)
{
    string result;
    unsigned int index = 0, length = mainString.length();
    while(index < length)
    {
        if(mainString[index] == '%' &&
                (static_cast<int>(index) < static_cast<int>(length)-2) &&
                isHexDigit(mainString[index + 1]) &&
                isHexDigit(mainString[index + 2]))
        {
            result += convertHexStringToNumber<char>(mainString.substr(index + 1, 2));
            index += 3;
        }
        else
        {
            result += mainString[index++];
        }
    }
    return result;
}

string getStringThatContainsWhiteSpaceIndention(string const& mainString)
{
    string result;
    unsigned int firstIndexOfNotOfCharacters(mainString.find_first_not_of(WHITESPACE_STRING));
    if(isNotNpos(static_cast<int>(firstIndexOfNotOfCharacters)))
    {
        result = mainString.substr(0, firstIndexOfNotOfCharacters);
    }
    return result;
}

string getStringWithoutStartingAndTrailingCharacters(string const& mainString, string const& characters)
{
    string result(mainString);
    unsigned int firstIndexOfNotOfCharacters(result.find_first_not_of(characters));
    if(isNotNpos(static_cast<int>(firstIndexOfNotOfCharacters)))
    {
        result.erase(0, firstIndexOfNotOfCharacters);
        unsigned int lastIndexOfOfNotOfCharacters(result.find_last_not_of(characters));
        if(isNotNpos(static_cast<int>(lastIndexOfOfNotOfCharacters)))
        {
            result.erase(lastIndexOfOfNotOfCharacters+1);
        }
    }
    else
    {
        result.clear();
    }
    return result;
}

string getStringWithoutStartingAndTrailingWhiteSpace(string const& mainString)
{
    return getStringWithoutStartingAndTrailingCharacters(mainString, WHITESPACE_STRING);
}

string getStringWithoutWhiteSpace(string const& mainString)
{
    string result;
    unsigned int index = 0, length = mainString.length();
    while(index < length)
    {
        if(!isWhiteSpace(mainString[index]))
        {
            result+=mainString[index];
        }
        index++;
    }
    return result;
}

string getStringWithoutRedundantWhiteSpace(string const& mainString)
{
    string result;
    unsigned int index = 0, length = mainString.length();
    while(index < length)
    {
        unsigned int indexNotWhiteSpace = mainString.find_first_not_of(WHITESPACE_STRING, index);
        if(isNpos(static_cast<int>(indexNotWhiteSpace))){break;}
        unsigned int indexWhiteSpace = mainString.find_first_of(WHITESPACE_STRING, indexNotWhiteSpace);
        index = (isNotNpos(static_cast<int>(indexWhiteSpace))) ? indexWhiteSpace : length;
        result += (!result.empty()) ? " "s : string();
        result += mainString.substr(indexNotWhiteSpace, index-indexNotWhiteSpace);
    }
    return result;
}

string getStringWithoutQuotations(string const& mainString)
{
    unsigned int length = mainString.length();
    if(length>2 && mainString[0] == '\"' && mainString[length-1] == '\"')
    {
        return mainString.substr(1, length-2);
    }
    return mainString;
}

string getStringWithoutCharAtTheStartAndEnd(string const& mainString, char const char1)
{
    return getStringWithoutCharAtTheStart(getStringWithoutCharAtTheEnd(mainString, char1), char1);
}

string getStringWithoutCharAtTheStart(string const& mainString, char const char1)
{
    unsigned int length = mainString.length();
    unsigned int start = (mainString[0] == char1) ? 1 : 0;
    return mainString.substr(start, length-start);
}

string getStringWithoutCharAtTheEnd(string const& mainString, char const char1)
{
    unsigned int length = mainString.length();
    unsigned int end = (length == 0) ? 0 : (mainString[length-1] == char1) ? length-1 : length;
    return mainString.substr(0, end);
}

string getStringWithoutOpeningClosingOperators(string const& mainString, char const openingOperator, char const closingOperator)
{
    unsigned int length = mainString.length();
    unsigned int start = (mainString[0] == openingOperator) ? 1 : 0;
    unsigned int end = (length == 0) ? 0 : (mainString[length-1] == closingOperator) ? length-1 : length;
    return mainString.substr(start, end-start);
}

string getLongestCommonPrefix(string const& first, string const& second)
{
    unsigned int i=0;
    for(; i<first.length() && i<second.length(); i++)
    {
        if(first.at(i) != second.at(i))
        {
            break;
        }
    }
    return first.substr(0, i);
}

void copyBeforeStringAndAfterString(
        string const& mainString,
        string const& stringToSearch,
        string & beforeString,
        string & afterString,
        unsigned int const indexToStartTheSearch)
{
    beforeString.clear();
    afterString.clear();
    unsigned int firstIndexOfFirstString = mainString.find(stringToSearch, indexToStartTheSearch);
    if(isNotNpos(static_cast<int>(firstIndexOfFirstString)))
    {
        unsigned int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        beforeString = mainString.substr(0, firstIndexOfFirstString);
        afterString = mainString.substr(lastIndexOfFirstString);
    }
}

string getStringBeforeThisString(string const& mainString, string const& stringToSearch, unsigned int const indexToStart)
{
    string result;
    unsigned int firstIndexOfFirstString = mainString.find(stringToSearch, indexToStart);
    if(isNotNpos(static_cast<int>(firstIndexOfFirstString)))
    {
        result = mainString.substr(0, firstIndexOfFirstString);
    }
    return result;
}

string getStringAfterThisString(string const& mainString, string const& stringToSearch, unsigned int const indexToStart)
{
    string result;
    unsigned int firstIndexOfFirstString = mainString.find(stringToSearch, indexToStart);
    if(isNotNpos(static_cast<int>(firstIndexOfFirstString)))
    {
        unsigned int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        result = mainString.substr(lastIndexOfFirstString);
    }
    return result;
}

string getStringInBetweenTwoStrings(string const& mainString, string const& firstString, string const& secondString, unsigned int const indexToStart)
{
    string result;
    unsigned int firstIndexOfFirstString = mainString.find(firstString, indexToStart);
    if(isNotNpos(static_cast<int>(firstIndexOfFirstString)))
    {
        unsigned int lastIndexOfFirstString = firstIndexOfFirstString + firstString.length();
        unsigned int firstIndexOfSecondString = mainString.find(secondString, lastIndexOfFirstString);
        if(isNotNpos(static_cast<int>(firstIndexOfSecondString)))
        {
            result = mainString.substr(lastIndexOfFirstString, firstIndexOfSecondString-lastIndexOfFirstString);
        }
    }
    return result;
}

string getStringBeforeThisCharacters(string const& mainString, string const& characters, unsigned int const indexToStart)
{
    string result;
    unsigned int firstIndexOfNotOfCharacters(mainString.find_first_of(characters, indexToStart));
    if(isNotNpos(static_cast<int>(firstIndexOfNotOfCharacters)))
    {
        result = mainString.substr(indexToStart, firstIndexOfNotOfCharacters-indexToStart);
    }
    return result;
}

string getStringByRepeatingUntilDesiredLength(string const& stringToRepeat, unsigned int desiredLength)
{
    string result;
    if(!stringToRepeat.empty())
    {
        unsigned int stringToRepeatLength = stringToRepeat.length();
        for(unsigned int index=0; index<=desiredLength; index += stringToRepeatLength)
        {
            result += stringToRepeat;
        }
        result = result.substr(0, desiredLength);
    }
    return result;
}

string getStringAndReplaceNonAlphanumericCharactersToUnderScore(string const& path)
{
    bool isPreviousCharacterNonAlphanumeric = false;
    string correctPath = accumulate(
                path.cbegin(), path.cend(), string(), [&isPreviousCharacterNonAlphanumeric]
                (string const& currentString, char const currentCharacter)
    {
            string partialResult(currentString);
            if(!isLetterOrNumber(currentCharacter))
    {
            if(!isPreviousCharacterNonAlphanumeric)
    {
            partialResult += "_"s;
}
}
            else
    {
            partialResult += currentCharacter;
}
            isPreviousCharacterNonAlphanumeric = !isLetterOrNumber(currentCharacter);
            return partialResult;
});
    return correctPath;
}

string getNumberAfterThisString(string const& mainString, string const& stringToSearch)
{
    string result;
    unsigned int firstIndexOfFirstString = mainString.find(stringToSearch);
    if(isNotNpos(static_cast<int>(firstIndexOfFirstString)))
    {
        unsigned int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        unsigned int lastIndexOfNumber;
        for(lastIndexOfNumber = lastIndexOfFirstString; isNumber(mainString[lastIndexOfNumber]); ++lastIndexOfNumber);
        result = mainString.substr(lastIndexOfFirstString, lastIndexOfNumber-lastIndexOfFirstString);
    }
    return result;
}

string getHexNumberAfterThisString(string const& mainString, string const& stringToSearch)
{
    string result;
    unsigned int firstIndexOfFirstString = mainString.find(stringToSearch);
    if(isNotNpos(static_cast<int>(firstIndexOfFirstString)))
    {
        unsigned int lastIndexOfFirstString = firstIndexOfFirstString + stringToSearch.length();
        unsigned int lastIndexOfNumber(lastIndexOfFirstString);
        for(; isHexDigit(mainString[lastIndexOfNumber]); ++lastIndexOfNumber);
        result = mainString.substr(lastIndexOfFirstString, lastIndexOfNumber-lastIndexOfFirstString);
    }
    return result;
}

string getHexEquivalentOfCharacters(string const& stringToCheck)
{
    stringstream ss;
    for(unsigned char const c : stringToCheck)
    {
        ss  << hex << uppercase << setfill('0') << setw(2) << static_cast<unsigned int>(c);
    }
    return ss.str();
}

string constructFileLocator(string const& file, int const lineNumber)
{
    stringstream ss;
    ss << file.substr(file.find_last_of('\\')+1) << "[" << lineNumber << "]";
    return ss.str();
}

string getRandomAlphaNumericString(unsigned int const length)
{
    constexpr auto ALPHA_NUMERIC_CHAR_MAP = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    AlbaSimpleRandomizer randomizer;
    int alphaNumericCharMapIndexMax = static_cast<int>(strlen(ALPHA_NUMERIC_CHAR_MAP))-1;
    string result;
    result.reserve(length);
    generate_n(back_inserter(result), length, [&]()
    {
        return ALPHA_NUMERIC_CHAR_MAP[static_cast<unsigned int>(randomizer.getRandomIntegerInUniformDistribution(0, alphaNumericCharMapIndexMax))];
    });
    return result;
}

strings getArgumentsToStringInMain(int const argc, char const * const argv[])
{
    strings result;
    for (int argumentIndex=0; argumentIndex<argc; argumentIndex++)
    {
        result.emplace_back(argv[argumentIndex]);
    }
    return result;
}

bool transformReplaceStringIfFound(string& mainString, string const& toReplace, string const& replaceWith)
{
    bool found=false;
    unsigned int toReplaceLength = toReplace.length();
    unsigned int replaceWithLength = replaceWith.length();
    unsigned int index = mainString.find(toReplace);
    while(isNotNpos(static_cast<int>(index)))
    {
        found = true;
        mainString.replace(index, toReplaceLength, replaceWith);
        index = mainString.find(toReplace, index + replaceWithLength);
    }
    return found;
}


template <SplitStringType splitStringType> void splitToStrings(strings & listOfStrings, string const& mainString, string const& delimiters)
{
    unsigned int startingIndexOfFind(0);
    unsigned int delimiterIndex = mainString.find_first_of(delimiters);
    unsigned int delimeterLength = 1;
    unsigned int mainStringLength = mainString.length();
    while(isNotNpos(static_cast<int>(delimiterIndex)))
    {
        if(startingIndexOfFind != delimiterIndex)
        {
            listOfStrings.emplace_back(mainString.substr(startingIndexOfFind, delimiterIndex-startingIndexOfFind));
        }
        if(SplitStringType::WithDelimeters == splitStringType)
        {
            listOfStrings.emplace_back(mainString.substr(delimiterIndex, delimeterLength));
        }
        startingIndexOfFind = delimiterIndex + delimeterLength;
        delimiterIndex = mainString.find_first_of(delimiters, startingIndexOfFind);
    }
    if(startingIndexOfFind != mainStringLength)
    {
        listOfStrings.emplace_back(mainString.substr(startingIndexOfFind, mainStringLength-startingIndexOfFind));
    }
}

template void splitToStrings<SplitStringType::WithoutDelimeters> (strings & listOfStrings, string const& mainString, string const& delimiter);
template void splitToStrings<SplitStringType::WithDelimeters> (strings & listOfStrings, string const& mainString, string const& delimiter);

string combineStrings(strings const& listOfStrings, string const& delimiters)
{
    string result = accumulate(listOfStrings.cbegin(), listOfStrings.cend(), string(), [&delimiters](string const& previousResult, string const& currentString)
    {
            return string(previousResult + currentString + delimiters);
});

    if(result.size() > delimiters.size())
    {
        result = result.substr(0, result.size() - delimiters.size());
    }
    return result;
}

void splitLinesToAchieveTargetLength(strings & strings, string const& mainString, unsigned int const targetLength)
{
    set<unsigned int> transitionIndexes;
    unsigned int mainStringLength = mainString.length();
    bool isPreviousCharacterAWhitespace(false);
    transitionIndexes.emplace(0);
    for(unsigned int i = 0; i < mainStringLength; i++)
    {
        char currentCharacter = mainString[i];
        if(isPreviousCharacterAWhitespace && !isWhiteSpace(currentCharacter))
        {
            transitionIndexes.emplace(i-1);
        }
        else if(!isPreviousCharacterAWhitespace && isWhiteSpace(currentCharacter))
        {
            transitionIndexes.emplace(i);
        }
        isPreviousCharacterAWhitespace = isWhiteSpace(currentCharacter);
    }
    transitionIndexes.emplace(mainStringLength);

    unsigned int previousSplittingIndex = 0;
    for(unsigned int splittingIndex = targetLength; splittingIndex < mainStringLength; splittingIndex += targetLength)
    {
        char currentCharacter = mainString[splittingIndex];

        if(!isWhiteSpace(currentCharacter))
        {
            auto pairOfIndex = containerHelper::getLowerAndUpperValuesForSet(transitionIndexes, splittingIndex);
            unsigned int lowerTransitionIndex(pairOfIndex.first+1);
            unsigned int upperTransitionIndex(pairOfIndex.second);
            int lowerDelta = static_cast<int>(splittingIndex-lowerTransitionIndex);
            int upperDelta = static_cast<int>(upperTransitionIndex-splittingIndex);

            bool isUpperValid(upperDelta >= 0);
            bool isLowerValid(lowerDelta >= 0 && lowerTransitionIndex != previousSplittingIndex);
            if(isUpperValid && isLowerValid)
            {
                if(upperDelta < lowerDelta)
                {
                    splittingIndex = upperTransitionIndex;
                }
                else
                {
                    splittingIndex = lowerTransitionIndex;
                }
            }
            else if(isUpperValid)
            {
                splittingIndex = upperTransitionIndex;
            }
            else if(isLowerValid)
            {
                splittingIndex = lowerTransitionIndex;
            }
        }
        strings.emplace_back(mainString.substr(previousSplittingIndex, splittingIndex-previousSplittingIndex));
        previousSplittingIndex = splittingIndex;
    }
    if(previousSplittingIndex!=mainStringLength)
    {
        strings.emplace_back(mainString.substr(previousSplittingIndex));
    }
}

void splitToStringsUsingASeriesOfDelimeters(strings & listOfStrings, string const& mainString, strings const& seriesOfDelimiters)
{
    if(!seriesOfDelimiters.empty())
    {
        unsigned int startingIndexOfFind(0);
        unsigned int mainStringLength = mainString.length();
        for(string const& delimeter : seriesOfDelimiters)
        {
            unsigned int delimiterIndex = mainString.find(delimeter, startingIndexOfFind);
            if(isNpos(static_cast<int>(delimiterIndex)))
            {
                break;
            }
            if(startingIndexOfFind != delimiterIndex)
            {
                listOfStrings.emplace_back(mainString.substr(startingIndexOfFind, delimiterIndex-startingIndexOfFind));
            }
            startingIndexOfFind = delimiterIndex + delimeter.length();
        }
        if(startingIndexOfFind != mainStringLength)
        {
            listOfStrings.emplace_back(mainString.substr(startingIndexOfFind, mainStringLength-startingIndexOfFind));
        }
    }
}

wstring convertStringToWideString(string const& stringInput)
{
    return wstring(stringInput.begin(), stringInput.end());
}

string convertWideStringToString(wstring const& wstringInput)
{
    return string(wstringInput.begin(), wstringInput.end());
}

string getStringWithJustifyAlignment(string const& mainString, unsigned int const targetLength)
{
    string result;
    string noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainString));
    string noWhiteSpace(getStringWithoutWhiteSpace(mainString));
    if(mainString.empty())
    {
        string gap(targetLength, ' ');
        result = gap;
    }
    else if(noRedundantWhiteSpace.length()>=targetLength)
    {
        result = noRedundantWhiteSpace;
    }
    else if(isOneWord(mainString))
    {
        unsigned int noRedundantWhiteSpaceLength = noRedundantWhiteSpace.length();
        unsigned int gapLength = (targetLength-noWhiteSpace.length())/(noRedundantWhiteSpaceLength+1);
        string gap(gapLength, ' ');
        result += gap;
        for(unsigned int i=0; i<noRedundantWhiteSpaceLength; i++)
        {
            result += noRedundantWhiteSpace[i];
            result += gap;
        }
        result += string(targetLength-result.length(), ' ');
    }
    else
    {
        strings actualStrings;
        splitToStrings<SplitStringType::WithoutDelimeters>(actualStrings, noRedundantWhiteSpace, " ");
        unsigned int numberOfStrings = actualStrings.size();
        unsigned int gapLength = (targetLength-noWhiteSpace.length())/(numberOfStrings-1);
        string gap(gapLength, ' ');
        for(unsigned int i=0; i<numberOfStrings; i++)
        {
            result += actualStrings[i];
            if(i<numberOfStrings-1)
            {
                result += gap;
            }
        }
        result += string(targetLength-result.length(), ' ');
    }
    return result;
}

string getStringWithCenterAlignment(string const& mainString, unsigned int const targetLength)
{
    string result;
    string noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainString));
    if(mainString.empty())
    {
        string gap(targetLength, ' ');
        result = gap;
    }
    else if(noRedundantWhiteSpace.length()>=targetLength)
    {
        result = noRedundantWhiteSpace;
    }
    else
    {
        unsigned int gapLength = (targetLength-noRedundantWhiteSpace.length())/2;
        result += string(gapLength, ' ');
        result += noRedundantWhiteSpace;
        result += string(targetLength-result.length(), ' ');
    }
    return result;
}

string getStringWithRightAlignment(string const& mainString, unsigned int const targetLength)
{
    string result;
    string noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainString));
    if(mainString.empty())
    {
        string gap(targetLength, ' ');
        result = gap;
    }
    else if(noRedundantWhiteSpace.length()>=targetLength)
    {
        result = noRedundantWhiteSpace;
    }
    else
    {
        unsigned int gapLength = (targetLength-noRedundantWhiteSpace.length());
        result += string(gapLength, ' ');
        result += noRedundantWhiteSpace;
    }
    return result;
}

string getStringWithLeftAlignment(string const& mainString, unsigned int const targetLength)
{
    string result;
    string noRedundantWhiteSpace(getStringWithoutRedundantWhiteSpace(mainString));
    if(mainString.empty())
    {
        string gap(targetLength, ' ');
        result = gap;
    }
    else if(noRedundantWhiteSpace.length()>=targetLength)
    {
        result = noRedundantWhiteSpace;
    }
    else
    {
        unsigned int gapLength = (targetLength-noRedundantWhiteSpace.length());
        result += noRedundantWhiteSpace;
        result += string(gapLength, ' ');
    }
    return result;
}

string getCorrectPathWithoutUrlParameters(string const& path)
{
    string correctPathWithoutUrlParameters(path);
    unsigned int indexOfQuestionMark = path.find_first_of('?');
    if(isNotNpos(static_cast<int>(indexOfQuestionMark)))
    {
        correctPathWithoutUrlParameters = path.substr(0, indexOfQuestionMark);
    }
    return correctPathWithoutUrlParameters;
}

string getUrlParameters(string const& path)
{
    string urlParameters;
    unsigned int indexOfQuestionMark = path.find_first_of('?');
    if(isNotNpos(static_cast<int>(indexOfQuestionMark)))
    {
        urlParameters = path.substr(indexOfQuestionMark);
    }
    return urlParameters;
}

string getCorrectPathWithReplacedSlashCharacters(string const& path, string const& slashCharacterString)
{
    bool wasSlashDetected = false;
    string correctPath = accumulate(path.cbegin(), path.cend(), string(),
                                    [&wasSlashDetected, slashCharacterString]
                                    (string const& currentString, char const currentCharacter)
    {
        string partialResult(currentString);
        if(isSlashCharacter(currentCharacter))
        {
            if(!wasSlashDetected){partialResult += slashCharacterString;}
        }
        else
        {
            partialResult += currentCharacter;
        }
        wasSlashDetected = isSlashCharacter(currentCharacter);
        return partialResult;
    });
    return correctPath;
}

string getCorrectPathWithoutDoublePeriod(string const& mainString, string const& slashCharacterString)
{
    string correctPath(mainString);
    bool isDirectoryChanged = true;
    while(isDirectoryChanged)
    {
        isDirectoryChanged = false;
        string stringToFind(slashCharacterString);
        stringToFind += ".."s;
        stringToFind += slashCharacterString;
        unsigned int indexOfDoublePeriod = correctPath.find(stringToFind);
        if(isNotNpos(static_cast<int>(indexOfDoublePeriod)))
        {
            unsigned int indexOfNearestSlash = correctPath.find_last_of(slashCharacterString, indexOfDoublePeriod-1);
            if(isNotNpos(static_cast<int>(indexOfNearestSlash)))
            {
                isDirectoryChanged = true;
                correctPath.erase(indexOfNearestSlash, indexOfDoublePeriod+3-indexOfNearestSlash);
            }
        }
    }
    return correctPath;
}

string getStringBeforeDoublePeriod(string const& mainString, string const& slashCharacterString)
{
    unsigned int indexOfLastDoublePeriod = mainString.rfind(".."s + slashCharacterString);
    if(isNotNpos(static_cast<int>(indexOfLastDoublePeriod)))
    {
        return mainString.substr(indexOfLastDoublePeriod+3);
    }
    return mainString;
}

string getImmediateDirectoryName(string const& mainString, string const& slashCharacterString)
{
    unsigned int indexLastCharacterToSearch = mainString.length();
    string result;
    while(result.empty())
    {
        unsigned int indexOfLastSlashString = mainString.find_last_of(slashCharacterString, indexLastCharacterToSearch);
        if(isNpos(static_cast<int>(indexOfLastSlashString)))
        {
            break;
        }
        result = mainString.substr(indexOfLastSlashString+1, indexLastCharacterToSearch-indexOfLastSlashString);
        indexLastCharacterToSearch = indexOfLastSlashString-1;
    }
    return result;
}

template <char slashCharacter>
string getCorrectPathWithReplacedSlashCharacters(string const& path)
{
    return getCorrectPathWithReplacedSlashCharacters(path, string(1, slashCharacter));
}
template string getCorrectPathWithReplacedSlashCharacters<'\\'>(string const& path);
template string getCorrectPathWithReplacedSlashCharacters<'/'>(string const& path);

template <char slashCharacter>
string getCorrectPathWithoutDoublePeriod(string const& path)
{
    return getCorrectPathWithoutDoublePeriod(path, string(1, slashCharacter));
}
template string getCorrectPathWithoutDoublePeriod<'\\'>(string const& path);
template string getCorrectPathWithoutDoublePeriod<'/'>(string const& path);

template <char slashCharacter>
string getStringBeforeDoublePeriod(string const& path)
{
    return getStringBeforeDoublePeriod(path, string(1, slashCharacter));
}
template string getStringBeforeDoublePeriod<'\\'>(string const& path);
template string getStringBeforeDoublePeriod<'/'>(string const& path);

template <char slashCharacter>
string getImmediateDirectoryName(string const& path)
{
    return getImmediateDirectoryName(path, string(1, slashCharacter));
}
template string getImmediateDirectoryName<'\\'>(string const& path);
template string getImmediateDirectoryName<'/'>(string const& path);

bool convertStringToBool(string const& stringToConvert)
{
    string allCapital(getStringWithCapitalLetters(stringToConvert));
    bool result(false);
    if("TRUE" == allCapital)
    {
        result = true;
    }
    else if("FALSE" == allCapital)
    {
        result = false;
    }
    else
    {
        result = (0 != convertStringToNumber<int>(stringToConvert));
    }
    return result;
}

AlbaNumber convertStringToAlbaNumber(string const& stringToConvert)
{
    AlbaNumber result;
    if(isStringFoundInsideTheOtherStringCaseSensitive(stringToConvert, "."))
    {
        result = AlbaNumber(convertStringToNumber<double>(stringToConvert));
    }
    else
    {
        result = AlbaNumber(convertStringToNumber<int>(stringToConvert));
    }
    return result;
}

string convertBoolToString(bool const value)
{
    stringstream temporaryStream;
    temporaryStream << boolalpha << value;
    return temporaryStream.str();
}

void StringConverterWithFormatting::setPrecision(int const precision)
{
    m_precisionOptional = precision;
}

void StringConverterWithFormatting::setFieldWidth(int const fieldWidth)
{
    m_fieldWidthOptional = fieldWidth;
}

void StringConverterWithFormatting::setFillCharacter(char const fillCharacter)
{
    m_fillCharacterOptional = fillCharacter;
}

void StringConverterWithFormatting::setMaximumLength(unsigned int const maximumLength)
{
    m_maximumLengthOptional = maximumLength;
}

}//namespace stringHelper

}//namespace alba
