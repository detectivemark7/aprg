#include "../Checkers.hpp"
#include "fixtures/ModuleTest.hpp"
#include "gtest/gtest.h"

#include <fstream>

using namespace codeReview;
using namespace std;

TEST_F(ModuleTest, MacroDefinitionsDefineTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#define MACRO0\n";
    testFile << "#define MACRO1 variable1\n";
    testFile << "#define MACRO2(a, b) a = a + b\n";
    testFile << "int MACRO1 = 5;\n";
    testFile << "int variable2 = 5;\n";
    testFile << "MACRO2(variable1, variable2);\n";
    testFile.close();

    processFile();
    ASSERT_TRUE(m_database.isMacro("MACRO0"));
    ASSERT_TRUE(m_database.isMacro("MACRO1"));
    ASSERT_TRUE(m_database.isMacro("MACRO2"));
    ASSERT_EQ(m_terms.size(), 6);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO0\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO1 variable1\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO2(a, b) a = a + b\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "int variable1 = 5;\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "int variable2 = 5;\n", 5);
    CHECK_TERM(it, TermType::ProcessedTerm, "variable1 = variable1 + variable2;\n", 6);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MacroDefinitionsDefineWithParameterMismatchTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#define MACRO0(a, b) a = a + b\n";
    testFile << "int variable1 = 5;\n";
    testFile << "int variable2 = 5;\n";
    testFile << "int variable3 = 5;\n";
    testFile << "MACRO0(variable1, variable2, variable3);\n";
    testFile.close();

    processFile();
    ASSERT_TRUE(m_database.isMacro("MACRO0"));
    ASSERT_EQ(m_terms.size(), 5);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO0(a, b) a = a + b\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int variable1 = 5;\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "int variable2 = 5;\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "int variable3 = 5;\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "variable1 = variable1 + variable2;\n", 5);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 1);
}

TEST_F(ModuleTest, MacroDefinitionsDefineWithVariadicParametersTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#define MACRO0(...) __VA_ARGS__\n";
    testFile << "#define MACRO1(a, ...) a = __VA_ARGS__\n";
    testFile << "#define MACRO2(a, b, ...) a = a + b + __VA_ARGS__\n";
    testFile << "int MACRO0(variable1) = 5;\n";
    testFile << "int MACRO0(variable2) = 5;\n";
    testFile << "int MACRO0(variable3) = 5;\n";
    testFile << "MACRO1(variable1, variable1 + variable2);\n";
    testFile << "MACRO2(variable1, variable2, variable3);\n";
    testFile.close();

    processFile();
    ASSERT_TRUE(m_database.isMacro("MACRO0"));
    ASSERT_TRUE(m_database.isMacro("MACRO1"));
    ASSERT_TRUE(m_database.isMacro("MACRO2"));
    ASSERT_EQ(m_terms.size(), 8);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO0(...) __VA_ARGS__\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO1(a, ...) a = __VA_ARGS__\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO2(a, b, ...) a = a + b + __VA_ARGS__\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "int variable1 = 5;\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "int variable2 = 5;\n", 5);
    CHECK_TERM(it, TermType::ProcessedTerm, "int variable3 = 5;\n", 6);
    CHECK_TERM(it, TermType::ProcessedTerm, "variable1 = variable1 + variable2;\n", 7);
    CHECK_TERM(it, TermType::ProcessedTerm, "variable1 = variable1 + variable2 + variable3;\n", 8);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MacroDefinitionsDefineWithVariadicWithContentsParametersTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#define MACRO0(a, b, ...) int a = b + __VA_ARGS__\n";
    testFile << "MACRO0(variable1, 100, 200 * 300);\n";
    testFile.close();

    processFile();
    ASSERT_TRUE(m_database.isMacro("MACRO0"));
    ASSERT_EQ(m_terms.size(), 2);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO0(a, b, ...) int a = b + __VA_ARGS__\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int variable1 = 100 + 200 * 300;\n", 2);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MacroDefinitionsDefineMultiLineTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#define MACROSTART if(1 == 1)\\\n";
    testFile << "{\n";
    testFile << "#define MACROEND }\n";
    testFile << "MACROSTART\n";
    testFile << "int x = 5;\n";
    testFile << "MACROEND\n";
    testFile.close();

    processFile();
    ASSERT_TRUE(m_database.isMacro("MACROSTART"));
    ASSERT_TRUE(m_database.isMacro("MACROEND"));
    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACROSTART if(1 == 1)\\\n{\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACROEND }\n", 3);
    CHECK_TERM(it, TermType::MultiLine_IfElseIfStartChain_Ignorable, "if(1 == 1)\n{\nint x = 5;\n}\n", 4);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MacroDefinitionsUndefTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#define MACRO1 variable1\n";
    testFile << "int MACRO1 = 5;\n";
    testFile << "#undef MACRO1\n";
    testFile << "int MACRO1 = 5;\n";
    testFile.close();

    processFile();
    ASSERT_FALSE(m_database.isMacro("MACRO1"));
    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO1 variable1\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int variable1 = 5;\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "#undef MACRO1\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "int MACRO1 = 5;\n", 4);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MacroDefinitionsDefineWithCyclicEquivalentCannotBeAddedTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#define MACRO1 MACRO1 MACRO2 MACRO3\n";
    testFile << "#define MACRO2 MACRO1 MACRO2 MACRO3\n";
    testFile << "#define MACRO3 MACRO1 MACRO2 MACRO3\n";
    testFile << "int MACRO1 = 1;\n";
    testFile << "int MACRO2 = 2;\n";
    testFile << "int MACRO3 = 3;\n";
    testFile.close();

    processFile();
    ASSERT_FALSE(m_database.isMacro("MACRO1"));
    ASSERT_FALSE(m_database.isMacro("MACRO2"));
    ASSERT_FALSE(m_database.isMacro("MACRO3"));
    ASSERT_EQ(m_terms.size(), 6);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO1 MACRO1 MACRO2 MACRO3\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO2 MACRO1 MACRO2 MACRO3\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO3 MACRO1 MACRO2 MACRO3\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "int MACRO1 = 1;\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "int MACRO2 = 2;\n", 5);
    CHECK_TERM(it, TermType::ProcessedTerm, "int MACRO3 = 3;\n", 6);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 3);
}

TEST_F(ModuleTest, MacroDefinitionsDefineWithCyclicEquivalentCannotBeAddedTest2)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#define MACRO1 MACRO2\n";
    testFile << "#define MACRO2 MACRO3\n";
    testFile << "#define MACRO3 MACRO1\n";
    testFile << "int MACRO1 = 1;\n";
    testFile.close();

    processFile();
    ASSERT_TRUE(m_database.isMacro("MACRO1"));
    ASSERT_TRUE(m_database.isMacro("MACRO2"));
    ASSERT_FALSE(m_database.isMacro("MACRO3"));
    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO1 MACRO2\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO2 MACRO3\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define MACRO3 MACRO1\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "int MACRO3 = 1;\n", 4);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 1);
}

TEST_F(ModuleTest, MacroExtraMacroTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#ifdef I dont care what is the next part\n";
    testFile << "#line I don2t cAre 234567\n";
    testFile << "#error Why?\n";
    testFile << "#pragma because the WHOLE line is combined\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 4);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#ifdef I dont care what is the next part\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "#line I don2t cAre 234567\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "#error Why?\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "#pragma because the WHOLE line is combined\n", 4);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MacroWithParenthesisTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#define _TRUNCATE ((size_t) - 1)\n";
    testFile << "int size_t;\n";
    testFile << "int x = _TRUNCATE;\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 3);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#define _TRUNCATE ((size_t) - 1)\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "int size_t;\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "int x = ((size_t) - 1);\n", 3);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}

TEST_F(ModuleTest, MacroWithStringsTest)
{
    ofstream testFile(MT_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "#ifdef _POSIX_\n";
    testFile << "#define _P_tmpdir \"/\"\n";
    testFile << "#define _wP_tmpdir L\"/\"\n";
    testFile << "#else\n";
    testFile << "#define _P_tmpdir \"\\\\\"\n";
    testFile << "#define _wP_tmpdir L\"\\\\\"\n";
    testFile << "#endif\n";
    testFile.close();

    processFile();
    ASSERT_EQ(m_terms.size(), 7);
    auto it = m_terms.begin();
    CHECK_TERM(it, TermType::ProcessedTerm, "#ifdef _POSIX_\n", 1);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define _P_tmpdir \"/\"\n", 2);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define _wP_tmpdir L\"/\"\n", 3);
    CHECK_TERM(it, TermType::ProcessedTerm, "#else\n", 4);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define _P_tmpdir \"\\\\\"\n", 5);
    CHECK_TERM(it, TermType::ProcessedTerm, "#define _wP_tmpdir L\"\\\\\"\n", 6);
    CHECK_TERM(it, TermType::ProcessedTerm, "#endif\n", 7);
    EXPECT_EQ(m_findings.getMultiMapOfFindingsReference().size(), 0);
}
