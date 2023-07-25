#pragma once

#include <Algorithm/Graph/ConnectedComponents/ConnectedComponentsUsingDfs.hpp>
#include <Algorithm/Graph/PathSearch/EulerPaths/UndirectedGraph/BaseEulerPathSearchForUndirectedGraph.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <algorithm>

namespace alba {

namespace algorithm {

template <typename Vertex>
class FleuryAlgorithm : public BaseEulerPathSearchForUndirectedGraph<Vertex> {
public:
    using BaseClass = BaseEulerPathSearchForUndirectedGraph<Vertex>;
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using SetOfEdges = typename GraphTypes<Vertex>::SetOfEdges;
    using GraphToManipulate = UndirectedGraphWithListOfEdges<Vertex>;

    FleuryAlgorithm(BaseUndirectedGraphWithVertex const& graph) : BaseClass(graph), b_graph(BaseClass::m_graph) {}

    Path getEulerCycle() const override {
        // Fleury’s Algorithm
        // 1. Start at any vertex if finding an Euler circuit. If finding an Euler path, start at one of the two
        // vertices with odd degree.
        // 2. Choose any edge leaving your current vertex, provided deleting that edge will not separate the graph into
        // two disconnected sets of edges.
        // 3. Add that edge to your circuit, and delete it from the graph.
        // 4. Continue until you’re done.

        Path result;
        Edges originalEdges(b_graph.getEdges());
        if (!originalEdges.empty()) {
            // start at the vertices of the first edge
            searchForEulerPath(result, originalEdges.front().first, originalEdges);
        }
        return result;
    }

    Path getEulerPath() const override {
        Path result;
        Edges originalEdges(b_graph.getEdges());
        if (!originalEdges.empty()) {
            // check graph for starting vertex
            searchForEulerPath(result, this->getStartingVertexForEulerPath(), originalEdges);
        }
        return result;
    }

private:
    bool isStillConnectedAfterRemovingThisEdge(GraphToManipulate const& graph, Edge const& edgeToDelete) const {
        // THIS IS COSTLY!
        GraphToManipulate graphWithDeletedEdge(graph);
        graphWithDeletedEdge.disconnect(edgeToDelete.first, edgeToDelete.second);
        ConnectedComponentsUsingDfs<Vertex> connectedComponents(graphWithDeletedEdge);
        return connectedComponents.getNumberOfComponentIds() <= 1               // graph is still connected
               && connectedComponents.getComponentId(edgeToDelete.second) > 0;  // destination is still connected
    }

    GraphToManipulate createGraphToManipulate(Edges const& originalEdges) const {
        GraphToManipulate graphToManipulate;
        for (Edge const& originalEdge : originalEdges) {
            graphToManipulate.connect(originalEdge.first, originalEdge.second);
        }
        return graphToManipulate;
    }

    void putEulerEdgesOnPath(Path& result, Edges const& edgesInEulerCycle) const {
        result.emplace_back(edgesInEulerCycle.front().first);
        for (auto const& [startVertexOfEdge, endVertexOfEdge] : edgesInEulerCycle) {
            result.emplace_back(endVertexOfEdge);
        }
    }

    void searchForEulerPath(Path& result, Vertex const& startVertex, Edges const& originalEdges) const {
        GraphToManipulate graphToManipulate(createGraphToManipulate(originalEdges));
        SetOfEdges& edgesReference(graphToManipulate.getSetOfEdgesReference());
        bool isComplete(true);
        Edges edgesInEulerCycle;
        Edge deletedEdge(startVertex, startVertex);
        while (!edgesReference.empty()) {
            // get next edge to delete so that graph is still connected
            auto edgeToDeleteIt =
                std::find_if(edgesReference.cbegin(), edgesReference.cend(), [&](Edge const& edgeToDelete) {
                    return deletedEdge.second == edgeToDelete.first &&
                           isStillConnectedAfterRemovingThisEdge(graphToManipulate, edgeToDelete);
                });
            if (edgeToDeleteIt == edgesReference.cend())  // if not found just get next edge
            {
                edgeToDeleteIt = std::find_if(
                    edgesReference.cbegin(), edgesReference.cend(),
                    [&](Edge const& edgeToDelete) { return deletedEdge.second == edgeToDelete.first; });
            }

            if (edgeToDeleteIt != edgesReference.cend()) {
                deletedEdge = *edgeToDeleteIt;
                edgesInEulerCycle.emplace_back(deletedEdge);
                graphToManipulate.disconnect(deletedEdge.first, deletedEdge.second);
            } else {
                isComplete = false;
                break;
            }
        }
        if (isComplete) {
            putEulerEdgesOnPath(result, edgesInEulerCycle);
        }
    }
    BaseUndirectedGraphWithVertex const& b_graph;
};

}  // namespace algorithm

}  // namespace alba

// Fleury's algorithm is an elegant but inefficient algorithm that dates to 1883.

// Algorithm description:
// Consider a graph known to have all edges in the same component and at most two vertices of odd degree.
// The algorithm starts at a vertex of odd degree, or, if the graph has none, it starts with an arbitrarily chosen
// vertex. At each step it chooses the next edge in the path to be one whose deletion would not disconnect the graph,
// unless there is no such edge, in which case it picks the remaining edge left at the current vertex.
// It then moves to the other endpoint of that edge and deletes the edge.
// At the end of the algorithm there are no edges left,
// and the sequence from which the edges were chosen forms an Eulerian cycle if the graph has no vertices of odd degree,
// or an Eulerian trail if there are exactly two vertices of odd degree.

// While the graph traversal in Fleury's algorithm is linear in the number of edges, i.e. O(E),
// we also need to factor in the complexity of detecting bridges.

// If we are to re-run Tarjan's linear time bridge-finding algorithm after the removal of every edge,
// Fleury's algorithm will have a time complexity of O(E^2)

// A dynamic bridge-finding algorithm of Thorup (2000) allows this to be improved to O (E*log^3(E)*log(log(E)),
// but this is still significantly slower than alternative algorithms.
