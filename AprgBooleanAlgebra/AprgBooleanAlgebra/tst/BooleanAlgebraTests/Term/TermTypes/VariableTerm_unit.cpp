#include <BooleanAlgebra/Term/TermTypes/VariableTerm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

TEST(VariableTermTest, VariableTermsAreConstructedCorrectly)
{
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("time");
    VariableTerm variableTerm3("time'");
    VariableTerm variableTerm4(VariableTerm::createNegatedVariableTerm("time"));

    EXPECT_EQ("", variableTerm1.getVariableTermName());
    EXPECT_FALSE(variableTerm1.isNegated());
    EXPECT_EQ("time", variableTerm2.getVariableTermName());
    EXPECT_FALSE(variableTerm2.isNegated());
    EXPECT_EQ("time", variableTerm3.getVariableTermName());
    EXPECT_TRUE(variableTerm3.isNegated());
    EXPECT_EQ("time", variableTerm4.getVariableTermName());
    EXPECT_TRUE(variableTerm4.isNegated());
}

TEST(VariableTermTest, EqualityOperatorWorks)
{
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("x");
    VariableTerm variable3("power");
    VariableTerm variable4(VariableTerm::createNegatedVariableTerm("x"));

    EXPECT_TRUE(variableTerm1==variableTerm1);
    EXPECT_FALSE(variableTerm1==variableTerm2);
    EXPECT_TRUE(variableTerm2==variableTerm2);
    EXPECT_FALSE(variableTerm2==variable3);
    EXPECT_FALSE(variableTerm2==variable4);
}

TEST(VariableTermTest, NonequalityOperatorWorks)
{
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("x");
    VariableTerm variable3("power");
    VariableTerm variable4("x'");

    EXPECT_FALSE(variableTerm1!=variableTerm1);
    EXPECT_TRUE(variableTerm1!=variableTerm2);
    EXPECT_FALSE(variableTerm2!=variableTerm2);
    EXPECT_TRUE(variableTerm2!=variable3);
    EXPECT_TRUE(variableTerm2!=variable4);
}

TEST(VariableTermTest, LessThanOperatorWorks)
{
    EXPECT_FALSE(VariableTerm() < VariableTerm());
    EXPECT_FALSE(VariableTerm("x") < VariableTerm("x"));
    EXPECT_FALSE(VariableTerm("x") < VariableTerm("w"));
    EXPECT_TRUE(VariableTerm("x") < VariableTerm("y"));
    EXPECT_FALSE(VariableTerm("x") < VariableTerm("x"));
    EXPECT_FALSE(VariableTerm("x'") < VariableTerm("x"));
    EXPECT_TRUE(VariableTerm("x") < VariableTerm("x'"));
}

TEST(VariableTermTest, NotOperationWorks)
{
    EXPECT_EQ(VariableTerm("time'"), ~VariableTerm("time"));
    EXPECT_EQ(VariableTerm("time"), ~VariableTerm("time'"));
}

TEST(VariableTermTest, IsNegatedWorks)
{
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("time'");

    EXPECT_FALSE(variableTerm1.isNegated());
    EXPECT_TRUE(variableTerm2.isNegated());
}

TEST(VariableTermTest, SettingANewVariableTermNameWorks)
{
    VariableTerm variableForTest;
    EXPECT_EQ("", variableForTest.getVariableTermName());

    variableForTest.setVariableTermName("omega");
    EXPECT_EQ("omega", variableForTest.getVariableTermName());
}

TEST(VariableTermTest, NegateWorks)
{
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("time");
    VariableTerm variableTerm3("time'");

    variableTerm1.negate();
    variableTerm2.negate();
    variableTerm3.negate();

    EXPECT_EQ(VariableTerm("'"), variableTerm1);
    EXPECT_EQ(VariableTerm("time'"), variableTerm2);
    EXPECT_EQ(VariableTerm("time"), variableTerm3);
}

TEST(VariableTermTest, OutputStreamOperatorWorks)
{
    stringstream ss;
    VariableTerm variableTerm1;
    VariableTerm variableTerm2("time");

    ss << variableTerm1 << "," << variableTerm2;

    EXPECT_EQ(",time", ss.str());
}

}

}
