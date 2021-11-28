#include <AprgUniqueProblems/DynamicProgramming/Other/ElevatorWeightProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using People = ElevatorWeightProblem::People;
using ListOfPeople = ElevatorWeightProblem::ListOfPeople;
}  // namespace

TEST(ElevatorWeightProblemTest, GetNumberOfOptimalRidesWorksOnExample1) {
    ElevatorWeightProblem queryForTest(10U, {2U, 3U, 3U, 5U, 6U});

    EXPECT_EQ(2U, queryForTest.getNumberOfOptimalRides());
}

}  // namespace alba
