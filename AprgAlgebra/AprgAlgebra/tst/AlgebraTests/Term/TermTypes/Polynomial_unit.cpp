#include <Algebra/Term/TermTypes/Polynomial.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba {

namespace algebra {

TEST(PolynomialTest, PolynomialsAreConstructedCorrectly) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    Monomials const& monomials1(polynomial1.getMonomialsConstReference());
    ASSERT_TRUE(monomials1.empty());

    Monomials const& monomials2(polynomial2.getMonomialsConstReference());
    ASSERT_EQ(2U, monomials2.size());
    EXPECT_DOUBLE_EQ(6, monomials2.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials2.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(-7, monomials2.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials2.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(3U, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(3, variableMap2.at("y").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap2.at("z").getDouble());
}

TEST(PolynomialTest, ConstructedPolynomialsHaveIsSimplifiedFlagNotSet) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    EXPECT_FALSE(polynomial1.isSimplified());
    EXPECT_FALSE(polynomial2.isSimplified());
}

TEST(PolynomialTest, EqualityOperatorWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};
    Polynomial polynomial3{Monomial(6, {}), Monomial(68, {{"x", 2}, {"y", 3}, {"z", 4}})};
    Polynomial polynomial4{Monomial(6, {})};
    Polynomial polynomial5{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    EXPECT_TRUE(polynomial1 == polynomial1);
    EXPECT_FALSE(polynomial1 == polynomial2);
    EXPECT_TRUE(polynomial2 == polynomial2);
    EXPECT_FALSE(polynomial2 == polynomial3);
    EXPECT_FALSE(polynomial2 == polynomial4);
    EXPECT_TRUE(polynomial2 == polynomial5);
}

TEST(PolynomialTest, LessThanOperatorWorks) {
    EXPECT_FALSE(Polynomial() < Polynomial());
    EXPECT_FALSE(
        Polynomial({Monomial(6, {}), Monomial(7, {{"x", 2}, {"y", 3}})}) <
        Polynomial({Monomial(6, {}), Monomial(7, {{"x", 2}, {"y", 3}})}));
    EXPECT_FALSE(Polynomial({Monomial(6, {}), Monomial(7, {{"x", 2}, {"y", 3}})}) < Polynomial({Monomial(6, {})}));
    EXPECT_TRUE(
        Polynomial({Monomial(6, {}), Monomial(7, {{"x", 2}, {"y", 3}})}) <
        Polynomial({Monomial(6, {}), Monomial(8, {{"x", 1}}), Monomial(7, {{"x", 2}, {"y", 3}})}));
    EXPECT_FALSE(
        Polynomial({Monomial(6, {}), Monomial(7, {{"x", 2}, {"y", 3}})}) <
        Polynomial({Monomial(6, {}), Monomial(6, {{"x", 2}, {"y", 3}})}));
    EXPECT_TRUE(
        Polynomial({Monomial(6, {}), Monomial(7, {{"x", 2}, {"y", 3}})}) <
        Polynomial({Monomial(6, {}), Monomial(8, {{"x", 2}, {"y", 3}})}));
}

TEST(PolynomialTest, IsEmptyWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(6, {})};

    EXPECT_TRUE(polynomial1.isEmpty());
    EXPECT_FALSE(polynomial2.isEmpty());
}

TEST(PolynomialTest, IsSimplifiedWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2;
    polynomial2.setAsSimplified();

    EXPECT_FALSE(polynomial1.isSimplified());
    EXPECT_TRUE(polynomial2.isSimplified());
}

TEST(PolynomialTest, GetMonomialsConstReferenceWorks) {
    Polynomial polynomial{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    Monomials const& monomials(polynomial.getMonomialsConstReference());

    ASSERT_EQ(2U, monomials.size());
    EXPECT_DOUBLE_EQ(6, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(-7, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(3U, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(3, variableMap2.at("y").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap2.at("z").getDouble());
}

TEST(PolynomialTest, GetMonomialsReferenceWorks) {
    Polynomial polynomial{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    Monomials& monomialsToChange(polynomial.getMonomialsReference());
    monomialsToChange.at(0).setConstant(22);
    monomialsToChange.at(1).putVariableWithExponent("a", 5);

    Monomials const& monomialsToCheck(polynomial.getMonomialsConstReference());
    ASSERT_EQ(2U, monomialsToCheck.size());
    EXPECT_DOUBLE_EQ(22, monomialsToCheck.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(
        monomialsToCheck.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(-7, monomialsToCheck.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(
        monomialsToCheck.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(4U, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(3, variableMap2.at("y").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap2.at("z").getDouble());
    EXPECT_DOUBLE_EQ(5, variableMap2.at("a").getDouble());
}

TEST(PolynomialTest, ClearWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(6, {})};
    Polynomial polynomial3{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    polynomial1.clear();
    polynomial2.clear();
    polynomial3.clear();

    EXPECT_TRUE(polynomial1.isEmpty());
    EXPECT_TRUE(polynomial2.isEmpty());
    EXPECT_TRUE(polynomial3.isEmpty());
}

TEST(PolynomialTest, SimplifyWorks) {
    Polynomial polynomial1{Monomial(0, {{"x", 1}}), Monomial(0, {{"x", 1}})};
    Polynomial polynomial2{Monomial(6, {})};
    Polynomial polynomial3{Monomial(6, {}), Monomial(-6, {})};
    Polynomial polynomial4{Monomial(-6, {{"y", 0}, {"z", 0}})};
    Polynomial polynomial5{Monomial(1, {{"x", 2}}), Monomial(3, {{"x", ALBA_NUMBER_NOT_A_NUMBER}})};

    polynomial1.simplify();
    polynomial2.simplify();
    polynomial3.simplify();
    polynomial4.simplify();
    polynomial5.simplify();

    Monomials const& monomials1(polynomial1.getMonomialsConstReference());
    ASSERT_TRUE(monomials1.empty());

    Monomials const& monomials2(polynomial2.getMonomialsConstReference());
    ASSERT_EQ(1U, monomials2.size());
    EXPECT_DOUBLE_EQ(6, monomials2.at(0).getConstantConstReference().getDouble());
    ASSERT_TRUE(monomials2.at(0).getVariablesToExponentsMapConstReference().empty());

    Monomials const& monomials3(polynomial3.getMonomialsConstReference());
    ASSERT_TRUE(monomials3.empty());

    Monomials const& monomials4(polynomial4.getMonomialsConstReference());
    ASSERT_EQ(1U, monomials4.size());
    EXPECT_DOUBLE_EQ(-6, monomials4.at(0).getConstantConstReference().getDouble());
    ASSERT_TRUE(monomials4.at(0).getVariablesToExponentsMapConstReference().empty());

    Monomials const& monomials5(polynomial5.getMonomialsConstReference());
    ASSERT_EQ(1U, monomials5.size());
    EXPECT_TRUE(monomials5.at(0).getConstantConstReference().isNotANumber());
    ASSERT_TRUE(monomials5.at(0).getVariablesToExponentsMapConstReference().empty());
}

TEST(PolynomialTest, SimplifyWorksAndItSortsMonomials) {
    Polynomial polynomial1;
    Polynomial polynomial2{
        Monomial(100, {}), Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}), Monomial(9, {{"x", 8}}), Monomial(10, {})};
    Polynomial polynomial3{
        Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 1}, {"y", 2}}),
        Monomial(5, {{"x", 3}})};

    polynomial1.simplify();
    polynomial2.simplify();
    polynomial3.simplify();

    EXPECT_EQ(Polynomial(), polynomial1);
    EXPECT_EQ(
        (Polynomial{Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}), Monomial(9, {{"x", 8}}), Monomial(110, {})}),
        polynomial2);
    EXPECT_EQ((Polynomial{Monomial(6, {{"x", 3}}), Monomial(2, {{"x", 1}, {"y", 2}})}), polynomial3);
}

TEST(PolynomialTest, SimplifyWorksWhenIsSimplifiedIsNotSet) {
    Polynomial polynomial{Monomial(-6, {{"y", 0}, {"z", 0}})};

    polynomial.simplify();

    Monomials const& monomials(polynomial.getMonomialsConstReference());
    ASSERT_EQ(1U, monomials.size());
    EXPECT_DOUBLE_EQ(-6, monomials.at(0).getConstantConstReference().getDouble());
    ASSERT_TRUE(monomials.at(0).getVariablesToExponentsMapConstReference().empty());
}

TEST(PolynomialTest, SimplifyWorksAsSkippedWhenIsSimplifiedIsSet) {
    Polynomial polynomial{Monomial(-6, {{"y", 0}, {"z", 0}})};
    polynomial.setAsSimplified();

    polynomial.simplify();

    Monomials const& monomials(polynomial.getMonomialsConstReference());
    ASSERT_EQ(1U, monomials.size());
    EXPECT_DOUBLE_EQ(-6, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableToExponentMap(
        monomials.at(0).getVariablesToExponentsMapConstReference());
    EXPECT_EQ(2U, variableToExponentMap.size());
    auto it = variableToExponentMap.cbegin();
    EXPECT_EQ("y", it->first);
    EXPECT_EQ(AlbaNumber(0), it->second);
    it++;
    EXPECT_EQ("z", it->first);
    EXPECT_EQ(AlbaNumber(0), it->second);
}

TEST(PolynomialTest, SimplifyWithNotANumberDoesNotCrash) {
    Polynomial polynomial{Monomial(ALBA_NUMBER_NOT_A_NUMBER, {})};

    polynomial.simplify();

    Monomials const& monomials(polynomial.getMonomialsConstReference());
    ASSERT_EQ(1U, monomials.size());
    EXPECT_TRUE(monomials.at(0).getConstantConstReference().isNotANumber());
}

TEST(PolynomialTest, SortWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{
        Monomial(100, {}), Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}), Monomial(9, {{"x", 8}}), Monomial(10, {})};
    Polynomial polynomial3{
        Monomial(1, {{"y", 3}}), Monomial(1, {{"x", 1}, {"y", 2}}), Monomial(1, {{"x", 2}, {"y", 1}}),
        Monomial(5, {{"x", 3}})};

    polynomial1.sortMonomialsWithInversePriority();
    polynomial2.sortMonomialsWithInversePriority();
    polynomial3.sortMonomialsWithInversePriority();

    EXPECT_EQ(Polynomial(), polynomial1);
    EXPECT_EQ(
        (Polynomial{
            Monomial(5, {{"x", 2}, {"y", 3}, {"z", 4}}), Monomial(9, {{"x", 8}}), Monomial(100, {}), Monomial(10, {})}),
        polynomial2);
    EXPECT_EQ(
        (Polynomial{
            Monomial(5, {{"x", 3}}), Monomial(1, {{"x", 2}, {"y", 1}}), Monomial(1, {{"x", 1}, {"y", 2}}),
            Monomial(1, {{"y", 3}})}),
        polynomial3);
}

TEST(PolynomialTest, AddMonomialWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(1, {})};
    Polynomial polynomial3{Monomial(2, {}), Monomial(3, {{"x", 4}})};

    polynomial1.addMonomial(Monomial(5, {{"x", 4}}));
    polynomial2.addMonomial(Monomial(5, {{"x", 4}}));
    polynomial3.addMonomial(Monomial(5, {{"x", 4}}));

    EXPECT_EQ(Polynomial{Monomial(5, {{"x", 4}})}, polynomial1);
    EXPECT_EQ((Polynomial{Monomial(1, {}), Monomial(5, {{"x", 4}})}), polynomial2);
    EXPECT_EQ((Polynomial{Monomial(2, {}), Monomial(8, {{"x", 4}})}), polynomial3);
}

TEST(PolynomialTest, AddPolynomialWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(1, {})};
    Polynomial polynomial3{Monomial(2, {}), Monomial(3, {{"x", 4}})};

    polynomial1.addPolynomial(Polynomial{Monomial(7, {{"x", 4}}), Monomial(9, {{"y", 8}})});
    polynomial2.addPolynomial(Polynomial{Monomial(7, {{"x", 4}}), Monomial(9, {{"y", 8}})});
    polynomial3.addPolynomial(Polynomial{Monomial(7, {{"x", 4}}), Monomial(9, {{"y", 8}})});

    EXPECT_EQ((Polynomial{Monomial(7, {{"x", 4}}), Monomial(9, {{"y", 8}})}), polynomial1);
    EXPECT_EQ((Polynomial{Monomial(1, {}), Monomial(7, {{"x", 4}}), Monomial(9, {{"y", 8}})}), polynomial2);
    EXPECT_EQ((Polynomial{Monomial(2, {}), Monomial(10, {{"x", 4}}), Monomial(9, {{"y", 8}})}), polynomial3);
}

TEST(PolynomialTest, MultiplyNumberWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(1, {})};
    Polynomial polynomial3{Monomial(2, {}), Monomial(3, {{"x", 4}})};

    polynomial1.multiplyNumber(5);
    polynomial2.multiplyNumber(5);
    polynomial3.multiplyNumber(5);

    EXPECT_EQ(Polynomial(), polynomial1);
    EXPECT_EQ((Polynomial{Monomial(5, {})}), polynomial2);
    EXPECT_EQ((Polynomial{Monomial(10, {}), Monomial(15, {{"x", 4}})}), polynomial3);
}

TEST(PolynomialTest, DivideNumberWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(5, {})};
    Polynomial polynomial3{Monomial(10, {}), Monomial(15, {{"x", 4}})};

    polynomial1.divideNumber(5);
    polynomial2.divideNumber(5);
    polynomial3.divideNumber(5);

    EXPECT_EQ(Polynomial(), polynomial1);
    EXPECT_EQ((Polynomial{Monomial(1, {})}), polynomial2);
    EXPECT_EQ((Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})}), polynomial3);
}

TEST(PolynomialTest, MultiplyMonomialWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(1, {})};
    Polynomial polynomial3{Monomial(2, {}), Monomial(3, {{"x", 4}})};

    polynomial1.multiplyMonomial(Monomial(5, {{"x", 4}}));
    polynomial2.multiplyMonomial(Monomial(5, {{"x", 4}}));
    polynomial3.multiplyMonomial(Monomial(5, {{"x", 4}}));

    EXPECT_EQ(Polynomial(), polynomial1);
    EXPECT_EQ((Polynomial{Monomial(5, {{"x", 4}})}), polynomial2);
    EXPECT_EQ((Polynomial{Monomial(10, {{"x", 4}}), Monomial(15, {{"x", 8}})}), polynomial3);
}

TEST(PolynomialTest, MultiplyPolynomialWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(1, {})};
    Polynomial polynomial3{Monomial(2, {}), Monomial(3, {{"x", 4}})};

    polynomial1.multiplyPolynomial(Polynomial{Monomial(7, {{"x", 4}}), Monomial(9, {{"y", 8}})});
    polynomial2.multiplyPolynomial(Polynomial{Monomial(7, {{"x", 4}}), Monomial(9, {{"y", 8}})});
    polynomial3.multiplyPolynomial(Polynomial{Monomial(7, {{"x", 4}}), Monomial(9, {{"y", 8}})});

    EXPECT_EQ(Polynomial(), polynomial1);
    EXPECT_EQ((Polynomial{Monomial(7, {{"x", 4}}), Monomial(9, {{"y", 8}})}), polynomial2);
    EXPECT_EQ(
        (Polynomial{
            Monomial(14, {{"x", 4}}), Monomial(21, {{"x", 8}}), Monomial(18, {{"y", 8}}),
            Monomial(27, {{"x", 4}, {"y", 8}})}),
        polynomial3);
}

TEST(PolynomialTest, MultiplyPolynomialUsingExample1Works) {
    Polynomial polynomial1{Monomial(3, {{"x", 2}}), Monomial(-12, {{"x", 1}}), Monomial(-2, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 2}}), Monomial(4, {{"x", 1}}), Monomial(6, {})};

    polynomial1.multiplyPolynomial(polynomial2);

    Polynomial polynomialToExpect{
        Monomial(3, {{"x", 4}}), Monomial(0, {{"x", 3}}), Monomial(-32, {{"x", 2}}), Monomial(-80, {{"x", 1}}),
        Monomial(-12, {})};
    EXPECT_EQ(polynomialToExpect, polynomial1);
}

TEST(PolynomialTest, DivideMonomialWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(10, {})};
    Polynomial polynomial3{Monomial(20, {}), Monomial(30, {{"x", 4}})};

    polynomial1.divideMonomial(Monomial(5, {{"x", 4}}));
    polynomial2.divideMonomial(Monomial(5, {{"x", 4}}));
    polynomial3.divideMonomial(Monomial(5, {{"x", 4}}));

    EXPECT_EQ(Polynomial(), polynomial1);
    EXPECT_EQ((Polynomial{Monomial(2, {{"x", -4}})}), polynomial2);
    EXPECT_EQ((Polynomial{Monomial(4, {{"x", -4}}), Monomial(6, {{"x", 0}})}), polynomial3);
}

TEST(PolynomialTest, RaiseToUnsignedIntegerWorks) {
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(10, {})};
    Polynomial polynomial3{Monomial(20, {}), Monomial(30, {{"x", 4}})};

    polynomial1.raiseToUnsignedInteger(2U);
    polynomial2.raiseToUnsignedInteger(2U);
    polynomial3.raiseToUnsignedInteger(2U);

    EXPECT_EQ(Polynomial(), polynomial1);
    EXPECT_EQ((Polynomial{Monomial(100, {})}), polynomial2);
    EXPECT_EQ((Polynomial{Monomial(400, {}), Monomial(1200, {{"x", 4}}), Monomial(900, {{"x", 8}})}), polynomial3);
}

TEST(PolynomialTest, SetAsSimplifiedWorks) {
    Polynomial polynomial;

    polynomial.setAsSimplified();

    EXPECT_TRUE(polynomial.isSimplified());
}

TEST(PolynomialTest, ClearSimplifiedFlagWorks) {
    Polynomial polynomial;
    polynomial.setAsSimplified();

    polynomial.clearSimplifiedFlag();

    EXPECT_FALSE(polynomial.isSimplified());
}

TEST(PolynomialTest, OutputStreamOperatorWorks) {
    stringstream ss;
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(6, {})};
    Polynomial polynomial3{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};

    ss << polynomial1 << "," << polynomial2 << "," << polynomial3;

    EXPECT_EQ("(EmptyPolynomial),(6),(6 + -7[x^2][y^3][z^4])", ss.str());
}

}  // namespace algebra

}  // namespace alba
