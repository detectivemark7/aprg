#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(LimitTest, IsAlmostEqualForLimitIterationWorks)
{
    AlbaNumber::ScopeObject scopeObject;
    scopeObject.setInThisScopeTheTolerancesToZero();

    EXPECT_TRUE(isAlmostEqualForLimitIteration(AlbaNumber(0), AlbaNumber(0)));
    EXPECT_FALSE(isAlmostEqualForLimitIteration(AlbaNumber(0.1), AlbaNumber(0.2)));
    EXPECT_FALSE(isAlmostEqualForLimitIteration(AlbaNumber(1E-15), AlbaNumber(3E-15)));
    EXPECT_TRUE(isAlmostEqualForLimitIteration(AlbaNumber(1E-16), AlbaNumber(3E-16)));
}

TEST(LimitTest, IsAlmostEqualForLimitCheckingWorks)
{
    EXPECT_TRUE(isAlmostEqualForLimitChecking(AlbaNumber(0), AlbaNumber(0)));
    EXPECT_FALSE(isAlmostEqualForLimitChecking(AlbaNumber(0.1), AlbaNumber(0.2)));
    EXPECT_FALSE(isAlmostEqualForLimitChecking(AlbaNumber(1E-5), AlbaNumber(3E-5)));
    EXPECT_TRUE(isAlmostEqualForLimitChecking(AlbaNumber(1E-6), AlbaNumber(3E-6)));
}

TEST(LimitTest, HasVerticalAsymptoteAtValueWorks)
{
    Term numerator(3);
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term constantOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_FALSE(hasVerticalAsymptoteAtValue("x", "x", 2));
    EXPECT_TRUE(hasVerticalAsymptoteAtValue(constantOverPolynomialTerm, "x", 2));
}

TEST(LimitTest, HasHorizontalAsymptoteAtValueWorks)
{
    Term numerator("x");
    Term denominatorInSquareRoot(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {})});
    Term denominator(createExpressionIfPossible({denominatorInSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    Term term(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_FALSE(hasHorizontalAsymptoteAtValue(term, "x", 3));
    EXPECT_TRUE(hasHorizontalAsymptoteAtValue(term, "x", 1));
}

TEST(LimitTest, IsSqueezeTheoremSatisfiedWorks)
{
    Term f(buildTermIfPossible("-4*(x-2)^2 + 3"));
    Term g(buildTermIfPossible("(x-2)*(x^2 - 4*x + 7)/(x-2)"));
    Term h(buildTermIfPossible("4*(x-2)^2 + 3"));

    EXPECT_FALSE(isSqueezeTheoremSatisfied(h, g, f, "x", 1));
    EXPECT_TRUE(isSqueezeTheoremSatisfied(h, g, f, "x", 2));
}

TEST(LimitTest, GetLimitAtAValueByApproachTypeWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueByApproachType(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueByApproachType(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueByApproachType(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueInBothSidesWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueInBothSides(polynomialOverPolynomialTerm, "x", 5));
}

TEST(LimitTest, GetLimitAtAValueInThePositiveSideWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueInThePositiveSide(polynomialOverPolynomialTerm, "x", 5));
}

TEST(LimitTest, GetLimitAtAValueInTheNegativeSideWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueInTheNegativeSide(polynomialOverPolynomialTerm, "x", 5));
}

TEST(LimitTest, GetLimitAtAValueByIterationAndLinearInterpolationWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueByIterationAndLinearInterpolation(polynomialOverPolynomialTerm, "x", 5, 6, 10));
    EXPECT_EQ(AlbaNumber(10), getLimitAtAValueByIterationAndLinearInterpolation(polynomialOverPolynomialTerm, "x", 5, 4, 10));
}

TEST(LimitTest, GetLimitAtAValueUsingTrendOfValuesWorks)
{
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term constantOverPolynomialTerm(createExpressionIfPossible({3, "/", denominator}));

    EXPECT_EQ(AlbaNumber(AlbaNumber::Value::PositiveInfinity), getLimitAtAValueUsingTrendOfValues(constantOverPolynomialTerm, "x", 2, 3, 4));
    EXPECT_EQ(AlbaNumber(AlbaNumber::Value::NegativeInfinity), getLimitAtAValueUsingTrendOfValues(constantOverPolynomialTerm, "x", 2, 1, 0));
    EXPECT_EQ(AlbaNumber::createFraction(9, 10), getLimitAtAValueUsingTrendOfValues(constantOverPolynomialTerm, "x", 5, 6, 7));
}

TEST(LimitTest, GetValueUsingLinearInterpolationWorks)
{
    EXPECT_EQ(AlbaNumber(6), getValueUsingLinearInterpolation(1, 2, 3, 2, 4));
    EXPECT_EQ(AlbaNumber(2), getValueUsingLinearInterpolation(1, 2, 3, 2, 2));
    EXPECT_TRUE(getValueUsingLinearInterpolation(1, 1, 3, 1, 2).isNotANumber());
    EXPECT_TRUE(getValueUsingLinearInterpolation(1, 1, 3, 2, 2).isNotANumber());
}

TEST(LimitTest, GetLimitWorksOnSingleVariable)
{
    Term termToVerify(getLimit("x", "x", 5));

    EXPECT_EQ(Term(5), termToVerify);
}

TEST(LimitTest, GetLimitWithMultipleVariablesWithDifferentApproachesWorksOnExample1)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 4}}), Monomial(-1, {{"y", 4}})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})});
    Term termToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SubstitutionsOfVariablesToTerms substitutions;
    substitutions.emplace_back(SubstitutionOfVariablesToTerms{{"y", "x"}});
    substitutions.emplace_back(SubstitutionOfVariablesToTerms{{"y", Monomial(1, {{"x", 2}})}});

    Term termToVerify(getLimitWithMultipleVariablesWithDifferentApproaches(termToTest, "x", 0, substitutions));

    EXPECT_EQ(Term(0), termToVerify);
}

TEST(LimitTest, GetLimitWithMultipleVariablesWithDifferentApproachesWorksOnExample2)
{
    Term numerator(Monomial(1, {{"x", 1}, {"y", 1}}));
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {{"y", 2}})});
    Term termToTest(createExpressionIfPossible({numerator, "/", denominator}));
    SubstitutionsOfVariablesToTerms substitutions;
    substitutions.emplace_back(SubstitutionOfVariablesToTerms{{"y", "x"}});
    substitutions.emplace_back(SubstitutionOfVariablesToTerms{{"y", Monomial(1, {{"x", 2}})}});

    Term termToVerify(getLimitWithMultipleVariablesWithDifferentApproaches(termToTest, "x", 0, substitutions));

    EXPECT_TRUE(isNan(termToVerify));
}

TEST(LimitTest, GetLimitUsingLhopitalsRuleWorks)
{
    Term oneMinusEToTheX(createExpressionIfPossible({1, "-", getEAsATerm(), "^", "x"}));
    Term oneOverX(createExpressionIfPossible({1, "/", "x"}));
    Term termToTest1("x");
    Term termToTest2(createExpressionIfPossible({"x", "/", oneMinusEToTheX}));
    Term termToTest3(createExpressionIfPossible({sin(oneOverX), "/", arctan(oneOverX)}));

    Term termToVerify1(getLimitUsingLhopitalsRule(termToTest1, "x", 5));
    Term termToVerify2(getLimitUsingLhopitalsRule(termToTest2, "x", 0));
    Term termToVerify3(getLimitUsingLhopitalsRule(termToTest3, "x", AlbaNumber(AlbaNumber::Value::PositiveInfinity)));

    EXPECT_EQ(Term(5), termToVerify1);
    EXPECT_EQ(Term(-1), termToVerify2);
    EXPECT_EQ(Term(1), termToVerify3);
}

TEST(LimitTest, GetTermUsingLhopitalsRuleWorks)
{
    Term oneMinusEToTheX(createExpressionIfPossible({1, "-", getEAsATerm(), "^", "x"}));
    Term oneOverX(createExpressionIfPossible({1, "/", "x"}));
    Term termToTest1("x");
    Term termToTest2(createExpressionIfPossible({"x", "/", oneMinusEToTheX}));
    Term termToTest3(createExpressionIfPossible({sin(oneOverX), "/", arctan(oneOverX)}));

    Term termToVerify1(getTermUsingLhopitalsRule(termToTest1, "x", 5));
    Term termToVerify2(getTermUsingLhopitalsRule(termToTest2, "x", 0));
    Term termToVerify3(getTermUsingLhopitalsRule(termToTest3, "x", AlbaNumber(AlbaNumber::Value::PositiveInfinity)));

    string stringToExpect1("x");
    string stringToExpect2("(-1/((e)^x))");
    string stringToExpect3("((1[x^2] + 1)*cos((1/x))/1[x^2])");
    EXPECT_EQ(stringToExpect1, termToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termToVerify2.getDisplayableString());
    EXPECT_EQ(stringToExpect3, termToVerify3.getDisplayableString());
}

TEST(LimitTest, CalculateTermAndLimitUsingLhopitalsRuleWorksUsingTrigonometricExample)
{
    Term oneOverX(createExpressionIfPossible({1, "/", "x"}));
    Term termToTest(createExpressionIfPossible({sin(oneOverX), "/", arctan(oneOverX)}));

    Term newTerm, limitValue;
    calculateTermAndLimitUsingLhopitalsRule(newTerm, limitValue, termToTest, "x", AlbaNumber(AlbaNumber::Value::PositiveInfinity));

    string stringToExpect("((1[x^2] + 1)*cos((1/x))/1[x^2])");
    EXPECT_EQ(Term(1), limitValue);
    EXPECT_EQ(stringToExpect, newTerm.getDisplayableString());
}

TEST(LimitTest, CalculateTermAndLimitUsingLhopitalsRuleWorksUsingLogarithmicAndExponentialExample)
{
    Term insideLogarithm(createExpressionIfPossible({2, "+", getEAsATerm(), "^", "x"}));
    Term numerator(ln(insideLogarithm));
    Term denominator(Monomial(3, {{"x", 1}}));
    Term termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    Term newTerm, limitValue;
    calculateTermAndLimitUsingLhopitalsRule(newTerm, limitValue, termToTest, "x", AlbaNumber(AlbaNumber::Value::PositiveInfinity));

    string stringToExpect("(1/3)");
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 3)), limitValue);
    EXPECT_EQ(stringToExpect, newTerm.getDisplayableString());
}

TEST(LimitTest, CalculateTermAndLimitUsingLhopitalsRuleWorksUsingTrigonometricExample2)
{
    Term xSquared(Monomial(1, {{"x", 2}}));
    Term termToTestPart1(createExpressionIfPossible({1, "/", xSquared}));
    Term termToTestPart2(createExpressionIfPossible({1, "/", xSquared, "/", sec("x")}));
    Term termToTest(createExpressionIfPossible({termToTestPart1, "-", termToTestPart2}));

    Term newTerm, limitValue;
    calculateTermAndLimitUsingLhopitalsRule(newTerm, limitValue, termToTest, "x", 0);

    string stringToExpect("((sec(x)^2)/(2+(1[x^2]*(sec(x)^2))+(2[x]*tan(x))))");
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), limitValue);
    EXPECT_EQ(stringToExpect, newTerm.getDisplayableString());
}

TEST(LimitTest, GetLimitAtAValueOrInfinityWorks)
{
    Term termToTest1(Polynomial{Monomial(4, {{"x", 1}}), Monomial(-7, {})});
    Term termToTest2(createExpressionIfPossible({1, "/", "x"}));

    EXPECT_EQ(Term(5), getLimitAtAValueOrInfinity(termToTest1, "x", 3));
    EXPECT_EQ(Term(0), getLimitAtAValueOrInfinity(termToTest2, "x", AlbaNumber(AlbaNumber::Value::PositiveInfinity)));
}

TEST(LimitTest, GetLimitAtAValueWorksWhichDoesNotResultToConstant)
{
    Term polynomialTerm(Polynomial{Monomial(4, {{"x", 1}, {"y", 2}}), Monomial(-7, {})});

    Term expectedTermWithY(Polynomial{Monomial(12, {{"y", 2}}), Monomial(-7, {})});
    EXPECT_EQ(expectedTermWithY, getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(expectedTermWithY, getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(expectedTermWithY, getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomial)
{
    Term polynomialTerm(Polynomial{Monomial(4, {{"x", 1}}), Monomial(-7, {})});

    EXPECT_EQ(Term(5), getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(5), getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(5), getLimitAtAValue(polynomialTerm, "x", 3, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForConstantOverPolynomial)
{
    Term numerator(3);
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term constantOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_TRUE(isNan(getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides)));
    EXPECT_EQ(getPositiveInfinityAsATerm(), getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(getNegativeInfinityAsATerm(), getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForConstantOverPolynomialSquared)
{
    Term numerator(3);
    Term polynomialTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term denominator(createExpressionIfPossible({polynomialTerm, "^", 2}));
    Term constantOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(getPositiveInfinityAsATerm(),
              getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(getPositiveInfinityAsATerm(),
              getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(getPositiveInfinityAsATerm(),
              getLimitAtAValue(constantOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(10), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(10), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(10), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 5, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomialOverPolynomialWithDiscontinuityAtOneTwoThree                                                                                                                                                                                                                                               )
{
    Term numerator(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-2, {{"x", 2}})});
    Term denominator(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(11, {{"x", 1}}), Monomial(-6, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_TRUE(isNan(getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides)));
    EXPECT_EQ(Term(-4), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(-3.88235294117647056211239942058), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}


TEST(LimitTest, GetLimitAtAValueWorksForPolynomialOverPolynomialWithEqualDegreeButNoCommonFactors                                                                                                                                                                                                                                               )
{
    Term numerator(Polynomial{Monomial(2, {{"x", 2}}), Monomial(5, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-3, {{"x", 1}}), Monomial(2, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_TRUE(isNan(getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides)));
    EXPECT_EQ(getPositiveInfinityAsATerm(),
              getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(getNegativeInfinityAsATerm(),
              getLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, SimplifyAndGetLimitAtAValueWorksForPolynomialOverPolynomialWithDiscontinuityAtOneTwoThree_ThisCancelsProblematicFactors)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-2, {{"x", 2}})});
    Term denominator(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(11, {{"x", 1}}), Monomial(-6, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(-4), simplifyAndGetLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(-4), simplifyAndGetLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(-4), simplifyAndGetLimitAtAValue(polynomialOverPolynomialTerm, "x", 2, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForPolynomialOverPolynomialWithFractionalValues)
{
    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term polynomialOverPolynomialTerm(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(0.25), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 4, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(0.25), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 4, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(0.25), getLimitAtAValue(polynomialOverPolynomialTerm, "x", 4, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForSignumFunction)
{
    Term signumFunctionTerm(sgn("x"));

    EXPECT_TRUE(isNan(getLimitAtAValue(signumFunctionTerm, "x", 0, LimitAtAValueApproachType::BothSides)));
    EXPECT_EQ(Term(1), getLimitAtAValue(signumFunctionTerm, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(-1), getLimitAtAValue(signumFunctionTerm, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForAbsoluteValueFunction)
{
    Term absoluteValueFunction(Functions::abs("x"));

    EXPECT_EQ(Term(0), getLimitAtAValue(absoluteValueFunction, "x", 0, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(0), getLimitAtAValue(absoluteValueFunction, "x", 0, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(0), getLimitAtAValue(absoluteValueFunction, "x", 0, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtAValueWorksForASpecifiedFunction)
{
    Function functionToTest(
                "functionToTest",
                Term("x"),
                [](AlbaNumber const& number)
    {
        AlbaNumber result;
        AlbaNumber numberSquared(number^2);
        if(number > 1)
        {
            result = numberSquared + 2;
        }
        else if(number < 1)
        {
            result = AlbaNumber(4) - numberSquared;
        }
        else
        {
            result = AlbaNumber(AlbaNumber::Value::NotANumber);
        }
        return result;
    });
    Term functionTermToTest(functionToTest);

    EXPECT_EQ(Term(3), getLimitAtAValue(functionTermToTest, "x", 1, LimitAtAValueApproachType::BothSides));
    EXPECT_EQ(Term(3), getLimitAtAValue(functionTermToTest, "x", 1, LimitAtAValueApproachType::PositiveSide));
    EXPECT_EQ(Term(3), getLimitAtAValue(functionTermToTest, "x", 1, LimitAtAValueApproachType::NegativeSide));
}

TEST(LimitTest, GetLimitAtInfinityWorks)
{
    EXPECT_EQ(getNegativeInfinityAsATerm(), getLimitAtInfinity("x", "x", AlbaNumber::Value::NegativeInfinity));
    EXPECT_EQ(getPositiveInfinityAsATerm(), getLimitAtInfinity("x", "x", AlbaNumber::Value::PositiveInfinity));
}

TEST(LimitTest, GetObliqueAsymptoteWorksAsResultIsEmptyWhenItsALine)
{
    Term termToTest(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});

    EXPECT_EQ(Term(), getObliqueAsymptote(termToTest));
}

TEST(LimitTest, GetObliqueAsymptoteWorksAsResultIsEmptyWhenDegreeOfDenominatorIsGreater)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(3, {})});
    Term termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(), getObliqueAsymptote(termToTest));
}

TEST(LimitTest, GetObliqueAsymptoteWorksWhenThereIsAnObliqueAsymptote)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(3, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {})});
    Term termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), getObliqueAsymptote(termToTest));
}

}

}
