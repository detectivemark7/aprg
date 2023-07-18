#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace std;
using namespace alba::stringHelper;

namespace alba {

TEST(BoolCharacterStringTest, IsWhiteSpaceWorks) {
    EXPECT_FALSE(isWhiteSpace('\0'));
    EXPECT_TRUE(isWhiteSpace('\xA'));
    EXPECT_TRUE(isWhiteSpace('\r'));
    EXPECT_TRUE(isWhiteSpace('\n'));
    EXPECT_TRUE(isWhiteSpace('\t'));
    EXPECT_TRUE(isWhiteSpace(' '));
    EXPECT_FALSE(isWhiteSpace('!'));
    EXPECT_FALSE(isWhiteSpace('~'));
    EXPECT_FALSE(isWhiteSpace('A'));
    EXPECT_FALSE(isWhiteSpace('J'));
    EXPECT_FALSE(isWhiteSpace('Z'));
    EXPECT_FALSE(isWhiteSpace('a'));
    EXPECT_FALSE(isWhiteSpace('j'));
    EXPECT_FALSE(isWhiteSpace('z'));
    EXPECT_FALSE(isWhiteSpace('1'));
    EXPECT_FALSE(isWhiteSpace('9'));
    EXPECT_FALSE(isWhiteSpace('0'));
}

TEST(BoolCharacterStringTest, IsNewlineWorks) {
    EXPECT_FALSE(isNewline('\0'));
    EXPECT_TRUE(isNewline('\xA'));
    EXPECT_TRUE(isNewline('\r'));
    EXPECT_TRUE(isNewline('\n'));
    EXPECT_FALSE(isNewline('\t'));
    EXPECT_FALSE(isNewline(' '));
    EXPECT_FALSE(isNewline('!'));
    EXPECT_FALSE(isNewline('~'));
    EXPECT_FALSE(isNewline('A'));
    EXPECT_FALSE(isNewline('J'));
    EXPECT_FALSE(isNewline('Z'));
    EXPECT_FALSE(isNewline('a'));
    EXPECT_FALSE(isNewline('j'));
    EXPECT_FALSE(isNewline('z'));
    EXPECT_FALSE(isNewline('1'));
    EXPECT_FALSE(isNewline('9'));
    EXPECT_FALSE(isNewline('0'));
}

TEST(BoolCharacterStringTest, IsCapitalLetterWorks) {
    EXPECT_FALSE(isCapitalLetter('\0'));
    EXPECT_FALSE(isCapitalLetter('\xA'));
    EXPECT_FALSE(isCapitalLetter('\r'));
    EXPECT_FALSE(isCapitalLetter('\n'));
    EXPECT_FALSE(isCapitalLetter('\t'));
    EXPECT_FALSE(isCapitalLetter(' '));
    EXPECT_FALSE(isCapitalLetter('!'));
    EXPECT_FALSE(isCapitalLetter('~'));
    EXPECT_FALSE(isCapitalLetter('_'));
    EXPECT_TRUE(isCapitalLetter('A'));
    EXPECT_TRUE(isCapitalLetter('J'));
    EXPECT_TRUE(isCapitalLetter('Z'));
    EXPECT_FALSE(isCapitalLetter('a'));
    EXPECT_FALSE(isCapitalLetter('j'));
    EXPECT_FALSE(isCapitalLetter('z'));
    EXPECT_FALSE(isCapitalLetter('1'));
    EXPECT_FALSE(isCapitalLetter('9'));
    EXPECT_FALSE(isCapitalLetter('0'));
}

TEST(BoolCharacterStringTest, IsLowerCaseLetterWorks) {
    EXPECT_FALSE(isLowerCaseLetter('\0'));
    EXPECT_FALSE(isLowerCaseLetter('\xA'));
    EXPECT_FALSE(isLowerCaseLetter('\r'));
    EXPECT_FALSE(isLowerCaseLetter('\n'));
    EXPECT_FALSE(isLowerCaseLetter('\t'));
    EXPECT_FALSE(isLowerCaseLetter(' '));
    EXPECT_FALSE(isLowerCaseLetter('!'));
    EXPECT_FALSE(isLowerCaseLetter('~'));
    EXPECT_FALSE(isLowerCaseLetter('_'));
    EXPECT_FALSE(isLowerCaseLetter('A'));
    EXPECT_FALSE(isLowerCaseLetter('J'));
    EXPECT_FALSE(isLowerCaseLetter('Z'));
    EXPECT_TRUE(isLowerCaseLetter('a'));
    EXPECT_TRUE(isLowerCaseLetter('j'));
    EXPECT_TRUE(isLowerCaseLetter('z'));
    EXPECT_FALSE(isLowerCaseLetter('1'));
    EXPECT_FALSE(isLowerCaseLetter('9'));
    EXPECT_FALSE(isLowerCaseLetter('0'));
}

TEST(BoolCharacterStringTest, IsNumberWorks) {
    EXPECT_FALSE(isNumber('\0'));
    EXPECT_FALSE(isNumber('\xA'));
    EXPECT_FALSE(isNumber('\r'));
    EXPECT_FALSE(isNumber('\n'));
    EXPECT_FALSE(isNumber('\t'));
    EXPECT_FALSE(isNumber(' '));
    EXPECT_FALSE(isNumber('!'));
    EXPECT_FALSE(isNumber('~'));
    EXPECT_FALSE(isNumber('_'));
    EXPECT_FALSE(isNumber('A'));
    EXPECT_FALSE(isNumber('J'));
    EXPECT_FALSE(isNumber('Z'));
    EXPECT_FALSE(isNumber('a'));
    EXPECT_FALSE(isNumber('j'));
    EXPECT_FALSE(isNumber('z'));
    EXPECT_TRUE(isNumber('1'));
    EXPECT_TRUE(isNumber('9'));
    EXPECT_TRUE(isNumber('0'));
}

TEST(BoolCharacterStringTest, IsHexDigitWorks) {
    EXPECT_FALSE(isHexDigit('\0'));
    EXPECT_FALSE(isHexDigit('\xA'));
    EXPECT_FALSE(isHexDigit('\r'));
    EXPECT_FALSE(isHexDigit('\n'));
    EXPECT_FALSE(isHexDigit('\t'));
    EXPECT_FALSE(isHexDigit(' '));
    EXPECT_FALSE(isHexDigit('!'));
    EXPECT_FALSE(isHexDigit('~'));
    EXPECT_FALSE(isHexDigit('_'));
    EXPECT_TRUE(isHexDigit('A'));
    EXPECT_FALSE(isHexDigit('J'));
    EXPECT_FALSE(isHexDigit('Z'));
    EXPECT_TRUE(isHexDigit('a'));
    EXPECT_FALSE(isHexDigit('j'));
    EXPECT_FALSE(isHexDigit('z'));
    EXPECT_TRUE(isHexDigit('1'));
    EXPECT_TRUE(isHexDigit('9'));
    EXPECT_TRUE(isHexDigit('0'));
}

TEST(BoolCharacterStringTest, IsLetterOrNumberWorks) {
    EXPECT_FALSE(isLetterOrNumber('\0'));
    EXPECT_FALSE(isLetterOrNumber('\xA'));
    EXPECT_FALSE(isLetterOrNumber('\r'));
    EXPECT_FALSE(isLetterOrNumber('\n'));
    EXPECT_FALSE(isLetterOrNumber('\t'));
    EXPECT_FALSE(isLetterOrNumber(' '));
    EXPECT_FALSE(isLetterOrNumber('!'));
    EXPECT_FALSE(isLetterOrNumber('~'));
    EXPECT_FALSE(isLetterOrNumber('_'));
    EXPECT_TRUE(isLetterOrNumber('A'));
    EXPECT_TRUE(isLetterOrNumber('J'));
    EXPECT_TRUE(isLetterOrNumber('Z'));
    EXPECT_TRUE(isLetterOrNumber('a'));
    EXPECT_TRUE(isLetterOrNumber('j'));
    EXPECT_TRUE(isLetterOrNumber('z'));
    EXPECT_TRUE(isLetterOrNumber('1'));
    EXPECT_TRUE(isLetterOrNumber('9'));
    EXPECT_TRUE(isLetterOrNumber('0'));
}

TEST(BoolCharacterStringTest, IsPunctuationrWorks) {
    EXPECT_FALSE(isPunctuation('\0'));
    EXPECT_FALSE(isPunctuation('\xA'));
    EXPECT_FALSE(isPunctuation('\r'));
    EXPECT_FALSE(isPunctuation('\n'));
    EXPECT_FALSE(isPunctuation('\t'));
    EXPECT_FALSE(isPunctuation(' '));
    EXPECT_TRUE(isPunctuation('!'));
    EXPECT_TRUE(isPunctuation('~'));
    EXPECT_TRUE(isPunctuation('_'));
    EXPECT_FALSE(isPunctuation('A'));
    EXPECT_FALSE(isPunctuation('J'));
    EXPECT_FALSE(isPunctuation('Z'));
    EXPECT_FALSE(isPunctuation('a'));
    EXPECT_FALSE(isPunctuation('j'));
    EXPECT_FALSE(isPunctuation('z'));
    EXPECT_FALSE(isPunctuation('1'));
    EXPECT_FALSE(isPunctuation('9'));
    EXPECT_FALSE(isPunctuation('0'));
}

TEST(BoolCharacterStringTest, IsUnderscoreWorks) {
    EXPECT_FALSE(isUnderscore('\0'));
    EXPECT_FALSE(isUnderscore('\xA'));
    EXPECT_FALSE(isUnderscore('\r'));
    EXPECT_FALSE(isUnderscore('\n'));
    EXPECT_FALSE(isUnderscore('\t'));
    EXPECT_FALSE(isUnderscore(' '));
    EXPECT_FALSE(isUnderscore('!'));
    EXPECT_FALSE(isUnderscore('~'));
    EXPECT_TRUE(isUnderscore('_'));
    EXPECT_FALSE(isUnderscore('A'));
    EXPECT_FALSE(isUnderscore('J'));
    EXPECT_FALSE(isUnderscore('Z'));
    EXPECT_FALSE(isUnderscore('a'));
    EXPECT_FALSE(isUnderscore('j'));
    EXPECT_FALSE(isUnderscore('z'));
    EXPECT_FALSE(isUnderscore('1'));
    EXPECT_FALSE(isUnderscore('9'));
    EXPECT_FALSE(isUnderscore('0'));
}

TEST(BoolCharacterStringTest, IsLetterOrNumberOrUnderscoreWorks) {
    EXPECT_FALSE(isLetterOrNumberOrUnderscore('\0'));
    EXPECT_FALSE(isLetterOrNumberOrUnderscore('\xA'));
    EXPECT_FALSE(isLetterOrNumberOrUnderscore('\r'));
    EXPECT_FALSE(isLetterOrNumberOrUnderscore('\n'));
    EXPECT_FALSE(isLetterOrNumberOrUnderscore('\t'));
    EXPECT_FALSE(isLetterOrNumberOrUnderscore(' '));
    EXPECT_FALSE(isLetterOrNumberOrUnderscore('!'));
    EXPECT_FALSE(isLetterOrNumberOrUnderscore('~'));
    EXPECT_TRUE(isLetterOrNumberOrUnderscore('_'));
    EXPECT_TRUE(isLetterOrNumberOrUnderscore('A'));
    EXPECT_TRUE(isLetterOrNumberOrUnderscore('J'));
    EXPECT_TRUE(isLetterOrNumberOrUnderscore('Z'));
    EXPECT_TRUE(isLetterOrNumberOrUnderscore('a'));
    EXPECT_TRUE(isLetterOrNumberOrUnderscore('j'));
    EXPECT_TRUE(isLetterOrNumberOrUnderscore('z'));
    EXPECT_TRUE(isLetterOrNumberOrUnderscore('1'));
    EXPECT_TRUE(isLetterOrNumberOrUnderscore('9'));
    EXPECT_TRUE(isLetterOrNumberOrUnderscore('0'));
}

TEST(BoolCharacterStringTest, IsDisplayableCharacterWorks) {
    EXPECT_FALSE(isDisplayableCharacter('\0'));
    EXPECT_FALSE(isDisplayableCharacter('\xA'));
    EXPECT_FALSE(isDisplayableCharacter('\r'));
    EXPECT_FALSE(isDisplayableCharacter('\n'));
    EXPECT_FALSE(isDisplayableCharacter('\t'));
    EXPECT_TRUE(isDisplayableCharacter(' '));
    EXPECT_TRUE(isDisplayableCharacter('!'));
    EXPECT_TRUE(isDisplayableCharacter('~'));
    EXPECT_TRUE(isDisplayableCharacter('A'));
    EXPECT_TRUE(isDisplayableCharacter('J'));
    EXPECT_TRUE(isDisplayableCharacter('Z'));
    EXPECT_TRUE(isDisplayableCharacter('a'));
    EXPECT_TRUE(isDisplayableCharacter('j'));
    EXPECT_TRUE(isDisplayableCharacter('z'));
    EXPECT_TRUE(isDisplayableCharacter('1'));
    EXPECT_TRUE(isDisplayableCharacter('9'));
    EXPECT_TRUE(isDisplayableCharacter('0'));
}

TEST(IntegerStringTest, GenerateUniqueIdWorks) {
    string string1("Mark is the no#1 guy in the world. Mark is also the nicest guy.");
    string string2("MARK is the no#1 programmer in the world. MARK is also the nicest programmer.");
    size_t uniqueId1 = generateUniqueId(string1);
    size_t uniqueId2 = generateUniqueId(string2);
    EXPECT_EQ(10144150177413483293ULL, uniqueId1);
    EXPECT_EQ(14490909308098778163ULL, uniqueId2);
}

TEST(IntegerStringTest, GetLevenshteinDistanceWorks) {
    EXPECT_EQ(2U, getLevenshteinDistance("MOVIE", "LOVE"));
    EXPECT_EQ(1U, getLevenshteinDistance("This is a statement", "This is  statement"));
    EXPECT_EQ(1U, getLevenshteinDistance("This is a statement", "This is  statement"));
    EXPECT_EQ(4U, getLevenshteinDistance("This is a statement", "This is not a statement"));
    EXPECT_EQ(1U, getLevenshteinDistance("This is a statement", "This is b statement"));
}

TEST(IntegerStringTest, GetHammingDistanceWorks) {
    EXPECT_EQ(2U, getHammingDistance("MOVIE", "LOVE"));
    EXPECT_EQ(10U, getHammingDistance("This is a statement", "This is  statement"));
    EXPECT_EQ(10U, getHammingDistance("This is a statement", "This is  statement"));
    EXPECT_EQ(10U, getHammingDistance("This is a statement", "This is not a statement"));
    EXPECT_EQ(1U, getHammingDistance("This is a statement", "This is b statement"));
}

TEST(IntegerStringTest, GetNumberOfSubStringsWorks) {
    // For example, the substrings of ABCD are A, B, C, D, AB, BC, CD, ABC, BCD and ABCD.

    EXPECT_EQ(10U, getNumberOfSubStrings("ABCD"));
}

TEST(IntegerStringTest, GetNumberOfSubsequencesWorks) {
    // For example, the subsequences of ABCD are A, B, C, D, AB, AC, AD, BC, BD, CD, ABC, ABD, ACD, BCD and ABCD.

    EXPECT_EQ(15U, getNumberOfSubsequences("ABCD"));
}

TEST(IntegerStringTest, GetRotationValueWorks) {
    // For example, the rotations of ABCD are ABCD, BCDA, CDAB and DABC.

    EXPECT_EQ(0, getRotationValue("ABCD", "ABCD"));
    EXPECT_EQ(1, getRotationValue("ABCD", "BCDA"));
    EXPECT_EQ(2, getRotationValue("ABCD", "CDAB"));
    EXPECT_EQ(3, getRotationValue("ABCD", "DABC"));
    EXPECT_EQ(static_cast<int>(string::npos), getRotationValue("ABCD", ""));
    EXPECT_EQ(static_cast<int>(string::npos), getRotationValue("ABCD", "ABCDE"));
    EXPECT_EQ(static_cast<int>(string::npos), getRotationValue("ABCD", "AAAA"));
}

TEST(IntegerStringTest, GetPeriodValueWorks) {
    // For example, the shortest period of ABCABCA is ABC.

    EXPECT_EQ(2, getPeriodValue("ABCABCA", "ABC"));
    EXPECT_EQ(1, getPeriodValue("ABCABCA", "ABCABC"));
    EXPECT_EQ(static_cast<int>(string::npos), getPeriodValue("ABCABCA", ""));
    EXPECT_EQ(static_cast<int>(string::npos), getPeriodValue("ABCABCA", "ABCDE"));
    EXPECT_EQ(static_cast<int>(string::npos), getPeriodValue("ABCD", "AAAA"));
}

TEST(ConvertCaseFromStringTest, ConvertToCapitalLettersUsingAllLetters) {
    string testString("AbCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    EXPECT_EQ(capitalLetters, getStringWithCapitalLetters(testString));
}

TEST(ConvertCaseFromStringTest, ConvertToCapitalLettersUsingAllLettersWithSpecialCharacters) {
    string testString("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("1234567890!@#$%^&*( )ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    EXPECT_EQ(capitalLetters, getStringWithCapitalLetters(testString));
}

TEST(ConvertCaseFromStringTest, ConvertToFirstNonWhiteSpaceCharacterToCapitalWithFirstLetter) {
    string testString("abCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(capitalLetters, getStringWithFirstNonWhiteSpaceCharacterToCapital(testString));
}

TEST(ConvertCaseFromStringTest, ConvertToFirstNonWhiteSpaceCharacterToCapitalWithFirstWhiteSpaceCharacter) {
    string testString("     abCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("     AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(capitalLetters, getStringWithFirstNonWhiteSpaceCharacterToCapital(testString));
}

TEST(ConvertCaseFromStringTest, ConvertToFirstNonWhiteSpaceCharacterToCapitalWithFirstNumber) {
    string testString("1abCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("1abCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(capitalLetters, getStringWithFirstNonWhiteSpaceCharacterToCapital(testString));
}

TEST(ConvertCaseFromStringTest, ConvertToLowerCaseLettersUsingAllLettersWithSpecialCharacters) {
    string testString("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");
    string lowerCaseLetters("1234567890!@#$%^&*( )abcdefghijklmnopqrstuvwxyz");

    EXPECT_EQ(lowerCaseLetters, getStringWithLowerCaseLetters(testString));
}

TEST(ConvertUrlFromStringTest, DecodeUrlString) {
    string testString("https%3A%2F%2Fmywebsite%2Fdocs%2Fenglish%2Fsite%2Fmybook.do%3Frequest_type");
    string decodedUrl("https://mywebsite/docs/english/site/mybook.do?request_type");

    EXPECT_EQ(decodedUrl, getStringWithUrlDecodedString(testString));
}

TEST(ConvertUrlFromStringTest, DecodeUrlString2) {
    string testString("Last+Week+Tonight+with+John+Oliver-+The+IRS+%28HBO%29");
    string decodedUrl("Last+Week+Tonight+with+John+Oliver-+The+IRS+(HBO)");

    EXPECT_EQ(decodedUrl, getStringWithUrlDecodedString(testString));
}

TEST(GetPartialStringFromStringTest, GetStringThatContainsWhiteSpaceIndention) {
    string testString(
        "     \n\n1 2 3 4 5 6   7 8 9 0!@#$%^&*( )a   b   c d e f g   h i j k l m  n o   p q r\n\n\ns t u v w x y z   "
        " ");
    string whiteSpaceIndention("     \n\n");

    EXPECT_EQ(whiteSpaceIndention, getStringThatContainsWhiteSpaceIndention(testString));
}

TEST(GetPartialStringFromStringTest, GetWithoutStartingAndTrailingWhiteSpaceUsingWhiteSpaceOnly) {
    string testString("     \n\n    \t\t\t   ");
    EXPECT_TRUE(getStringWithoutStartingAndTrailingWhiteSpace(testString).empty());
}

TEST(GetPartialStringFromStringTest, GetWithoutStartingAndTrailingWhiteSpaceUsingAllLettersWithSpecialCharacters) {
    string testString(
        "     \n\n1 2 3 4 5 6   7 8 9 0!@#$%^&*( )a   b   c d e f g   h i j k l m  n o   p q r\n\n\ns t u v w x y z   "
        " ");
    string withoutStartingAndTrailingWhiteSpace(
        "1 2 3 4 5 6   7 8 9 0!@#$%^&*( )a   b   c d e f g   h i j k l m  n o   p q r\n\n\ns t u v w x y z");

    EXPECT_EQ(withoutStartingAndTrailingWhiteSpace, getStringWithoutStartingAndTrailingWhiteSpace(testString));
}

TEST(GetPartialStringFromStringTest, GetWithoutRedundantWhiteSpaceUsingAllLettersWithSpecialCharacters) {
    string testString(
        "     \n\n1 2 3 4 5 6   7 8 9 0!@#$%^&*( )a   b   c d e f g   h i j k l m  n o   p q r\n\n\ns t u v w x y z   "
        " ");
    string withoutRedundantWhiteSpace(
        "1 2 3 4 5 6 7 8 9 0!@#$%^&*( )a b c d e f g h i j k l m n o p q r s t u v w x y z");

    EXPECT_EQ(withoutRedundantWhiteSpace, getStringWithoutRedundantWhiteSpace(testString));
}

TEST(GetPartialStringFromStringTest, GetWithoutRedundantWhiteSpaceWithTabsAndNewLine) {
    string correctOutput("Mark is the no#1 guy in the world");
    EXPECT_EQ(correctOutput, getStringWithoutRedundantWhiteSpace("Mark is the no#1 guy in the world"));
    EXPECT_EQ(correctOutput, getStringWithoutRedundantWhiteSpace("    Mark    is the no#1 guy  in the     world    "));
    EXPECT_EQ(
        correctOutput, getStringWithoutRedundantWhiteSpace("Mark is\n\tthe\tno#1    \n\n\nguy\tin\r\rthe\nworld"));
}

TEST(GetPartialStringFromStringTest, GetStringWithoutQuotationsUsingAllLettersWithSpecialCharacters) {
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string withoutQuotations("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(withoutQuotations, getStringWithoutQuotations(testString));
}

TEST(GetPartialStringFromStringTest, GetStringWithoutCharacterAtTheStartUsingAllLetters) {
    string testString("_AbCDEFghIjKlMnopQRstUvWxYz");
    string withoutUnderscore("AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(withoutUnderscore, getStringWithoutCharAtTheStart(testString, '_'));
}

TEST(GetPartialStringFromStringTest, GetStringWithoutCharacterAtTheEndUsingAllLetters) {
    string testString("AbCDEFghIjKlMnopQRstUvWxYz_");
    string withoutUnderscore("AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(withoutUnderscore, getStringWithoutCharAtTheEnd(testString, '_'));
}

TEST(GetPartialStringFromStringTest, GetStringWithoutCharacterAtTheStartAndEndUsingAllLetters) {
    string testString("_AbCDEFghIjKlMnopQRstUvWxYz_");
    string withoutUnderscore("AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ(withoutUnderscore, getStringWithoutCharAtTheStartAndEnd(testString, '_'));
}

TEST(GetPartialStringFromStringTest, GetLongestCommonPrefixWorks) {
    string testString1("adjustedforever");
    string testString2("adjustedforevah");

    EXPECT_EQ("adjustedforev", getLongestCommonPrefix(testString1, testString2));
}

TEST(GetPartialStringFromStringTest, CopyBeforeStringAndAfterStringWhenStringIsFound) {
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string expectedBeforeString(R"("1234567890!@#$%^&*( ))");
    string expectedAfterString(R"(EFghIjKlMnopQRstUvWxYz")");
    string actualBeforeString;
    string actualAfterString;

    copyBeforeStringAndAfterString(testString, "AbCD", actualBeforeString, actualAfterString);
    EXPECT_EQ(expectedBeforeString, actualBeforeString);
    EXPECT_EQ(expectedAfterString, actualAfterString);
}

TEST(GetPartialStringFromStringTest, CopyBeforeStringAndAfterStringWhenStringIsNotFound) {
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string actualBeforeString;
    string actualAfterString;

    copyBeforeStringAndAfterString(testString, "777", actualBeforeString, actualAfterString);
    EXPECT_TRUE(actualBeforeString.empty());
    EXPECT_TRUE(actualBeforeString.empty());
}

TEST(GetPartialStringFromStringTest, GetStringBeforeThisStringWithCharactersAfterQuestionMarkIsRemoved) {
    string testString("http://a.mhcdn.net/store/manga/12114/001.0/compressed/r049.jpg?v=1354256522");
    string withCharactersAfterQuestionMarkRemoved("http://a.mhcdn.net/store/manga/12114/001.0/compressed/r049.jpg");
    string questionMarkString("?");

    EXPECT_EQ(withCharactersAfterQuestionMarkRemoved, getStringBeforeThisString(testString, questionMarkString));
}

TEST(GetPartialStringFromStringTest, GetStringAfterThisStringUsingAllLettersWithSpecialCharacters) {
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string stringInBetweenAtTheStart(R"(567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string stringInBetweenInTheMiddle(R"(^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");

    EXPECT_EQ(stringInBetweenAtTheStart, getStringAfterThisString(testString, R"("1234)"));
    EXPECT_EQ(stringInBetweenInTheMiddle, getStringAfterThisString(testString, "@#$%"));
    EXPECT_TRUE(getStringAfterThisString(testString, "777").empty());
}

TEST(GetPartialStringFromStringTest, GetStringInBetweenTwoStringsUsingAllLettersWithSpecialCharacters) {
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string firstString("1234567890");
    string secondString("AbCDEFghIjKlMnopQRstUvWxYz");
    string stringInBetween("!@#$%^&*( )");

    EXPECT_EQ(stringInBetween, getStringInBetweenTwoStrings(testString, firstString, secondString));
    EXPECT_TRUE(getStringInBetweenTwoStrings(testString, secondString, firstString).empty());
    EXPECT_TRUE(getStringInBetweenTwoStrings(testString, firstString, firstString).empty());
}

TEST(GetPartialStringFromStringTest, GetStringBeforeThisCharacters) {
    string testString("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_EQ("1234567890", getStringBeforeThisCharacters(testString, "$#^%@&!*"));
    EXPECT_EQ("1234567890!@#$%^&*(", getStringBeforeThisCharacters(testString, " "));
    EXPECT_TRUE(getStringBeforeThisCharacters(testString, "a").empty());
}

TEST(GetNewStringFromStringTest, GetStringReplacingSpecialCharactersWithUnderscore) {
    string testString(R"("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz")");
    string withoutSpecialCharacters("_1234567890_AbCDEFghIjKlMnopQRstUvWxYz_");

    EXPECT_EQ(withoutSpecialCharacters, getStringAndReplaceNonAlphanumericCharactersToUnderScore(testString));
}

TEST(GetNewStringFromStringTest, GetStringByRepeatingUntilDesiredLength) {
    EXPECT_TRUE(getStringByRepeatingUntilDesiredLength(string(), 50).empty());
    EXPECT_TRUE(getStringByRepeatingUntilDesiredLength("MARK", 0).empty());
    EXPECT_EQ("MARKMARK", getStringByRepeatingUntilDesiredLength("MARK", 8));
    EXPECT_EQ("MARKMARKMA", getStringByRepeatingUntilDesiredLength("MARK", 10));
}

TEST(GetNewStringFromStringTest, GetStringReplacingSpacesWithUnderscore) {
    string testString(R"( Mark Earvin Alba 1234567890 ")");
    string withoutSpecialCharacters("_Mark_Earvin_Alba_1234567890_");

    EXPECT_EQ(withoutSpecialCharacters, getStringAndReplaceNonAlphanumericCharactersToUnderScore(testString));
}

TEST(GetStringNumberFromStringTest, GetStringNumberAfterThisString) {
    EXPECT_EQ("1234", getNumberAfterThisString("INF/TCOM/R, nbccId: 1234, ", "nbccId: "));
    EXPECT_EQ("5678", getNumberAfterThisString("INF/TCOM/R, nbccId: 5678 ", "nbccId: "));
    EXPECT_EQ("7890", getNumberAfterThisString("INF/TCOM/R, nbccId: 7890", "nbccId: "));
}

TEST(GetStringNumberFromStringTest, GetStringHexNumberAfterThisString) {
    EXPECT_EQ("AFBA", getHexNumberAfterThisString("INF/TCOM/R, nbccId: AFBA, ", "nbccId: "));
    EXPECT_EQ("1234", getHexNumberAfterThisString("INF/TCOM/R, nbccId: 1234 ", "nbccId: "));
    EXPECT_EQ("AC3EB434", getHexNumberAfterThisString("INF/TCOM/R, nbccId: AC3EB434", "nbccId: "));
}

TEST(GetStringNumberFromStringTest, GetHexEquivalentOfCharacters) {
    EXPECT_EQ("4D61726B2045617276696E20416C6261", getHexEquivalentOfCharacters("Mark Earvin Alba"));
    EXPECT_EQ("FF", getHexEquivalentOfCharacters("\xff"));
}

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
TEST(GetStringFromStringTest, GetQuotedString) {
    EXPECT_EQ(
        R"("std::quoted() quotes this string and embedded \"quotes\" too")",
        getQuotedString(R"(std::quoted() quotes this string and embedded "quotes" too)"));
}
#endif

TEST(UtilitiesStringTest, ConstructFileLocator) { EXPECT_FALSE(constructFileLocator(__FILE__, __LINE__).empty()); }

TEST(UtilitiesStringTest, RandomString100Characters) {
    size_t length(100);
    EXPECT_EQ(length, getRandomAlphaNumericString(length).length());
}

TEST(UtilitiesStringTest, GetArgumentsToStringInMainWorks) {
    constexpr size_t argc = 3U;
    char const* const argv[argc] = {"parameter0", "parameter1", "parameter2"};
    EXPECT_EQ((strings{"parameter0", "parameter1", "parameter2"}), getArgumentsToStringInMain(argc, argv));
}

TEST(GetNewStringFromStringTest, FindAndReplaceStrings) {
    string string1("Mark is the no#1 guy in the world. Mark is also the nicest guy.");

    EXPECT_FALSE(transformReplaceStringIfFound(string1, "alba", "ALBA"));
    EXPECT_TRUE(transformReplaceStringIfFound(string1, "Mark", "MARK"));
    EXPECT_EQ("MARK is the no#1 guy in the world. MARK is also the nicest guy.", string1);
    EXPECT_TRUE(transformReplaceStringIfFound(string1, "guy", "programmer"));
    EXPECT_EQ("MARK is the no#1 programmer in the world. MARK is also the nicest programmer.", string1);
}

TEST(GetNewStringFromStringTest, FindAndReplaceStringsWithRedundantStrings) {
    string string1("Mark is the no#1 guy in the world. Mark is also the nicest guy.");

    EXPECT_TRUE(transformReplaceStringIfFound(string1, "M", "MMMMMMMMMMMM"));
    EXPECT_EQ("MMMMMMMMMMMMark is the no#1 guy in the world. MMMMMMMMMMMMark is also the nicest guy.", string1);
}

TEST(SplitStringTest, SplitBySpaces) {
    string string1("   Mark is the no#1      guy in the  world.    Mark is also the nicest guy.    ");
    strings expectedStrings{"Mark",   "is",   "the", "no#1", "guy", "in",     "the",
                            "world.", "Mark", "is",  "also", "the", "nicest", "guy."};
    strings actualStrings;
    splitToStrings<SplitStringType::WithoutDelimeters>(actualStrings, string1, " ");

    EXPECT_EQ(expectedStrings.size(), actualStrings.size());
    size_t size = min(expectedStrings.size(), actualStrings.size());
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(expectedStrings[i], actualStrings[i]);
    }
}

TEST(SplitStringTest, SplitBySpacesWithDelimeters) {
    string string1("   Mark is the no#1      guy in the  world.   ");
    strings expectedStrings{" ", " ", " ",   "Mark", " ",  "is", " ",   "the", " ", "no#1",   " ", " ", " ", " ",
                            " ", " ", "guy", " ",    "in", " ",  "the", " ",   " ", "world.", " ", " ", " "};
    strings actualStrings;
    splitToStrings<SplitStringType::WithDelimeters>(actualStrings, string1, " ");

    EXPECT_EQ(expectedStrings.size(), actualStrings.size());
    size_t size = min(expectedStrings.size(), actualStrings.size());
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(expectedStrings[i], actualStrings[i]);
    }
}

TEST(SplitStringTest, SplitLinesToAchieveTargetLengthWorksWithLargeTargetLength) {
    string string1("   Mark is the no#1      guy in the  world.   ThisIsALongString");
    strings expectedStrings{"   Mark is", " the no#1 ", "     guy ", "in the  ", "world.   ", "ThisIsALongString"};
    strings actualStrings;
    const int targetLength = 10;

    splitLinesToAchieveTargetLength(actualStrings, string1, targetLength);

    EXPECT_EQ(expectedStrings.size(), actualStrings.size());
    size_t size = min(expectedStrings.size(), actualStrings.size());
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(expectedStrings[i], actualStrings[i]);
    }
}

TEST(SplitStringTest, SplitLinesToAchieveTargetLengthWorks_LastLineIsIncluded) {
    string string1("TupcIlm starts when its deployed on board 0x1011 (same with legacy Aalman)");
    strings expectedStrings{"TupcIlm starts when its deployed", " on board 0x1011 (same with ", "legacy Aalman)"};
    strings actualStrings;
    const int targetLength = 30;

    splitLinesToAchieveTargetLength(actualStrings, string1, targetLength);

    EXPECT_EQ(expectedStrings.size(), actualStrings.size());
    size_t size = min(expectedStrings.size(), actualStrings.size());
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(expectedStrings[i], actualStrings[i]);
    }
}

TEST(SplitStringTest, SplitLinesToAchieveTargetLengthCanBeSplitPerCharacter) {
    string string1("   Mark is the no#1      ");
    strings expectedStrings{" ", " ", " ", "Mark", " ", "is", " ", "the", " ", "no#1", " ", " ", " ", " ", " ", " "};
    strings actualStrings;
    const int targetLength = 1;

    splitLinesToAchieveTargetLength(actualStrings, string1, targetLength);

    EXPECT_EQ(expectedStrings.size(), actualStrings.size());
    size_t size = min(expectedStrings.size(), actualStrings.size());
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(expectedStrings[i], actualStrings[i]);
    }
}

TEST(SplitStringTest, SplitToStringsUsingASeriesOfDelimetersWorks) {
    string string1(R"(TLH_DEBUG_PRINT("Creating new licence entry in DB for featureCode: %d.", featureCode);)");
    strings delimeters{R"((")", R"(",)", ");"};
    strings expectedStrings{
        "TLH_DEBUG_PRINT", R"(Creating new licence entry in DB for featureCode: %d.)", " featureCode"};
    strings actualStrings;
    splitToStringsUsingASeriesOfDelimeters(actualStrings, string1, delimeters);

    EXPECT_EQ(expectedStrings.size(), actualStrings.size());
    size_t size = min(expectedStrings.size(), actualStrings.size());
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(expectedStrings[i], actualStrings[i]);
    }
}

TEST(BasicStringVariantTest, IsBasicStringVariantWorks) {
    EXPECT_TRUE(isBasicStringVariant<string>());
    EXPECT_TRUE(isBasicStringVariant<wstring>());
    EXPECT_TRUE(isBasicStringVariant<u16string>());
    EXPECT_TRUE(isBasicStringVariant<u32string>());
    EXPECT_FALSE(isBasicStringVariant<int>());
}

TEST(BasicStringVariantTest, ConvertToAnotherBasicStringVariantWorks) {
    EXPECT_EQ(
        "ThisABasicStringVariant",
        (convertToAnotherBasicStringVariant<string, string>(R"delimeter(ThisABasicStringVariant)delimeter")));
    EXPECT_EQ(
        L"ThisABasicStringVariant"s, (convertToAnotherBasicStringVariant<string, wstring>("ThisABasicStringVariant"s)));
    EXPECT_EQ(
        u"ThisABasicStringVariant"s,
        (convertToAnotherBasicStringVariant<string, u16string>("ThisABasicStringVariant"s)));
    EXPECT_EQ(
        U"ThisABasicStringVariant"s,
        (convertToAnotherBasicStringVariant<string, u32string>("ThisABasicStringVariant"s)));
    EXPECT_EQ(
        "ThisABasicStringVariant"s, (convertToAnotherBasicStringVariant<wstring, string>(L"ThisABasicStringVariant"s)));
    EXPECT_EQ(
        "ThisABasicStringVariant"s,
        (convertToAnotherBasicStringVariant<u16string, string>(u"ThisABasicStringVariant"s)));
    EXPECT_EQ(
        "ThisABasicStringVariant"s,
        (convertToAnotherBasicStringVariant<u32string, string>(U"ThisABasicStringVariant"s)));
    EXPECT_EQ(
        "ThisABasicStringVariant"s,
        (convertToAnotherBasicStringVariant<string, string>(
            u8"ThisABasicStringVariant"s)));  // UTF-8 encoded (UTF-8 is backwards compatible with ASCII)
    EXPECT_EQ(
        u8"ThisABasicStringVariant"s,
        (convertToAnotherBasicStringVariant<string, string>(
            "ThisABasicStringVariant"s)));  // UTF-8 encoded (UTF-8 is backwards compatible with ASCII)
}

TEST(CombineStringTest, CombinedStringsWithComma) {
    strings stringsToCombine{"Mark",   "is",   "the", "no#1", "guy", "in",     "the",
                             "world.", "Mark", "is",  "also", "the", "nicest", "guy."};
    string expectedString("Mark,is,the,no#1,guy,in,the,world.,Mark,is,also,the,nicest,guy.");
    string actualString(combineStrings(stringsToCombine, ","));

    EXPECT_EQ(expectedString, actualString);
}

TEST(GetStringWithAlignmentFromStringTest, GetStringUsingJustifyAlignment) {
    EXPECT_EQ("                        M                         ", getStringWithJustifyAlignment("M", 50));
    EXPECT_EQ("         M         a         r         k          ", getStringWithJustifyAlignment("Mark", 50));
    EXPECT_EQ(
        "Mark        Earvin        Alba        1234567890  ",
        getStringWithJustifyAlignment("Mark Earvin Alba 1234567890", 50));
    EXPECT_EQ("Mark Earvin Alba 1234567890", getStringWithJustifyAlignment("Mark Earvin Alba 1234567890", 1));
    EXPECT_EQ("                                                  ", getStringWithJustifyAlignment(string(), 50));
}

TEST(GetStringWithAlignmentFromStringTest, GetStringUsingCenterAlignment) {
    EXPECT_EQ("                       Mark                       ", getStringWithCenterAlignment("Mark", 50));
    EXPECT_EQ(
        "           Mark Earvin Alba 1234567890            ",
        getStringWithCenterAlignment("Mark Earvin Alba 1234567890", 50));
    EXPECT_EQ("Mark Earvin Alba 1234567890", getStringWithCenterAlignment("Mark Earvin Alba 1234567890", 1));
    EXPECT_EQ("                                                  ", getStringWithCenterAlignment(string(), 50));
}

TEST(GetStringWithAlignmentFromStringTest, GetStringUsingRightAlignment) {
    EXPECT_EQ("                                              Mark", getStringWithRightAlignment("Mark", 50));
    EXPECT_EQ(
        "                       Mark Earvin Alba 1234567890",
        getStringWithRightAlignment("Mark Earvin Alba 1234567890", 50));
    EXPECT_EQ("Mark Earvin Alba 1234567890", getStringWithRightAlignment("Mark Earvin Alba 1234567890", 1));
    EXPECT_EQ("                                                  ", getStringWithRightAlignment(string(), 50));
}

TEST(GetStringWithAlignmentFromStringTest, GetStringUsingLeftAlignment) {
    EXPECT_EQ("Mark                                              ", getStringWithLeftAlignment("Mark", 50));
    EXPECT_EQ(
        "Mark Earvin Alba 1234567890                       ",
        getStringWithLeftAlignment("Mark Earvin Alba 1234567890", 50));
    EXPECT_EQ("Mark Earvin Alba 1234567890", getStringWithLeftAlignment("Mark Earvin Alba 1234567890", 1));
    EXPECT_EQ("                                                  ", getStringWithLeftAlignment(string(), 50));
}

TEST(GetNewStringFromStringTest, GetStringWithoutRedundantSlashesUsingAllLettersWithSpecialCharacters) {
    string testString(R"(////DIR1\\/\\/\\/DIR2\\\\DIR3///DIR4\\\\//DIR5////\\\\)");
    string withoutRedundantSlashes(R"(\DIR1\DIR2\DIR3\DIR4\DIR5\)");

    EXPECT_EQ(withoutRedundantSlashes, getCorrectPathWithReplacedSlashCharacters(testString, R"(\)"));
}

TEST(GetNewStringFromStringTest, GetStringWithoutRedundantPeriodInPathUsingAllLettersWithSpecialCharacters) {
    string testString(R"(\DIR1\DIR2\..\DIR3\DIR4\..\..\DIR5\)");
    string withoutRedundantPeriodInPath(R"(\DIR1\DIR5\)");

    EXPECT_EQ(withoutRedundantPeriodInPath, getCorrectPathWithoutDoublePeriod(testString, R"(\)"));
}

TEST(GetNewStringFromStringTest, GetStringBeforeDoublePeriodInPathUsingAllLettersWithSpecialCharacters) {
    string testString(R"(\DIR1\DIR2\..\DIR3\DIR4\..\..\DIR5\)");
    string beforeDoublePeriod(R"(DIR5\)");

    EXPECT_EQ(beforeDoublePeriod, getStringBeforeDoublePeriod(testString, R"(\)"));
}

TEST(GetNewStringFromStringTest, GetStringBeforeDoublePeriodInPathUsingNoDoublePeriodInput) {
    string testString(R"(\DIR1\DIR2\DIR3\DIR4\DIR5\)");
    string beforeDoublePeriod(R"(\DIR1\DIR2\DIR3\DIR4\DIR5\)");

    EXPECT_EQ(beforeDoublePeriod, getStringBeforeDoublePeriod(testString, R"(\)"));
}

TEST(GetNewStringFromStringTest, GetImmediateDirectoryNameUsingLastCharacterIsSlash) {
    string testString(R"(\DIR1\DIR2\DIR3\DIR4\DIR5\)");
    string immediateDirectoryName("DIR5");

    EXPECT_EQ(immediateDirectoryName, getImmediateDirectoryName(testString, R"(\)"));
}

TEST(GetNewStringFromStringTest, GetImmediateDirectoryNameUsingLastCharacterIsNotSlash) {
    string testString(R"(\DIR1\DIR2\DIR3\DIR4\DIR5)");
    string immediateDirectoryName("DIR5");

    EXPECT_EQ(immediateDirectoryName, getImmediateDirectoryName(testString, R"(\)"));
}

TEST(BooleanStringTest, IsNumberTest) {
    string testString1("AbCDEFghIjKlMnopQRstUvWxYz");
    string testString2("AbCD1234567890!@#$%^&*( )");
    string testString3("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_FALSE(isNumber(testString1));
    EXPECT_TRUE(isNumber(testString2));
    EXPECT_TRUE(isNumber(testString3));
}

TEST(BooleanStringTest, IsWhiteSpaceTest) {
    string testString1("   AbCDEFghIjKlMnopQRstUvWxYz  ");
    string testString2("       ");
    string testString3("   \n\n    \t\t\t\t");

    EXPECT_FALSE(isWhiteSpace(testString1));
    EXPECT_TRUE(isWhiteSpace(testString2));
    EXPECT_TRUE(isWhiteSpace(testString3));
}

TEST(BooleanStringTest, IsIdentifierTest) {
    string testString1("   AbCDEFghIjKlMnopQRstUvWxYz  ");
    string testString2("   \n\n    \t\t\t\t");
    string testString3("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");
    string testString4("abc1234");
    string testString5("_abc1234");

    EXPECT_FALSE(isIdentifier(testString1));
    EXPECT_FALSE(isIdentifier(testString2));
    EXPECT_FALSE(isIdentifier(testString3));
    EXPECT_TRUE(isIdentifier(testString4));
    EXPECT_TRUE(isIdentifier(testString5));
}

TEST(BooleanStringTest, IsOneWordTest) {
    string testString1("   AbCDEFghIjKlMnopQRstUvWxYz  ");
    string testString2("   \n\n    \t\t\t\t");
    string testString3("AbCDE FghIj KlM nopQR stU vWx Yz");
    string testString4("AbCDEFghIjKlMnopQRstUvWxYz1234567890!@#$%^&*()");
    string testString5;

    EXPECT_FALSE(isOneWord(testString1));
    EXPECT_FALSE(isOneWord(testString2));
    EXPECT_FALSE(isOneWord(testString3));
    EXPECT_TRUE(isOneWord(testString4));
    EXPECT_FALSE(isOneWord(testString5));
}

TEST(BooleanStringTest, IsPalindromeTest) {
    EXPECT_FALSE(isPalindrome(string()));
    EXPECT_TRUE(isPalindrome("abcba"));
    EXPECT_TRUE(isPalindrome("abba"));
    EXPECT_FALSE(isPalindrome("abca"));
}

TEST(BooleanStringTest, IsSubstringTest) {
    // For example, the substrings of ABCD are A, B, C, D, AB, BC, CD, ABC, BCD and ABCD.

    EXPECT_TRUE(isSubstring("ABCD", "A"));
    EXPECT_TRUE(isSubstring("ABCD", "B"));
    EXPECT_TRUE(isSubstring("ABCD", "C"));
    EXPECT_TRUE(isSubstring("ABCD", "D"));
    EXPECT_TRUE(isSubstring("ABCD", "AB"));
    EXPECT_TRUE(isSubstring("ABCD", "BC"));
    EXPECT_TRUE(isSubstring("ABCD", "CD"));
    EXPECT_TRUE(isSubstring("ABCD", "ABC"));
    EXPECT_TRUE(isSubstring("ABCD", "BCD"));
    EXPECT_TRUE(isSubstring("ABCD", "ABCD"));
    EXPECT_TRUE(isSubstring("ABCD", ""));  // null strings are considered
    EXPECT_FALSE(isSubstring("ABCD", "ABCDE"));
}

TEST(BooleanStringTest, IsSubsequenceTest) {
    // For example, the subsequences of ABCD are A, B, C, D, AB, AC, AD, BC, BD, CD, ABC, ABD, ACD, BCD and ABCD.

    EXPECT_TRUE(isSubsequence("ABCD", "A"));
    EXPECT_TRUE(isSubsequence("ABCD", "B"));
    EXPECT_TRUE(isSubsequence("ABCD", "C"));
    EXPECT_TRUE(isSubsequence("ABCD", "D"));
    EXPECT_TRUE(isSubsequence("ABCD", "AB"));
    EXPECT_TRUE(isSubsequence("ABCD", "AC"));
    EXPECT_TRUE(isSubsequence("ABCD", "AD"));
    EXPECT_TRUE(isSubsequence("ABCD", "BC"));
    EXPECT_TRUE(isSubsequence("ABCD", "BD"));
    EXPECT_TRUE(isSubsequence("ABCD", "CD"));
    EXPECT_TRUE(isSubsequence("ABCD", "ABC"));
    EXPECT_TRUE(isSubsequence("ABCD", "ABD"));
    EXPECT_TRUE(isSubsequence("ABCD", "ACD"));
    EXPECT_TRUE(isSubsequence("ABCD", "BCD"));
    EXPECT_TRUE(isSubsequence("ABCD", "ABCD"));
    EXPECT_TRUE(isSubsequence("ABCD", ""));  // null strings are considered
    EXPECT_FALSE(isSubsequence("ABCD", "ABCDE"));
    EXPECT_FALSE(isSubsequence("ABCD", "BA"));
}

TEST(BooleanStringTest, IsPrefixTest) {
    // For example, the prefixes of ABCD are A, AB, ABC and ABCD.

    EXPECT_TRUE(isPrefix("ABCD", "A"));
    EXPECT_TRUE(isPrefix("ABCD", "AB"));
    EXPECT_TRUE(isPrefix("ABCD", "ABC"));
    EXPECT_TRUE(isPrefix("ABCD", "ABCD"));
    EXPECT_TRUE(isPrefix("ABCD", ""));  // null strings are considered
    EXPECT_FALSE(isPrefix("ABCD", "ABCDE"));
    EXPECT_FALSE(isPrefix("ABCD", "BA"));
}

TEST(BooleanStringTest, IsSuffixTest) {
    // For example, the suffixes of ABCD are D, CD, BCD and ABCD.

    EXPECT_TRUE(isSuffix("ABCD", "D"));
    EXPECT_TRUE(isSuffix("ABCD", "CD"));
    EXPECT_TRUE(isSuffix("ABCD", "BCD"));
    EXPECT_TRUE(isSuffix("ABCD", "ABCD"));
    EXPECT_TRUE(isSuffix("ABCD", ""));  // null strings are considered
    EXPECT_FALSE(isSuffix("ABCD", "1ABCD"));
    EXPECT_FALSE(isSuffix("ABCD", "DC"));
}

TEST(BooleanStringTest, IsRotationTest) {
    // For example, the rotations of ABCD are ABCD, BCDA, CDAB and DABC.

    EXPECT_TRUE(isRotation("ABCD", "ABCD"));
    EXPECT_TRUE(isRotation("ABCD", "BCDA"));
    EXPECT_TRUE(isRotation("ABCD", "CDAB"));
    EXPECT_TRUE(isRotation("ABCD", "DABC"));
    EXPECT_FALSE(isRotation("ABCD", ""));  // null strings are NOT considered
    EXPECT_FALSE(isRotation("ABCD", "ABCDE"));
    EXPECT_FALSE(isRotation("ABCD", "AAAA"));
}

TEST(IntegerStringTest, IsPeriodWorks) {
    // For example, the shortest period of ABCABCA is ABC.

    EXPECT_TRUE(isPeriod("ABCABCA", "ABC"));
    EXPECT_TRUE(isPeriod("ABCABCA", "ABCABC"));
    EXPECT_FALSE(isPeriod("ABCABCA", ""));  // null strings are NOT considered
    EXPECT_FALSE(isPeriod("ABCABCA", "ABCDE"));
    EXPECT_FALSE(isPeriod("ABCD", "AAAA"));
}

TEST(IntegerStringTest, IsBorderWorks) {
    // For example, the borders of ABACABA are A, ABA and ABACABA.

    EXPECT_TRUE(isBorder("ABACABA", "A"));
    EXPECT_TRUE(isBorder("ABACABA", "ABA"));
    EXPECT_TRUE(isBorder("ABACABA", ""));
    EXPECT_FALSE(isBorder("ABACABA", "AB"));
    EXPECT_FALSE(isBorder("ABACABA", "ABCDE"));
    EXPECT_FALSE(isBorder("ABCD", "AAAA"));
}

TEST(BooleanStringTest, StringCompareNotCaseSensitive) {
    string testString("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");
    string capitalLetters("1234567890!@#$%^&*( )abcdEFghijklMnOPQRstUvWxYz");

    EXPECT_TRUE(isEqualNotCaseSensitive(testString, capitalLetters));
}

TEST(BooleanStringTest, StringCompareWithLowestCommonLength) {
    string testString1("1234567890!@#$%^&*( )AbCD");
    string testString2("1234567890!@#$%^&*( )AbCDEFghIjKlMnopQRstUvWxYz");

    EXPECT_TRUE(isEqualWithLowestCommonLength(testString1, testString2));
    EXPECT_TRUE(isEqualWithLowestCommonLength(testString2, testString1));
}

TEST(BooleanStringTest, isStringFoundCaseSensitiveWithLettersOnly) {
    string longString("Mark is the no#1 guy in the world");

    EXPECT_FALSE(isStringFoundCaseSensitive(longString, "mark"));
    EXPECT_TRUE(isStringFoundCaseSensitive(longString, "Mark"));
}

TEST(BooleanStringTest, isStringFoundCaseSensitiveWithLettersAndNumbersAndSpecialCharacters) {
    string longString("Mark is the no#1 guy in the world");

    EXPECT_FALSE(isStringFoundCaseSensitive(longString, "nO#1"));
    EXPECT_TRUE(isStringFoundCaseSensitive(longString, "no#1"));
}

TEST(BooleanStringTest, isStringFoundCaseSensitiveWithSameLength) {
    string longString("Attribute = ");

    EXPECT_FALSE(isStringFoundCaseSensitive(longString, "aTTRIBUTE = "));
    EXPECT_TRUE(isStringFoundCaseSensitive(longString, "Attribute = "));
}

TEST(BooleanStringTest, isStringFoundCaseSensitiveWithRunningIndex) {
    string longString("Mark is the no#1 guy in the world");

    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(longString, "Mark", runningIndex));
    EXPECT_FALSE(isStringFoundCaseSensitive(longString, "Mark", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(longString, "no#1", runningIndex));
    EXPECT_FALSE(isStringFoundCaseSensitive(longString, "no#1", runningIndex));
    EXPECT_FALSE(isStringFoundCaseSensitive(longString, "Mark", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(longString, "world", runningIndex));
    EXPECT_FALSE(isStringFoundCaseSensitive(longString, "world", runningIndex));
}

TEST(BooleanStringTest, isStringFoundNotCaseSensitiveWithLettersOnly) {
    string longString("Mark is the no#1 guy in the world");

    EXPECT_TRUE(isStringFoundNotCaseSensitive(longString, "mark"));
    EXPECT_TRUE(isStringFoundNotCaseSensitive(longString, "Mark"));
}

TEST(BooleanStringTest, isStringFoundNotCaseSensitiveWithLettersAndNumbersAndSpecialCharacters) {
    string longString("Mark is the no#1 guy in the world");

    EXPECT_TRUE(isStringFoundNotCaseSensitive(longString, "nO#1"));
    EXPECT_TRUE(isStringFoundNotCaseSensitive(longString, "no#1"));
}

TEST(BooleanStringTest, IsWildcardMatchTest) {
    EXPECT_TRUE(isWildcardMatch("alba", "a*ba"));
    EXPECT_TRUE(isWildcardMatch("albaisthebest", "al?ba*"));
    EXPECT_FALSE(isWildcardMatch("alba", "a*m"));
    EXPECT_FALSE(isWildcardMatch("markalba", "*mark"));
    EXPECT_TRUE(isWildcardMatch("markisthebest", "mark*best"));
    EXPECT_FALSE(isWildcardMatch("alba", "alb*b?a"));
    EXPECT_TRUE(isWildcardMatch("alba", "*l*a"));
    EXPECT_TRUE(isWildcardMatch("alba", "*?l*a"));
}

TEST(ConvertFromStringTest, ConvertStringToBool) {
    EXPECT_TRUE(convertStringToBool("true"));
    EXPECT_FALSE(convertStringToBool("false"));
    EXPECT_TRUE(convertStringToBool("TruE"));
    EXPECT_FALSE(convertStringToBool("fAlse"));
    EXPECT_FALSE(convertStringToBool("0"));
    EXPECT_FALSE(convertStringToBool("00000"));
    EXPECT_TRUE(convertStringToBool("1"));
    EXPECT_TRUE(convertStringToBool("-892347589"));
    EXPECT_FALSE(convertStringToBool("this is a random string"));
}

TEST(ConvertFromStringTest, ConvertStringToIntegerWithNumbersOnly) {
    EXPECT_EQ(0, convertStringToNumber<int>("this is a random string"));
    EXPECT_EQ(12345, convertStringToNumber<int>("12345"));
    EXPECT_EQ(-67890, convertStringToNumber<int>("-67890"));
    EXPECT_EQ(67890, convertStringToNumber<int>("--67890"));
    EXPECT_EQ(67890, convertStringToNumber<int>("--67-890"));
    EXPECT_EQ(67890, convertStringToNumber<int>("0--67-890"));
}

TEST(ConvertFromStringTest, ConvertStringToIntegerWithNumbersAndLettersAndSpecialCharacters) {
    EXPECT_EQ(12345, convertStringToNumber<int>("1a2l3b4a5"));
    EXPECT_EQ(12345, convertStringToNumber<int>("12345.6789"));
    EXPECT_EQ(0, convertStringToNumber<int>("a&-.6$7*8(9)0"));
    EXPECT_EQ(6, convertStringToNumber<int>("$@!-a-a6.78)9(0"));
    EXPECT_EQ(6, convertStringToNumber<int>(")(*&^%$--6(*&.^%7-89(*&^%0"));
}

TEST(ConvertFromStringTest, ConvertStringToDoubleWithNumbersOnly) {
    EXPECT_DOUBLE_EQ(12345.6789, convertStringToNumber<double>("12345.6789"));
    EXPECT_DOUBLE_EQ(-67890.1111, convertStringToNumber<double>("-67890.1111"));
    EXPECT_DOUBLE_EQ(67890.12345, convertStringToNumber<double>("--67890.12345"));
    EXPECT_DOUBLE_EQ(67890.9999999, convertStringToNumber<double>("--67-890.9999999"));
    EXPECT_DOUBLE_EQ(67890.67890, convertStringToNumber<double>("0--67-890. 67890"));
}

TEST(ConvertFromStringTest, ConvertStringToDoubleWithNumbersAndLettersAndSpecialCharacters) {
    EXPECT_DOUBLE_EQ(12345.6789, convertStringToNumber<double>("12l3^s45.67l$89"));
    EXPECT_DOUBLE_EQ(-67890.1111, convertStringToNumber<double>("-67s8*a9s0.1s11d1"));
    EXPECT_DOUBLE_EQ(67890.12345, convertStringToNumber<double>("--6d&7sd8s90.12345"));
    EXPECT_DOUBLE_EQ(67890.9999999, convertStringToNumber<double>("--6s7-8$f90.9d9*99$999"));
    EXPECT_DOUBLE_EQ(67890.67890, convertStringToNumber<double>("0--67-j 8#9j0.678& dk90"));
}

TEST(ConvertFromStringTest, HexConvertStringToIntegerWithNumbersOnly) {
    EXPECT_EQ(0x12345, convertHexStringToNumber<int>("12345"));
    EXPECT_EQ(0xABCDE, convertHexStringToNumber<int>("ABCDE"));
    EXPECT_EQ(0x1A2B3, convertHexStringToNumber<int>("1A2B3"));
    EXPECT_EQ(0xA1B2C, convertHexStringToNumber<int>("A1B2C"));
    EXPECT_EQ(0xA1B2C, convertHexStringToNumber<int>("xxxA#$%1 @#$#@B ^&*&^2%^&%^C*(&"));
}

TEST(ConvertFromStringTest, ConvertStringToDoubleWithAlbaNumber) {
    AlbaNumber numberToVerify1(convertStringToAlbaNumber("12345"));
    AlbaNumber numberToVerify2(convertStringToAlbaNumber("12345.6789"));

    EXPECT_EQ(AlbaNumber::Type::Integer, numberToVerify1.getType());
    EXPECT_EQ(12345, numberToVerify1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, numberToVerify2.getType());
    EXPECT_DOUBLE_EQ(12345.6789, numberToVerify2.getDouble());
}

TEST(ConvertToStringTest, ConvertBoolToStringWorks) {
    EXPECT_EQ("true", convertBoolToString(true));
    EXPECT_EQ("false", convertBoolToString(false));
}

TEST(ConvertToStringTest, ConvertNumberToString) {
    EXPECT_EQ("12345", convertToString(12345));
    EXPECT_EQ("12345.7", convertToString(12345.6789));
    EXPECT_EQ("-67890.1", convertToString(-67890.1111));
    EXPECT_EQ("(8/3)", convertToString(AlbaNumber::createFraction(8, 3)));
}

TEST(StringConverterWithFormattingTest, ConvertNumberToStringWithDefaultParameters) {
    StringConverterWithFormatting converter;

    EXPECT_EQ("12345", converter.convertToString(12345));
    EXPECT_EQ("12345.7", converter.convertToString(12345.6789));
    EXPECT_EQ("-67890.1", converter.convertToString(-67890.1111));
    EXPECT_EQ("(8/3)", converter.convertToString(AlbaNumber::createFraction(8, 3)));
}

TEST(StringConverterWithFormattingTest, ConvertNumberToStringWithUnderPrecision) {
    StringConverterWithFormatting converter;
    converter.setPrecision(8);

    EXPECT_EQ("12345", converter.convertToString(12345));
    EXPECT_EQ("12345.679", converter.convertToString(12345.6789));
    EXPECT_EQ("-67890.111", converter.convertToString(-67890.1111));
    EXPECT_EQ("(8/3)", converter.convertToString(AlbaNumber::createFraction(8, 3)));
}

TEST(StringConverterWithFormattingTest, ConvertNumberToStringWithOverPrecision) {
    StringConverterWithFormatting converter;
    converter.setPrecision(15);

    EXPECT_EQ("12345", converter.convertToString(12345));
    EXPECT_EQ("12345.6789", converter.convertToString(12345.6789));
    EXPECT_EQ("-67890.1111", converter.convertToString(-67890.1111));
    EXPECT_EQ("(8/3)", converter.convertToString(AlbaNumber::createFraction(8, 3)));
}

TEST(StringConverterWithFormattingTest, ConvertNumberToStringWithFloatOutputType) {
    StringConverterWithFormatting converter;
    converter.setPrecision(15);

    converter.setFloatOutputType(StringConverterWithFormatting::FloatOutputType::Default);
    EXPECT_EQ("12345", converter.convertToString(12345));
    EXPECT_EQ("12345.6789", converter.convertToString(12345.6789));
    EXPECT_EQ("-67890.1111", converter.convertToString(-67890.1111));
    EXPECT_EQ("(8/3)", converter.convertToString(AlbaNumber::createFraction(8, 3)));

    converter.setFloatOutputType(StringConverterWithFormatting::FloatOutputType::Fixed);
    EXPECT_EQ("12345", converter.convertToString(12345));
    EXPECT_EQ("12345.678900000000795", converter.convertToString(12345.6789));
    EXPECT_EQ("-67890.111099999994622", converter.convertToString(-67890.1111));
    EXPECT_EQ("(8/3)", converter.convertToString(AlbaNumber::createFraction(8, 3)));

    converter.setFloatOutputType(StringConverterWithFormatting::FloatOutputType::HexFloat);
    EXPECT_EQ("12345", converter.convertToString(12345));
    // EXPECT_EQ("0xc.0e6b7318fc508p+10", converter.convertToString(12345.6789)); // varies across machines
    // EXPECT_EQ("-0x8.4990e38865948p+13", converter.convertToString(-67890.1111)); // varies across machines
    EXPECT_EQ("(8/3)", converter.convertToString(AlbaNumber::createFraction(8, 3)));

    converter.setFloatOutputType(StringConverterWithFormatting::FloatOutputType::Scientific);
    EXPECT_EQ("12345", converter.convertToString(12345));
    EXPECT_EQ("1.234567890000000e+04", converter.convertToString(12345.6789));
    EXPECT_EQ("-6.789011109999999e+04", converter.convertToString(-67890.1111));
    EXPECT_EQ("(8/3)", converter.convertToString(AlbaNumber::createFraction(8, 3)));
}

TEST(StringConverterWithFormattingTest, ConvertNumberToStringWithLessFieldWidth) {
    StringConverterWithFormatting converter;
    converter.setPrecision(15);
    converter.setFieldWidth(3);

    EXPECT_EQ("12345", converter.convertToString(12345));
    EXPECT_EQ("12345.6789", converter.convertToString(12345.6789));
    EXPECT_EQ("-67890.1111", converter.convertToString(-67890.1111));
    EXPECT_EQ("  (8/3)", converter.convertToString(AlbaNumber::createFraction(8, 3)));
}

TEST(StringConverterWithFormattingTest, ConvertNumberToStringWithMoreFieldWidth) {
    StringConverterWithFormatting converter;
    converter.setPrecision(15);
    converter.setFieldWidth(15);

    EXPECT_EQ("          12345", converter.convertToString(12345));
    EXPECT_EQ("     12345.6789", converter.convertToString(12345.6789));
    EXPECT_EQ("    -67890.1111", converter.convertToString(-67890.1111));
    EXPECT_EQ("              (8/3)", converter.convertToString(AlbaNumber::createFraction(8, 3)));
}

TEST(StringConverterWithFormattingTest, ConvertNumberToStringWithFillCharacter) {
    StringConverterWithFormatting converter;
    converter.setPrecision(15);
    converter.setFieldWidth(15);
    converter.setFillCharacter('0');

    EXPECT_EQ("000000000012345", converter.convertToString(12345));
    EXPECT_EQ("0000012345.6789", converter.convertToString(12345.6789));
    EXPECT_EQ("0000-67890.1111", converter.convertToString(-67890.1111));
    EXPECT_EQ("00000000000000(8/3)", converter.convertToString(AlbaNumber::createFraction(8, 3)));
}

TEST(StringConverterWithFormattingTest, ConvertNumberToStringWithMaximumLength) {
    StringConverterWithFormatting converter;
    converter.setMaximumLength(5);

    EXPECT_EQ("12345", converter.convertToString(1234567890));
}

}  // namespace alba
