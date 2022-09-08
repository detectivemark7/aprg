#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class BinarySearchWithTwoIndices {
public:
    using Index = int;
    using Value = typename Values::value_type;
    static constexpr Index INVALID_INDEX = getInvalidIndex<Index>();

    BinarySearchWithTwoIndices(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    Index getIndexOfValue(Value const& target) const {
        Index result(INVALID_INDEX);
        if (!m_sortedValues.empty()) {
            result = getIndexUsingInterval(0, m_sortedValues.size() - 1, target);
        }
        return result;
    }

    Index getIndexOfValue(Index const startIndex, Index const endIndex, Value const& target) const {
        Index result(INVALID_INDEX);
        if (startIndex < static_cast<Index>(m_sortedValues.size()) &&
            endIndex < static_cast<Index>(m_sortedValues.size()) && startIndex <= endIndex) {
            result = getIndexUsingInterval(startIndex, endIndex, target);
        }
        return result;
    }

private:
    Index getIndexUsingInterval(Index const startIndex, Index const endIndex, Value const& target) const {
        Index result(INVALID_INDEX);
        Index lowIndex(startIndex), highIndex(endIndex);
        while (lowIndex <= highIndex) {
            Index middleIndex = getMidpointOfIndexes(lowIndex, highIndex);
            Value middleValue(m_sortedValues[middleIndex]);
            if (target < middleValue) {
                highIndex = middleIndex - 1;
            } else if (middleValue < target) {
                lowIndex = middleIndex + 1;
            } else {  // target == middleValue
                result = middleIndex;
                break;
            }
        }
        return result;
    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba

// The usual way to implement binary search resembles looking for a word in a dictionary.
// The search maintains an active region in the array, which initially contains all array elements.
// Then, a number of steps is performed, each of which halves the size of the region.

// At each step, the search checks the middle element of the active region.
// If the middle element is the target element, the search terminates.
// Otherwise, the search recursively continues to the left or right half of the region, depending on the target of the
// middle element.

// In this implementation, the active region is a...b, and initially the region is 0...n-1.
// The algorithm halves the size of the region at each step, so the time complexity is O(logn).
