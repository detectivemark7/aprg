#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Vector/PlaneMotionUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba {

namespace algebra {

namespace VectorUtilities {

TEST(PlaneMotionUtilitiesTest, GetInstantaneousVelocityWorks) {
    Term x(createExpressionIfPossible({getEAsATerm(), "^", "(", -2, "*", "t", ")"}));
    Term y(createExpressionIfPossible({3, "*", getEAsATerm(), "^", "t"}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getInstantaneousVelocity(termVector, "t"));

    string stringToExpect("{(-2/((e)^2[t])), (3*((e)^t))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(PlaneMotionUtilitiesTest, GetInstantaneousAccelerationFromVelocityWorks) {
    Term x(createExpressionIfPossible({getEAsATerm(), "^", "(", -2, "*", "t", ")"}));
    Term y(createExpressionIfPossible({3, "*", getEAsATerm(), "^", "t"}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getInstantaneousAccelerationFromVelocity(termVector, "t"));

    string stringToExpect("{(-2/((e)^2[t])), (3*((e)^t))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(PlaneMotionUtilitiesTest, GetInstantaneousAccelerationFromPathWorks) {
    Term x(Monomial(2, {{"t", 3}}));
    Term y(Monomial(4, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getInstantaneousAccelerationFromPath(termVector, "t"));

    string stringToExpect("{12[t], 8}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(PlaneMotionUtilitiesTest, GetTangentPartOfAccelerationWorks) {
    Term x(Monomial(2, {{"t", 3}}));
    Term y(Monomial(4, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getTangentPartOfAcceleration(termVector, "t"));

    string stringToExpect(
        "{((36[t^5] + 216[t^3] + 192[t])/((1[t^2] + 4)^(3/2))/((9[t^2] + 16)^(1/2))), ((48[t^4] + 288[t^2] + "
        "256)/((1[t^2] + 4)^(3/2))/((9[t^2] + 16)^(1/2)))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

TEST(PlaneMotionUtilitiesTest, GetNormalPartOfAccelerationWorks) {
    Term x(Monomial(2, {{"t", 3}}));
    Term y(Monomial(4, {{"t", 2}}));
    MathVectorOfTwoTerms termVector{x, y};

    MathVectorOfTwoTerms vectorToVerify(getNormalPartOfAcceleration(termVector, "t"));

    string stringToExpect(
        "{((864[t^5] + 4608[t^3] + 6144[t])/(81[t^6] + 612[t^4] + 1408[t^2] + 1024)), ((-648[t^6] + -3456[t^4] + "
        "-4608[t^2])/(81[t^6] + 612[t^4] + 1408[t^2] + 1024))}");
    EXPECT_EQ(stringToExpect, convertToString(vectorToVerify));
}

}  // namespace VectorUtilities

}  // namespace algebra

}  // namespace alba
