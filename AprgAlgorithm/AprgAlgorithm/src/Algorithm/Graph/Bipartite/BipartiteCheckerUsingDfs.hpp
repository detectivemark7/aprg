#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex>
class BipartiteCheckerUsingDfs {
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToColorMap = std::map<Vertex, bool>;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    BipartiteCheckerUsingDfs(BaseUndirectedGraphWithVertex const& graph) : m_graph(graph), m_isBipartite(true) {
        initialize();
    }

    bool isBipartite() const { return m_isBipartite; }

    bool hasFirstColor(Vertex const& vertex) const {
        bool result(false);
        auto it = m_vertexToColorMap.find(vertex);
        if (it != m_vertexToColorMap.cend()) {
            result = !it->second;
        }
        return result;
    }

    void retrieveVerticesWithColor(Vertices& verticesWithFirstColor, Vertices& verticesWithSecondColor) const {
        for (auto const& [vertex, color] : m_vertexToColorMap) {
            if (!color) {
                verticesWithFirstColor.emplace_back(vertex);
            } else {
                verticesWithSecondColor.emplace_back(vertex);
            }
        }
    }

private:
    bool areColorsEqualOnVertices(Vertex const& vertex1, Vertex const& vertex2) const {
        bool result(false);
        auto it1 = m_vertexToColorMap.find(vertex1);
        auto it2 = m_vertexToColorMap.find(vertex2);
        if (it1 != m_vertexToColorMap.cend() && it2 != m_vertexToColorMap.cend()) {
            result = it1->second == it2->second;
        }
        return result;
    }

    void initialize() {
        Vertices vertices(m_graph.getVertices());
        for (Vertex const& vertex : vertices) {
            m_vertexToColorMap[vertex] = false;  // set all colors to one color (note that "false" is the first color)
        }
        for (Vertex const& vertex : vertices) {
            if (m_processedVertices.isNotFound(vertex)) {
                checkUsingDfs(vertex);
                if (!m_isBipartite) {
                    // if not bipartite, stop (no use continuing on it)
                    break;
                }
            }
        }
    }

    void checkUsingDfs(Vertex const& vertex) {
        m_processedVertices.putVertex(vertex);
        bool vertexColor(m_vertexToColorMap[vertex]);
        for (Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex)) {
            if (m_processedVertices.isNotFound(adjacentVertex)) {
                // assign the other color for unprocessed adjacent vertices
                m_vertexToColorMap[adjacentVertex] = getTheOtherColor(vertexColor);
                checkUsingDfs(adjacentVertex);
            } else if (vertexColor == m_vertexToColorMap[adjacentVertex]) {
                // two adjacent vertices can't be in the same color to be bipartite
                // (colors needs to be alternating)
                m_isBipartite = false;
                break;
            }
        }
    }

    bool getTheOtherColor(bool const color) { return !color; }

    BaseUndirectedGraphWithVertex const& m_graph;
    bool m_isBipartite;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToColorMap m_vertexToColorMap;
};

// Other definition:
// A graph is bipartite if its nodes can be colored using two colors so that there are no adjacent nodes with the same
// color. The idea is to color the starting node blue, all its neighbors red, all their neighbors blue, and so on. If at
// some point of the search we notice that two adjacent nodes have the same color, this means that the graph is not
// bipartite.

// This algorithm always works, because when there are only two colors available,
// the color of the starting node in a component determines the colors of all other nodes in the component.
// It does not make any difference whether the starting node is red or blue.

// Other cases:
// Note that in the general case, it is difficult to find out if the nodes in a graph
// can be colored using k colors so that no adjacent nodes have the same color.
// Even when k=3, no efficient algorithm is known but the problem is NP-hard.

}  // namespace algorithm

}  // namespace alba
