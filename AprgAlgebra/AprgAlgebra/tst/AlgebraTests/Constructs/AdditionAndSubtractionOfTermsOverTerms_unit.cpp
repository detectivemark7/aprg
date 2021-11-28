#include <Algebra/Constructs/AdditionAndSubtractionOfTermsOverTerms.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

TEST(AdditionAndSubtractionOfTermsOverTermsTest, ConstructionWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;

    EXPECT_TRUE(additionAndSubtraction.getItems().empty());
    EXPECT_TRUE(additionAndSubtraction.getAssociations().empty());
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithNoTermsWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({1}, {});
    TermsOverTerms fraction2({1}, {});
    TermsOverTerms fraction3({1}, {});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(1);
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithTermsThatAreEmptyWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({1}, {Term()});
    TermsOverTerms fraction2({1}, {Term()});
    TermsOverTerms fraction3({1}, {Term()});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(1);
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
}
TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithAllOneWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({1}, {1});
    TermsOverTerms fraction2({1}, {1});
    TermsOverTerms fraction3({1}, {1});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(1);
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithLcmMonomialWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({1}, {Polynomial{Monomial(3, {{"x", 3}})}});
    TermsOverTerms fraction2({1}, {Monomial(5, {{"x", 5}})});
    TermsOverTerms fraction3({1}, {Monomial(7, {{"y", 7}})});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(Monomial(105, {{"x", 5}, {"y", 7}}));
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithNoCommonFactorsWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({1}, {Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})}});
    TermsOverTerms fraction2({1}, {Polynomial{Monomial(1, {{"y", 1}}), Monomial(5, {})}});
    TermsOverTerms fraction3({1}, {Polynomial{Monomial(1, {{"z", 1}}), Monomial(7, {})}});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})});
    Term termToExpect2(Polynomial{Monomial(1, {{"y", 1}}), Monomial(5, {})});
    Term termToExpect3(Polynomial{Monomial(1, {{"z", 1}}), Monomial(7, {})});
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
    EXPECT_EQ(termToExpect2, termsToVerify.at(1));
    EXPECT_EQ(termToExpect3, termsToVerify.at(2));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithCommonFactorsWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    TermsOverTerms fraction1({1}, {polynomial});
    TermsOverTerms fraction2({1}, {Term(), polynomial});
    TermsOverTerms fraction3({1}, {polynomial, polynomial, polynomial});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(polynomial);
    Term termToExpect2(createExpressionIfPossible({polynomial, "^", 3}));
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
    EXPECT_EQ(termToExpect2, termsToVerify.at(1));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetLcmOfDenominatorTermsWithFactorsOfDifferenceOfSquaresWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({1}, {Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}});
    TermsOverTerms fraction2({1}, {Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}});
    TermsOverTerms fraction3({1}, {Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Terms termsToVerify(additionAndSubtraction.getLcmOfDenominatorTerms());

    Term termToExpect1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    Term termToExpect2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(termToExpect1, termsToVerify.at(0));
    EXPECT_EQ(termToExpect2, termsToVerify.at(1));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexUsingOutOfRangeIndexReturnsEmpty) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;

    Terms termsToVerify1(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {}));
    Terms termsToVerify2(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(1, {}));
    Terms termsToVerify3(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(2, {}));

    ASSERT_TRUE(termsToVerify1.empty());
    ASSERT_TRUE(termsToVerify2.empty());
    ASSERT_TRUE(termsToVerify3.empty());
}

TEST(
    AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexReturnsNumeratorTermsWhenLcmIsEmpty) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction({Polynomial{Monomial(1, {{"x", 1}}), Monomial(17, {})}}, {1});
    additionAndSubtraction.putAsAddition(fraction);

    Terms termsToVerify(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {}));

    Term termToExpect(Polynomial{Monomial(1, {{"x", 1}}), Monomial(17, {})});
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexReturnsNumeratorTermsWhenLcmIsOne) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction({Polynomial{Monomial(1, {{"x", 1}}), Monomial(17, {})}}, {1});
    additionAndSubtraction.putAsAddition(fraction);

    Terms termsToVerify(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {1}));

    Term termToExpect(Polynomial{Monomial(1, {{"x", 1}}), Monomial(17, {})});
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexReturnsGcfOfDenominatorAndLcm) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction({1}, {Monomial(4, {{"x", 5}, {"y", 3}})});
    additionAndSubtraction.putAsAddition(fraction);

    Terms termsToVerify(
        additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {Monomial(52, {{"x", 7}, {"y", 8}})}));

    Term termToExpect(Monomial(13, {{"x", 2}, {"y", 5}}));
    ASSERT_EQ(1U, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
}

TEST(
    AdditionAndSubtractionOfTermsOverTermsTest,
    GetNumeratorTermsBasedOnLcmOnIndexReturnsWithCommonFactorsFromDenominatorAndLcmRemoved) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    TermsOverTerms fraction({1}, {polynomial});
    additionAndSubtraction.putAsAddition(fraction);

    Terms termsToVerify(
        additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, {polynomial, polynomial, polynomial}));

    Term termToExpect(polynomial);
    ASSERT_EQ(2U, termsToVerify.size());
    EXPECT_EQ(termToExpect, termsToVerify.at(0));
    EXPECT_EQ(termToExpect, termsToVerify.at(1));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetNumeratorTermsBasedOnLcmOnIndexUsingAComplicatedExampleWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({4}, {Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}});
    TermsOverTerms fraction2(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})}},
        {Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}});
    TermsOverTerms fraction3(
        {Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})}},
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);
    Terms denominatorTerms(additionAndSubtraction.getLcmOfDenominatorTerms());

    Terms termsToVerify1(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(0, denominatorTerms));
    Terms termsToVerify2(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(1, denominatorTerms));
    Terms termsToVerify3(additionAndSubtraction.getRevisedNumeratorTermsBasedOnLcmOnIndex(2, denominatorTerms));

    Term termToExpect1(4);
    Term termToExpect2(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})});
    Term termToExpect3(Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})});
    Term termToExpect4(Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Term termToExpect5(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})});
    ASSERT_EQ(2U, termsToVerify1.size());
    EXPECT_EQ(termToExpect1, termsToVerify1.at(0));
    EXPECT_EQ(termToExpect2, termsToVerify1.at(1));
    ASSERT_EQ(1U, termsToVerify2.size());
    EXPECT_EQ(termToExpect3, termsToVerify2.at(0));
    ASSERT_EQ(2U, termsToVerify3.size());
    EXPECT_EQ(termToExpect4, termsToVerify3.at(0));
    EXPECT_EQ(termToExpect5, termsToVerify3.at(1));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionForNumeratorTermsWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({7}, {1});
    TermsOverTerms fraction2({11}, {1});
    TermsOverTerms fraction3({13}, {1});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsSubtraction(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());

    Expression subExpression1(createExpressionIfPossible({7}));
    Expression subExpression2(createExpressionIfPossible({11}));
    Expression subExpression3(createExpressionIfPossible({13}));
    Expression subExpression4(createExpressionIfPossible({subExpression1, "-", subExpression2, "+", subExpression3}));
    Expression expressionToExpect(createExpressionIfPossible({subExpression4}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionForLcmDenominatorWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({1}, {2});
    TermsOverTerms fraction2({1}, {3});
    TermsOverTerms fraction3({1}, {4});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());

    Expression subExpression1(createExpressionIfPossible({createMonomialFromNumber(6)}));
    Expression subExpression2(createExpressionIfPossible({createMonomialFromNumber(4)}));
    Expression subExpression3(createExpressionIfPossible({createMonomialFromNumber(3)}));
    Expression subExpression4(createExpressionIfPossible({subExpression1, "+", subExpression2, "+", subExpression3}));
    Expression expressionToExpect(createExpressionIfPossible({subExpression4, "/", 12}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionForRevisedNumeratorTermsWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({7}, {2});
    TermsOverTerms fraction2({11}, {3});
    TermsOverTerms fraction3({13}, {4});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsSubtraction(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());

    Expression subExpression1(createExpressionIfPossible({7, "*", createMonomialFromNumber(6)}));
    Expression subExpression2(createExpressionIfPossible({11, "*", createMonomialFromNumber(4)}));
    Expression subExpression3(createExpressionIfPossible({13, "*", createMonomialFromNumber(3)}));
    Expression subExpression4(createExpressionIfPossible({subExpression1, "-", subExpression2, "+", subExpression3}));
    Expression expressionToExpect(createExpressionIfPossible({subExpression4, "/", 12}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionUsingExample1Works) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({4}, {Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}});
    TermsOverTerms fraction2(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})}},
        {Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}});
    TermsOverTerms fraction3(
        {Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})}},
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());

    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(-2, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Polynomial polynomial3{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    Polynomial polynomial4{Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Expression subExpression1(createExpressionIfPossible({4, "*", polynomial1}));
    Expression subExpression2(createExpressionIfPossible({polynomial3}));
    Expression subExpression3(createExpressionIfPossible({polynomial4, "*", polynomial2}));
    Expression subExpression4(createExpressionIfPossible({subExpression1, "+", subExpression2, "+", subExpression3}));
    Expression expressionToExpect(createExpressionIfPossible({subExpression4, "/", polynomial2, "/", polynomial1}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(
    AdditionAndSubtractionOfTermsOverTermsTest,
    GetCombinedExpressionAndSimplifyWorksOnExponentPlusPolynomialDenominator) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Expression exponentExpression(createExpressionIfPossible({2, "^", "x"}));
    TermsOverTerms fraction1({exponentExpression}, {});
    TermsOverTerms fraction2({}, {polynomial});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());
    expressionToVerify.simplify();

    string stringToExpect("((1+(x*(2^x))+(2^(1[x] + 1)))/(1[x] + 2))");
    EXPECT_EQ(stringToExpect, convertToString(expressionToVerify));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionAndSimplifyUsingExample1Works) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction1({4}, {Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {})}});
    TermsOverTerms fraction2(
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(3, {})}},
        {Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {})}});
    TermsOverTerms fraction3(
        {Polynomial{Monomial(2, {{"x", 1}}), Monomial(1, {})}},
        {Polynomial{Monomial(1, {{"x", 1}}), Monomial(-2, {})}});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsAddition(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());
    expressionToVerify.simplify();

    Polynomial polynomialToExpect1{Monomial(2, {{"x", 2}}), Monomial(10, {{"x", 1}}), Monomial(-3, {})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 2}}), Monomial(-4, {})};
    Expression expressionToExpect(createExpressionIfPossible({polynomialToExpect1, "/", polynomialToExpect2}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, GetCombinedExpressionAndSimplifyUsingExample2Works) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    Polynomial polynomial1{Monomial(2, {{"x", 1}}), Monomial(-1, {})};
    Polynomial polynomial2{Monomial(2, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(-6, {})};
    Polynomial polynomial3{Monomial(1, {{"x", 1}}), Monomial(3, {})};
    Polynomial polynomial4{Monomial(6, {{"x", 2}}), Monomial(1, {{"x", 1}}), Monomial(-12, {})};
    Polynomial polynomial5{Monomial(2, {{"x", 1}}), Monomial(-3, {})};
    Polynomial polynomial6{Monomial(3, {{"x", 2}}), Monomial(-10, {{"x", 1}}), Monomial(8, {})};
    TermsOverTerms fraction1({polynomial1}, {polynomial2});
    TermsOverTerms fraction2({polynomial3}, {polynomial4});
    TermsOverTerms fraction3({polynomial5}, {polynomial6});
    additionAndSubtraction.putAsAddition(fraction1);
    additionAndSubtraction.putAsAddition(fraction2);
    additionAndSubtraction.putAsSubtraction(fraction3);

    Expression expressionToVerify(additionAndSubtraction.getCombinedExpression());
    expressionToVerify.simplify();

    Polynomial polynomialToExpect1{Monomial(3, {{"x", 2}}), Monomial(-10, {{"x", 1}}), Monomial(7, {})};
    Polynomial polynomialToExpect2{
        Monomial(6, {{"x", 3}}), Monomial(-11, {{"x", 2}}), Monomial(-14, {{"x", 1}}), Monomial(24, {})};
    Expression expressionToExpect(createExpressionIfPossible({polynomialToExpect1, "/", polynomialToExpect2}));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, PutAsAdditionWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction({487}, {756});

    additionAndSubtraction.putAsAddition(fraction);

    VectorOfTermsOverTerms const& itemsToVerify(additionAndSubtraction.getItems());
    TermAssociationTypes const& associationToVerify(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, itemsToVerify.size());
    Terms const& numerators(itemsToVerify.at(0).getNumerators());
    Terms const& denominators(itemsToVerify.at(0).getDenominators());
    ASSERT_EQ(1U, numerators.size());
    EXPECT_EQ(Term(487), numerators.at(0));
    ASSERT_EQ(1U, denominators.size());
    EXPECT_EQ(Term(756), denominators.at(0));
    ASSERT_EQ(1U, associationToVerify.size());
    EXPECT_EQ(TermAssociationType::Positive, associationToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, PutAsSubtractionWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction({487}, {756});

    additionAndSubtraction.putAsSubtraction(fraction);

    VectorOfTermsOverTerms const& itemsToVerify(additionAndSubtraction.getItems());
    TermAssociationTypes const& associationToVerify(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, itemsToVerify.size());
    Terms const& numerators(itemsToVerify.at(0).getNumerators());
    Terms const& denominators(itemsToVerify.at(0).getDenominators());
    ASSERT_EQ(1U, numerators.size());
    EXPECT_EQ(Term(487), numerators.at(0));
    ASSERT_EQ(1U, denominators.size());
    EXPECT_EQ(Term(756), denominators.at(0));
    ASSERT_EQ(1U, associationToVerify.size());
    EXPECT_EQ(TermAssociationType::Negative, associationToVerify.at(0));
}

TEST(AdditionAndSubtractionOfTermsOverTermsTest, PutAsAddOrSubtractionWorks) {
    AdditionAndSubtractionOfTermsOverTerms additionAndSubtraction;
    TermsOverTerms fraction({487}, {756});

    additionAndSubtraction.putAsAddOrSubtraction(fraction, TermAssociationType::Negative);

    VectorOfTermsOverTerms const& itemsToVerify(additionAndSubtraction.getItems());
    TermAssociationTypes const& associationToVerify(additionAndSubtraction.getAssociations());
    ASSERT_EQ(1U, itemsToVerify.size());
    Terms const& numerators(itemsToVerify.at(0).getNumerators());
    Terms const& denominators(itemsToVerify.at(0).getDenominators());
    ASSERT_EQ(1U, numerators.size());
    EXPECT_EQ(Term(487), numerators.at(0));
    ASSERT_EQ(1U, denominators.size());
    EXPECT_EQ(Term(756), denominators.at(0));
    ASSERT_EQ(1U, associationToVerify.size());
    EXPECT_EQ(TermAssociationType::Negative, associationToVerify.at(0));
}

}  // namespace algebra

}  // namespace alba
