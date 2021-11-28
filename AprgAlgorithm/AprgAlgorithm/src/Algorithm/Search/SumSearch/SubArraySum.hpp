#pragma once

namespace alba {

namespace algorithm {

template <typename Values>
class SubArraySum {
public:
    // As the first example, consider a problem where we are given an array of n positive integers and a target sum x,
    // and we want to find a subarray whose sum is x or report that there is no such subarray.

    using Index = unsigned int;
    using Value = typename Values::value_type;

    SubArraySum(Values const& valuesToCheck) : m_valuesToCheck(valuesToCheck) {}

    Values getSubArrayWithSum(Value const& targetSum) const {
        Values result;
        if (!m_valuesToCheck.empty()) {
            Index start = 0, end = 0, size = m_valuesToCheck.size();
            Value currentSum = m_valuesToCheck.at(0);
            while (start < size && end < size) {
                if (currentSum == targetSum) {
                    result = Values(m_valuesToCheck.cbegin() + start, m_valuesToCheck.cbegin() + end + 1);
                    break;
                } else if (currentSum > targetSum) {
                    if (start < end) {
                        currentSum -= m_valuesToCheck.at(start);
                        start++;
                    } else if (end + 1 < size) {
                        start++;
                        end++;
                        currentSum = m_valuesToCheck.at(end);
                    } else {
                        break;
                    }
                } else if (currentSum < targetSum) {
                    if (end + 1 < size) {
                        end++;
                        currentSum += m_valuesToCheck.at(end);
                    } else {
                        break;
                    }
                }
            }
        }
        return result;
    }

private:
    Values const& m_valuesToCheck;
};

}  // namespace algorithm

}  // namespace alba
