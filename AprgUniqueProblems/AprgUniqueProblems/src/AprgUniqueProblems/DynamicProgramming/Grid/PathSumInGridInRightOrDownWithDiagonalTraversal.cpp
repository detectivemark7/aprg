#include "PathSumInGridInRightOrDownWithDiagonalTraversal.hpp"

using namespace std;

namespace alba {

PathSumInGridInRightOrDownWithDiagonalTraversal::PathSumInGridInRightOrDownWithDiagonalTraversal(
    Type const type, Grid const& inputGrid)
    : m_inputGrid(inputGrid) {
    initialize(type);
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Value
PathSumInGridInRightOrDownWithDiagonalTraversal::getBestPathSumUsingNaiveRecursion() const {
    Value pathSum(0);
    if (!m_inputGrid.isEmpty()) {
        pathSum =
            getBestPathSumUsingNaiveRecursion(m_inputGrid.getNumberOfColumns() - 1, m_inputGrid.getNumberOfRows() - 1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Value
PathSumInGridInRightOrDownWithDiagonalTraversal::getBestPathSumUsingMemoizationDP() const {
    Value pathSum(0);
    if (!m_inputGrid.isEmpty()) {
        Grid partialSumGrid(m_inputGrid.getNumberOfColumns(), m_inputGrid.getNumberOfRows(), UNUSED_VALUE);
        pathSum = getBestPathSumUsingMemoizationDP(
            partialSumGrid, m_inputGrid.getNumberOfColumns() - 1, m_inputGrid.getNumberOfRows() - 1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Value
PathSumInGridInRightOrDownWithDiagonalTraversal::getBestPathSumUsingIterativeDP() const {
    // Time Complexity of the DP implementation is O(mn) which is much better than Naive Recursive implementation.

    Value pathSum(0);
    if (!m_inputGrid.isEmpty()) {
        Grid partialSumGrid(getPartialSumGridUsingIterativeDP());
        pathSum =
            partialSumGrid.getEntry(partialSumGrid.getNumberOfColumns() - 1, partialSumGrid.getNumberOfRows() - 1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Path
PathSumInGridInRightOrDownWithDiagonalTraversal::getBestPathUsingIterativeDP() const {
    Path path;
    if (!m_inputGrid.isEmpty()) {
        Grid partialSumGrid(getPartialSumGridUsingIterativeDP());
        Index x = partialSumGrid.getNumberOfColumns() - 1, y = partialSumGrid.getNumberOfRows() - 1;
        path = {m_inputGrid.getEntry(x, y)};
        while (true) {
            if (x == 0 && y == 0) {
                break;
            } else if (x == 0) {
                path.emplace_back(m_inputGrid.getEntry(x, --y));
            } else if (y == 0) {
                path.emplace_back(m_inputGrid.getEntry(--x, y));
            } else {
                Value bestNeighbor = m_minMaxFunction(
                    m_minMaxFunction(partialSumGrid.getEntry(x - 1, y), partialSumGrid.getEntry(x, y - 1)),
                    partialSumGrid.getEntry(x - 1, y - 1));
                if (bestNeighbor == partialSumGrid.getEntry(x - 1, y)) {
                    path.emplace_back(m_inputGrid.getEntry(--x, y));
                } else if (bestNeighbor == partialSumGrid.getEntry(x, y - 1)) {
                    path.emplace_back(m_inputGrid.getEntry(x, --y));
                } else if (bestNeighbor == partialSumGrid.getEntry(x - 1, y - 1)) {
                    path.emplace_back(m_inputGrid.getEntry(--x, --y));
                }
            }
        }
        reverse(path.begin(), path.end());
    }
    return path;
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Value
PathSumInGridInRightOrDownWithDiagonalTraversal::getBestPathSumUsingNaiveRecursion(Index const x, Index const y) const {
    // Naive recursion approach

    Value result(m_inputGrid.getEntry(x, y));
    if (!(x == 0 && y == 0)) {
        if (x == 0) {
            result += getBestPathSumUsingNaiveRecursion(x, y - 1);
        } else if (y == 0) {
            result += getBestPathSumUsingNaiveRecursion(x - 1, y);
        } else {
            // diagonal is included
            result += m_minMaxFunction(
                m_minMaxFunction(
                    getBestPathSumUsingNaiveRecursion(x - 1, y), getBestPathSumUsingNaiveRecursion(x, y - 1)),
                getBestPathSumUsingNaiveRecursion(x - 1, y - 1));
        }
    }
    return result;
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Grid
PathSumInGridInRightOrDownWithDiagonalTraversal::getPartialSumGridUsingIterativeDP() const {
    Grid result(m_inputGrid);
    for (Index x = 1; x < result.getNumberOfColumns(); x++)  // first row has only left neighbors
    {
        result.getEntryReference(x, 0) += result.getEntry(x - 1, 0);
    }
    for (Index y = 1; y < result.getNumberOfRows(); y++)  // first column has only up neighbors
    {
        result.getEntryReference(0, y) += result.getEntry(0, y - 1);
    }
    for (Index x = 1; x < result.getNumberOfColumns(); x++)  // the rest of the matrix
    {
        for (Index y = 1; y < result.getNumberOfRows(); y++) {
            // diagonal is included
            result.getEntryReference(x, y) += m_minMaxFunction(
                m_minMaxFunction(result.getEntry(x - 1, y), result.getEntry(x, y - 1)), result.getEntry(x - 1, y - 1));
        }
    }
    return result;
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Value
PathSumInGridInRightOrDownWithDiagonalTraversal::getBestPathSumUsingMemoizationDP(
    Grid& partialSumGrid, Index const x, Index const y) const {
    Value result(partialSumGrid.getEntry(x, y));
    if (UNUSED_VALUE == result) {
        result = m_inputGrid.getEntry(x, y);
        if (!(x == 0 && y == 0)) {
            if (x == 0) {
                result += getBestPathSumUsingMemoizationDP(partialSumGrid, x, y - 1);
            } else if (y == 0) {
                result += getBestPathSumUsingMemoizationDP(partialSumGrid, x - 1, y);
            } else {
                result += m_minMaxFunction(
                    m_minMaxFunction(
                        getBestPathSumUsingMemoizationDP(partialSumGrid, x - 1, y),
                        getBestPathSumUsingMemoizationDP(partialSumGrid, x, y - 1)),
                    getBestPathSumUsingMemoizationDP(partialSumGrid, x - 1, y - 1));
            }
        }
        partialSumGrid.setEntry(x, y, result);
    }
    return result;
}

void PathSumInGridInRightOrDownWithDiagonalTraversal::initialize(Type const type) {
    if (Type::MinimumSum == type) {
        m_compareFunction = less_equal<>();
        m_minMaxFunction = [](Value const& value1, Value const& value2) { return min(value1, value2); };
    } else if (Type::MaximumSum == type) {
        m_compareFunction = greater_equal<>();
        m_minMaxFunction = [](Value const& value1, Value const& value2) { return max(value1, value2); };
    }
}

}  // namespace alba
