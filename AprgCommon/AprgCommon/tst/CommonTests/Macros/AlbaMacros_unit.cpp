#include <Common/Macros/AlbaMacros.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {
TEST(AlbaMacrosTest, StandardPredefinedMacrosWorks) {
    EXPECT_FALSE(string(ALBA_MACROS_GET_FILE).empty());
    EXPECT_EQ(13, ALBA_MACROS_GET_LINE);
    EXPECT_FALSE(string(ALBA_MACROS_GET_COMPILATION_DATE).empty());
    EXPECT_FALSE(string(ALBA_MACROS_GET_TIME_OF_TRANSLATION).empty());
    EXPECT_LT(201100, ALBA_MACROS_GET_COMPILER_VERSION);  // it should be above 2011 compiler
}

TEST(AlbaMacrosTest, CompilerSpecificPredefinedMacrosWorks) {
    EXPECT_EQ("TestBody", string(ALBA_MACROS_GET_FUNCTION));
    EXPECT_EQ(
        "virtual void alba::AlbaMacrosTest_CompilerSpecificPredefinedMacrosWorks_Test::TestBody()",
        string(ALBA_MACROS_GET_PRETTY_FUNCTION));
    EXPECT_EQ(0, ALBA_MACROS_GET_UNIQUE_COUNTER_VALUE);
    EXPECT_EQ(1, ALBA_MACROS_GET_UNIQUE_COUNTER_VALUE);
    EXPECT_EQ(2, ALBA_MACROS_GET_UNIQUE_COUNTER_VALUE);
    EXPECT_EQ(3, ALBA_MACROS_GET_UNIQUE_COUNTER_VALUE);
}

TEST(AlbaMacrosTest, DisplayMessageTest) {
#define ALBA_MACROS_TEST_SAMPLE_MACRO1 10000
    EXPECT_EQ(
        "ALBA_MACROS_TEST_SAMPLE_MACRO1=10000",
        ALBA_MACROS_PARAMETER_FOR_PRAGMA_MESSAGE(ALBA_MACROS_TEST_SAMPLE_MACRO1));
#pragma message(ALBA_MACROS_PARAMETER_FOR_PRAGMA_MESSAGE(ALBA_MACROS_TEST_SAMPLE_MACRO1))
}

TEST(AlbaMacrosTest, GetStringLiteralWorks) {
    enum class SampleEnumClass { Type1, Type2 };

    EXPECT_EQ("12345", ALBA_MACROS_GET_STRING_LITERAL(12345));
    EXPECT_EQ("SampleEnumClass::Type1", ALBA_MACROS_GET_STRING_LITERAL(SampleEnumClass::Type1));
    EXPECT_EQ("SampleEnumClass::Type2", ALBA_MACROS_GET_STRING_LITERAL(SampleEnumClass::Type2));
}

TEST(AlbaMacrosTest, CaseEnumStringWorks) {
    enum class SampleEnumClass { Type1, Type2 };
    struct SampleClass {
        string getString(SampleEnumClass const enumValue) {
            switch (enumValue) {
                ALBA_MACROS_CASE_ENUM_STRING(SampleEnumClass::Type1)
                ALBA_MACROS_CASE_ENUM_STRING(SampleEnumClass::Type2)
                default:
                    return "default";
            }
        }
    };
    SampleEnumClass enumValue1 = SampleEnumClass::Type1;
    SampleEnumClass enumValue2 = SampleEnumClass::Type2;

    SampleClass sampleObject;
    EXPECT_EQ("SampleEnumClass::Type1", sampleObject.getString(enumValue1));
    EXPECT_EQ("SampleEnumClass::Type2", sampleObject.getString(enumValue2));
}

TEST(AlbaMacrosTest, CaseEnumShortStringWorks) {
    enum class SampleEnumClass { Type1, Type2 };
    struct SampleClass {
        string getString(SampleEnumClass const enumValue) {
            switch (enumValue) {
                ALBA_MACROS_CASE_ENUM_SHORT_STRING(SampleEnumClass::Type1, "Type1")
                ALBA_MACROS_CASE_ENUM_SHORT_STRING(SampleEnumClass::Type2, "Type2")
                default:
                    return "default";
            }
        }
    };
    SampleEnumClass enumValue1 = SampleEnumClass::Type1;
    SampleEnumClass enumValue2 = SampleEnumClass::Type2;

    SampleClass sampleObject;
    EXPECT_EQ("Type1", sampleObject.getString(enumValue1));
    EXPECT_EQ("Type2", sampleObject.getString(enumValue2));
}

TEST(AlbaMacrosTest, ConcatenateWorks) {
    EXPECT_EQ(12345678, ALBA_MACROS_CONCATENATE_EXPANSION(1234, 5678));
    EXPECT_EQ(12345678, ALBA_MACROS_CONCATENATE(1234, 5678));
    // compiler error: results to 1234__LINE__ (needs another layer of indirection)
    // EXPECT_EQ(12345678U, ALBA_MACROS_CONCATENATE_EXPANSION(1234, __LINE__));
    EXPECT_EQ(1234110, ALBA_MACROS_CONCATENATE(1234, __LINE__));
}

TEST(AlbaMacrosTest, GetNameWithCountWorks) {
    unsigned int ALBA_MACROS_GET_NAME_WITH_COUNT(VariablePrefix) = 0xA1BAU;
    EXPECT_EQ(0xA1BAU, VariablePrefix4);
}

TEST(AlbaMacrosTest, IntegerTest) {
    EXPECT_EQ(1, ALBA_MACROS_COUNT_ARGUMENTS(1));
    EXPECT_EQ(3, ALBA_MACROS_COUNT_ARGUMENTS(8237, 23458, 28749));
    EXPECT_EQ(4, ALBA_MACROS_COUNT_ARGUMENTS(0x1, 0x2, 0x3, 0x4));
}

TEST(AlbaMacrosTest, StringTest) {
    EXPECT_EQ(1, ALBA_MACROS_COUNT_ARGUMENTS("one"));
    EXPECT_EQ(2, ALBA_MACROS_COUNT_ARGUMENTS("one", "two"));
    EXPECT_EQ(3, ALBA_MACROS_COUNT_ARGUMENTS("one", "two", "three"));
}

}  // namespace alba
