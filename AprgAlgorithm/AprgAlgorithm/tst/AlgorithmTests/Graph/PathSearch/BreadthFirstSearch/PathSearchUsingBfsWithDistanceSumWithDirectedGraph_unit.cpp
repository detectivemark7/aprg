#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/PathSearch/BreadthFirstSearch/PathSearchUsingBfsWithDistanceSum.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using WeightForTest = double;
using ContentMapForTest = GraphTypesWithWeights<VertexForTest, WeightForTest>::VertexToWeightMap;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedDirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, DirectedGraphForTest>;
using PathSearchForTest = PathSearchUsingBfsWithDistanceSum<VertexForTest, WeightForTest, EdgeWeightedDirectedGraphForTest>;

void putConnectionsForTest(EdgeWeightedDirectedGraphForTest & graph)
{
    graph.connect(0U, 1U, 0.05);
    graph.connect(0U, 2U, 0.10);
    graph.connect(0U, 5U, 0.15);
    graph.connect(1U, 2U, 0.20);
    graph.connect(2U, 3U, 0.25);
    graph.connect(2U, 4U, 0.30);
    graph.connect(3U, 4U, 0.35);
    graph.connect(3U, 5U, 0.40);
}
}

TEST(PathSearchUsingBfsWithDistanceSumTest, GetDistanceToWorksWithDirectedGraph)
{
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0U});

    EXPECT_DOUBLE_EQ(0, pathSearch.getDistanceTo(0U));
    EXPECT_DOUBLE_EQ(0.05, pathSearch.getDistanceTo(1U));
    EXPECT_DOUBLE_EQ(0.1, pathSearch.getDistanceTo(2U));
    EXPECT_DOUBLE_EQ(0.35, pathSearch.getDistanceTo(3U));
    EXPECT_DOUBLE_EQ(0.4, pathSearch.getDistanceTo(4U));
    EXPECT_DOUBLE_EQ(0.15, pathSearch.getDistanceTo(5U));
    EXPECT_DOUBLE_EQ(0, pathSearch.getDistanceTo(6U));
}

TEST(PathSearchUsingBfsWithDistanceSumTest, GetEndVertexToDistanceSumMapWorksWithDirectedGraph)
{
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0U});

    ContentMapForTest expectedMap{{0U, 0.0}, {1U, 0.05}, {2U, 0.1}, {3U, 0.35}, {4U, 0.4}, {5U, 0.15}};
    EXPECT_EQ(expectedMap, pathSearch.getEndVertexToDistanceSumMap());
}

}

}
