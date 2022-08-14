#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class TernarySearch {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    TernarySearch(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    Index getIndexOfValue(Value const& value) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexOfValueWithoutCheck(0, m_sortedValues.size() - 1, value);
        }
        return result;
    }

    Index getIndexOfValue(Index const startIndex, Index const endIndex, Value const& value) const {
        Index result(INVALID_INDEX);
        if (startIndex < static_cast<Index>(m_sortedValues.size()) &&
            endIndex < static_cast<Index>(m_sortedValues.size()) && startIndex <= endIndex) {
            result = getIndexOfValueWithoutCheck(startIndex, endIndex, value);
        }
        return result;
    }

private:
    Index getIndexOfValueWithoutCheck(Index const lowIndex, Index const highIndex, Value const& value) const {
        // Based from https://en.wikipedia.org/wiki/Ternary_search#Algorithm

        Index result(INVALID_INDEX);
        if (lowIndex < highIndex) {
            Index firstMiddleIndex = (2 * lowIndex + highIndex) / 3;   // Note: possible overflow bug
            Index secondMiddleIndex = (lowIndex + 2 * highIndex) / 3;  // Note: possible overflow bug
            if (value < m_sortedValues.at(firstMiddleIndex)) {
                // if on the first one-third part
                result = getIndexOfValueWithoutCheck(lowIndex, firstMiddleIndex - 1, value);
            } else if (m_sortedValues.at(secondMiddleIndex) < value) {
                // if on the third one-third part
                result = getIndexOfValueWithoutCheck(secondMiddleIndex + 1, highIndex, value);
            } else {
                // if on the second one-third part
                result = getIndexOfValueWithoutCheck(firstMiddleIndex, secondMiddleIndex, value);
            }
        } else if (lowIndex == highIndex && value == m_sortedValues.at(lowIndex)) {
            result = lowIndex;
        }
        return result;
    }
    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba

// Which of the above two does less comparisons in worst case?
// From the first look, it seems the ternary search does less number of comparisons as it makes Log3n recursive calls,
// but binary search makes Log2n recursive calls.

// The following is recursive formula for counting comparisons in worst case of Binary Search.
// -> T(n) = T(n/2) + 2,  T(1) = 1

// The following is recursive formula for counting comparisons in worst case of Ternary Search.
// -> T(n) = T(n/3) + 4, T(1) = 1

// In binary search, there are 2Log2n + 1 comparisons in worst case. In ternary search, there are 4Log3n + 1 comparisons
// in worst case.
// -> Time Complexity for Binary search = 2clog2n + O(1)
// -> Time Complexity for Ternary search = 4clog3n + O(1)

// Therefore, the comparison of Ternary and Binary Searches boils down the comparison of expressions 2Log3n and Log2n .
// The value of 2Log3n can be written as (2 / Log2(3)) * Log2n .
// Since the value of (2 / Log23) is more than one, Ternary Search does more comparisons than Binary Search in worst
// case.
