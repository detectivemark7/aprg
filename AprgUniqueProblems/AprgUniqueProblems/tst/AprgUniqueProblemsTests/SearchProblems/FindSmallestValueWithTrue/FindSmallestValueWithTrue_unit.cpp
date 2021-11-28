#include <AprgUniqueProblems/SearchProblems/FindSmallestValueWithTrue/FindSmallestValueWithTrue.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValueForTest = unsigned int;
using SearchForTest = FindSmallestValueWithTrue<ValueForTest>;
}  // namespace

TEST(FindSmallestValueWithTrueTest, GetNearestValueWorksWhenItsAlwaysFalse) {
    SearchForTest binarySearch([](ValueForTest const) { return false; });

    EXPECT_EQ(0U, binarySearch.getSmallestValueWithTrue(45U, 500U));
}

TEST(FindSmallestValueWithTrueTest, GetNearestValueWorksWhenThereAreMultipleValues) {
    SearchForTest binarySearch([](ValueForTest const value) { return value >= 111U; });

    EXPECT_EQ(111U, binarySearch.getSmallestValueWithTrue(45U, 500U));
}

}  // namespace algorithm

}  // namespace alba
