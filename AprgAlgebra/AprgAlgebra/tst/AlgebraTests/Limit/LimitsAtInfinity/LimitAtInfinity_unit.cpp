#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Limit/LimitsAtInfinity/LimitsAtInfinity.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace alba::algebra::Functions;
using namespace std;

namespace alba {

namespace algebra {

TEST(LimitsAtInfinityTest, XWorksAndSimplifiesToZero) {
    LimitsAtInfinity limits("x", "x");

    EXPECT_EQ(Term("x"), limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(getNegativeInfinityAsATerm(), limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(getPositiveInfinityAsATerm(), limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, OneOverXWorksAndSimplifiesToZero) {
    Term term(createExpressionIfPossible({1, "/", "x"}));

    LimitsAtInfinity limits(term, "x");

    Term expectedTerm(0);
    Term expectedValueTerm(0);
    EXPECT_EQ(expectedTerm, limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, PolynomialOverPolynomialWithEqualDegreeWorks) {
    Term numerator(Polynomial{Monomial(2, {{"x", 2}})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {})});
    Term term(createExpressionIfPossible({numerator, "/", denominator}));

    LimitsAtInfinity limits(term, "x");

    Term expectedTerm(2);
    Term expectedValueTerm(2);
    EXPECT_EQ(expectedTerm, limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, PolynomialOverPolynomialWithNumeratorDegreeIsGreaterAndPositiveWorks) {
    Term numerator(Polynomial{Monomial(1, {{"x", 2}})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term term(createExpressionIfPossible({numerator, "/", denominator}));

    LimitsAtInfinity limits(term, "x");

    EXPECT_EQ(Term("x"), limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(getNegativeInfinityAsATerm(), limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(getPositiveInfinityAsATerm(), limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, PolynomialOverPolynomialWithNumeratorDegreeIsGreaterAndNegativeWorks) {
    Term numerator(Polynomial{Monomial(-6, {{"x", 2}}), Monomial(2, {{"x", 1}})});
    Term denominator(Polynomial{Monomial(3, {{"x", 1}}), Monomial(5, {})});
    Term term(createExpressionIfPossible({numerator, "/", denominator}));

    LimitsAtInfinity limits(term, "x");

    EXPECT_EQ(Term(Monomial(-2, {{"x", 1}})), limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(getPositiveInfinityAsATerm(), limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(getNegativeInfinityAsATerm(), limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, PolynomialOverPolynomialWithDenominatorDegreeIsGreaterWorks) {
    Term numerator(Polynomial{Monomial(2, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(5, {})});
    Term denominator(Polynomial{Monomial(4, {{"x", 3}}), Monomial(-1, {})});
    Term term(createExpressionIfPossible({numerator, "/", denominator}));

    LimitsAtInfinity limits(term, "x");

    Term expectedTerm(0);
    Term expectedValueTerm(0);
    EXPECT_EQ(expectedTerm, limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, PolynomialOverSquareRootOfPolynomialWithEqualDegreeWorks) {
    Term numerator("x");
    Term denominatorInSquareRoot(Polynomial{Monomial(1, {{"x", 2}}), Monomial(1, {})});
    Term denominator(createExpressionIfPossible({denominatorInSquareRoot, "^", AlbaNumber::createFraction(1, 2)}));
    Term term(createExpressionIfPossible({numerator, "/", denominator}));

    LimitsAtInfinity limits(term, "x");

    Term expectedTerm(1);
    Term expectedValueTerm(1);
    EXPECT_EQ(expectedTerm, limits.getSimplifiedTermAtInfinity());
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY));
    EXPECT_EQ(expectedValueTerm, limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY));
}

TEST(LimitsAtInfinityTest, ExpressionWithTrigonometricFunctionsWorks) {
    Term numerator(sin(Monomial(1, {{"x", -1}})));
    Term denominator(arctan(Monomial(1, {{"x", -1}})));
    Term term(createExpressionIfPossible({numerator, "/", denominator}));

    LimitsAtInfinity limits(term, "x");

    EXPECT_TRUE(isNan(limits.getSimplifiedTermAtInfinity()));
    EXPECT_TRUE(isNan(limits.getValueAtInfinity(ALBA_NUMBER_NEGATIVE_INFINITY)));
    EXPECT_TRUE(isNan(limits.getValueAtInfinity(ALBA_NUMBER_POSITIVE_INFINITY)));
}

}  // namespace algebra

}  // namespace alba
