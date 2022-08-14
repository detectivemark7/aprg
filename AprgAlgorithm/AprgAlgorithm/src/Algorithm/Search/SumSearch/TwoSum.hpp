#pragma once

#include <functional>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class TwoSum {
public:
    // Another problem that can be solved using the two pointers method is the following problem,
    // also known as the 2SUM problem: given an array of n numbers and a target sum x,
    // find two array values such that their sum is x, or report that no such values exist.

    using Index = int;
    using Value = typename Values::value_type;
    using ValuePair = std::pair<Value, Value>;
    using Comparator = std::function<bool(Index const, Index const)>;

    TwoSum(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    ValuePair getNonDuplicateTwoValuesWithSum(Value const& targetSum) const {
        // std::less because index must be distinct
        return getTwoValuesWithSum(targetSum, 0, m_sortedValues.size() - 1, std::less<Index>());
    }

    ValuePair getNonDuplicateTwoValuesWithSum(
        Value const& targetSum, Index const lowIndex, Index const highIndex) const {
        // std::less because index must be distinct
        return getTwoValuesWithSum(targetSum, lowIndex, highIndex, std::less<Index>());
    }

    ValuePair getPossibleDuplicatedTwoValuesWithSum(Value const& targetSum) const {
        // std::less_equal because index can be equal
        return getTwoValuesWithSum(targetSum, 0, m_sortedValues.size() - 1, std::less_equal<Index>());
    }

    ValuePair getPossibleDuplicatedTwoValuesWithSum(
        Value const& targetSum, Index const lowIndex, Index const highIndex) const {
        // std::less_equal because index can be equal
        return getTwoValuesWithSum(targetSum, lowIndex, highIndex, std::less_equal<Index>());
    }

private:
    ValuePair getTwoValuesWithSum(
        Value const& targetSum, Index const lowIndex, Index const highIndex,
        Comparator const& shouldContinue) const {
        ValuePair result{};
        if (!m_sortedValues.empty()) {
            Index iLow = lowIndex, iHigh = highIndex;
            while (shouldContinue(iLow, iHigh)) {
                Value currentSum(m_sortedValues.at(iLow) + m_sortedValues.at(iHigh));
                if (currentSum == targetSum) {
                    result = {m_sortedValues.at(iLow), m_sortedValues.at(iHigh)};
                    break;
                } else if (currentSum > targetSum) {
                    --iHigh;
                } else {  // currentSum < targetSum
                    ++iLow;
                }
            }
        }
        return result;
    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
