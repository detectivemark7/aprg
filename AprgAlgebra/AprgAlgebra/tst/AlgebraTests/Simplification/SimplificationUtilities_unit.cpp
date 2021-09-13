#include <Algebra/Simplification/SimplificationUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

TEST(SimplificationUtilitiesTest, SimplifyTermToACommonDenominatorWorks)
{
    Term denominator1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    Term denominator2(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(3, {})});
    Term firstTerm(createExpressionIfPossible({1, "/", denominator1}));
    Term secondTerm(createExpressionIfPossible({1, "/", denominator2}));

    Term termToTest(createExpressionIfPossible({firstTerm, "+", secondTerm}));
    simplifyTermToACommonDenominator(termToTest);

    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(-6, {})});
    Term expectedTerm(createExpressionIfPossible({-5, "/", expectedDenominator}));
    EXPECT_EQ(expectedTerm, termToTest);
}

TEST(SimplificationUtilitiesTest, SimplifyToACommonDenominatorWorks)
{
    Expression expression(createExpressionIfPossible(tokenizeToTerms("((4)/(x+2))+((x+3)/(x*x-4))+((2*x+1)/(x-2))")));

    bool didItOccurOnTopLevelExpression = simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(expression);

    Expression expressionToExpect(
                createExpressionIfPossible(
    {Polynomial{Monomial(2, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(-3, {})},
     "/",
     Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}}));
    EXPECT_EQ(expressionToExpect, expression);
    EXPECT_TRUE(didItOccurOnTopLevelExpression);
}

TEST(SimplificationUtilitiesTest, SimplifyToACommonDenominatorWorks_OnExponentPlusPolynomialDenominator)
{
    Expression expression(createExpressionIfPossible(tokenizeToTerms("2^x+((1)/(x+2))")));

    bool didItOccurOnTopLevelExpression = simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(expression);

    string stringToExpect("((1+(x*(2^x))+(2^(1[x] + 1)))/(1[x] + 2))");
    EXPECT_EQ(stringToExpect, convertToString(expression));
    EXPECT_TRUE(didItOccurOnTopLevelExpression);
}

TEST(SimplificationUtilitiesTest, SimplifyToACommonDenominatorWorks_OnExponentWithFractionExpressions)
{
    Expression expression(createExpressionIfPossible(tokenizeToTerms("2^(((1)/(x+2))+((1)/(x-2)))")));

    bool didItOccurOnTopLevelExpression = simplifyToACommonDenominatorForExpressionAndReturnIfAdditionOrSubtractionOfTermsOverTermsOccurred(expression);

    Polynomial polynomialToExpect{Monomial(1, {{"x", 2}}), Monomial(-4, {})};
    Expression subExpression(createExpressionIfPossible({Monomial(2, {{"x", 1}}), "/", polynomialToExpect}));
    Expression expressionToExpect(createExpressionIfPossible({2, "^", subExpression}));
    EXPECT_EQ(expressionToExpect, expression);
    EXPECT_FALSE(didItOccurOnTopLevelExpression);
}

TEST(SimplificationUtilitiesTest, SimplifyAndCopyTermsAndChangeOperatorLevelIfNeededWorksForOneTerm)
{
    TermsWithDetails inputTermWithDetails;
    inputTermWithDetails.emplace_back(Term(Monomial(5, {{}})), TermAssociationType::Positive);
    OperatorLevel operatorLevel(OperatorLevel::Unknown);
    TermsWithDetails outputTermsWithDetails;

    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(outputTermsWithDetails, operatorLevel, inputTermWithDetails);

    TermsWithDetails expectedTermsWithDetails;
    expectedTermsWithDetails.emplace_back(Term(5), TermAssociationType::Positive);
    EXPECT_EQ(expectedTermsWithDetails, outputTermsWithDetails);
}

TEST(SimplificationUtilitiesTest, SimplifyAndCopyTermsAndChangeOperatorLevelIfNeededWorksForOneTermWithManyExpressions)
{
    Term oneTerm(createExpressionInAnExpression(createExpressionInAnExpression(createAndWrapExpressionFromATerm(Monomial(5, {{}})))));
    TermsWithDetails inputTermWithDetails;
    inputTermWithDetails.emplace_back(oneTerm, TermAssociationType::Positive);
    OperatorLevel operatorLevel(OperatorLevel::Unknown);
    TermsWithDetails outputTermsWithDetails;

    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(outputTermsWithDetails, operatorLevel, inputTermWithDetails);

    TermsWithDetails expectedTermsWithDetails;
    expectedTermsWithDetails.emplace_back(Term(5), TermAssociationType::Positive);
    EXPECT_EQ(expectedTermsWithDetails, outputTermsWithDetails);
}



}

}

}
