#pragma once

#include <Algorithm/Search/Geometry/KdTree.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

#include <limits>

namespace alba {

namespace algorithm {

template <typename Key>
bool isEqualThanWithDepth(Key const& key1, Key const& key2, int const depth) {
    if (mathHelper::isOdd(depth)) {
        return key1.first == key2.first;
    } else {
        return key1.second == key2.second;
    }
}

template <typename Key>
bool isLessThanWithDepth(Key const& key1, Key const& key2, int const depth) {
    if (mathHelper::isOdd(depth)) {
        return key1.first < key2.first;
    } else {
        return key1.second < key2.second;
    }
}

template <typename Key>
bool isGreaterThanWithDepth(Key const& key1, Key const& key2, int const depth) {
    if (mathHelper::isOdd(depth)) {
        return key1.first > key2.first;
    } else {
        return key1.second > key2.second;
    }
}

template <typename Unit>
class NearestPointSearch {
public:
    using Point = std::pair<Unit, Unit>;
    using PointPair = std::pair<Point, Point>;
    using TwoDTree = KdTree<Point>;
    using NodeUniquePointer = typename TwoDTree::NodeUniquePointer;

    enum class SearchAction { Nothing, GoToLeftChild, GoToRightChild, GoToBoth };

    struct SearchDetails {
        Point pointToCheck;
        Point nearestPoint;
        Unit nearestDistance;
    };

    Point getNearestPoint(Point const& pointToCheck) const {
        Point result{};
        NodeUniquePointer const& root(m_twoDTree.getRoot());
        SearchDetails searchDetails{pointToCheck, root->key, getInitialMaxDistance()};
        searchNearestPoint(root, searchDetails);
        result = searchDetails.nearestPoint;
        return result;
    }

    PointPair getNearestPointPair() const {
        // This is O(n*log(n))
        PointPair result{};
        Unit nearestDistance(getInitialMaxDistance());
        for (Point const& pointToCheck : m_twoDTree.getKeys()) {
            NodeUniquePointer const& root(m_twoDTree.getRoot());
            SearchDetails searchDetails{pointToCheck, root->key, nearestDistance};
            searchNearestPoint(root, searchDetails);
            if (nearestDistance > searchDetails.nearestDistance) {
                nearestDistance = searchDetails.nearestDistance;
                result = {pointToCheck, searchDetails.nearestPoint};
            }
        }
        return result;
    }

    void addPoint(Point const& point) { m_twoDTree.put(point); }

private:
    void searchNearestPoint(NodeUniquePointer const& nodePointer, SearchDetails& searchDetails) const {
        static int depth = 0;
        depth++;
        if (nodePointer) {
            Point const& currentPoint(nodePointer->key);
            if (currentPoint != searchDetails.pointToCheck)  // only consider other points
            {
                Unit currentDistance(getDistance(currentPoint, searchDetails.pointToCheck));
                if (currentDistance < searchDetails.nearestDistance) {
                    searchDetails.nearestPoint = currentPoint;
                    searchDetails.nearestDistance = currentDistance;
                }
                SearchAction searchAction(getSearchAction(nodePointer, searchDetails.pointToCheck, depth));
                if (SearchAction::GoToLeftChild == searchAction || SearchAction::GoToBoth == searchAction) {
                    searchNearestPoint(nodePointer->left, searchDetails);
                }
                if (SearchAction::GoToRightChild == searchAction || SearchAction::GoToBoth == searchAction) {
                    searchNearestPoint(nodePointer->right, searchDetails);
                }
            }
        }
        depth--;
    }

    SearchAction getSearchAction(
        NodeUniquePointer const& nodePointer, Point const& pointToCheck, int const depth) const {
        SearchAction result(SearchAction::Nothing);
        if (nodePointer) {
            Point const& currentPoint(nodePointer->key);
            if (mathHelper::isOdd(depth)) {
                if (pointToCheck.first < currentPoint.first)  // point to check is to the left (arrangement * <- N)
                {
                    if (nodePointer->left) {
                        if (pointToCheck.first <
                            nodePointer->left->key
                                .first)  // point to check is to the left of left child  (arrangement * <- L <- N)
                        {
                            result = SearchAction::GoToLeftChild;
                        } else  // point to check is to the right of left child  (arrangement L <- * <- N)
                        {
                            result = SearchAction::GoToBoth;
                        }
                    } else if (nodePointer->right) {
                        result = SearchAction::GoToRightChild;
                    }
                } else  // point to check is to the right (arrangement N -> *)
                {
                    if (nodePointer->right) {
                        if (nodePointer->right->key.first <
                            pointToCheck
                                .first)  // point to check is to the right of right child  (arrangement N -> R -> *)
                        {
                            result = SearchAction::GoToRightChild;
                        } else  // point to check is to the left of right child  (arrangement N -> * -> R)
                        {
                            result = SearchAction::GoToBoth;
                        }
                    } else if (nodePointer->left) {
                        result = SearchAction::GoToLeftChild;
                    }
                }
            } else {
                // same logic but top and bottom
                if (pointToCheck.second < currentPoint.second)  // point to check is to the left (arrangement * <- N)
                {
                    if (nodePointer->left) {
                        if (pointToCheck.second <
                            nodePointer->left->key
                                .second)  // point to check is to the left of left child  (arrangement * <- L <- N)
                        {
                            result = SearchAction::GoToLeftChild;
                        } else  // point to check is to the right of left child  (arrangement L <- * <- N)
                        {
                            result = SearchAction::GoToBoth;
                        }
                    } else if (nodePointer->right) {
                        result = SearchAction::GoToRightChild;
                    }
                } else  // point to check is to the right (arrangement N -> *)
                {
                    if (nodePointer->right) {
                        if (nodePointer->right->key.second <
                            pointToCheck
                                .second)  // point to check is to the right of right child  (arrangement N -> R -> *)
                        {
                            result = SearchAction::GoToRightChild;
                        } else  // point to check is to the left of right child  (arrangement N -> * -> R)
                        {
                            result = SearchAction::GoToBoth;
                        }
                    } else if (nodePointer->left) {
                        result = SearchAction::GoToLeftChild;
                    }
                }
            }
        }
        return result;
    }

    inline Unit getDistance(Point const& point1, Point const& point2) const {
        return mathHelper::getSquareRootOfXSquaredPlusYSquared(
            point1.first - point2.first, point1.second - point2.second);
    }

    inline Unit getInitialMaxDistance() const { return std::numeric_limits<Unit>::max(); }

    TwoDTree m_twoDTree;
};

}  // namespace algorithm

}  // namespace alba
