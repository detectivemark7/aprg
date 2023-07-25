#pragma once

#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex>
class SubTreeQuery {
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    using Counts = std::vector<int>;
    using VertexToIndexMap = std::map<Vertex, int>;

    SubTreeQuery(BaseUndirectedGraphWithVertex const& graph, Vertex const& rootOfTree)
        : m_graph(graph), m_rootOfTree(rootOfTree) {
        initializeIfNeeded();
    }

    Vertices const& getVerticesInDfsPreOrder() const { return m_verticesInDfsPreOrder; }

    Counts const& getSubTreeSize() const { return m_subTreeSize; }

    Vertices getVerticesOfSubTreeAt(Vertex const& subRoot) {
        Vertices result;
        auto it = m_vertexToIndexMap.find(subRoot);
        if (it != m_vertexToIndexMap.cend()) {
            int indexOfSubRoot = it->second;
            int subTreeSizeAtSubRoot = m_subTreeSize[indexOfSubRoot];
            result.reserve(subTreeSizeAtSubRoot);
            auto start = m_verticesInDfsPreOrder.cbegin() + indexOfSubRoot;
            auto end = m_verticesInDfsPreOrder.cbegin() + indexOfSubRoot + subTreeSizeAtSubRoot;
            std::copy(start, end, std::back_inserter(result));
        }
        return result;
    }

protected:
    void initializeIfNeeded() {
        if (GraphUtilities::isATree(m_graph)) {
            initialize();
        }
    }

    void initialize() { traverseStartingFromAVertex(m_rootOfTree); }

    void traverseStartingFromAVertex(Vertex const& startVertex) {
        if (m_processedVertices.isNotFound(startVertex) &&
            !m_graph.getAdjacentVerticesAt(startVertex).empty())  // dont include invalid vertex
        {
            m_subTreeSize.resize(m_graph.getNumberOfVertices());

            int treeSize(0);
            traverseUsingDfs(treeSize, startVertex);

            m_subTreeSize.resize(m_verticesInDfsPreOrder.size());
            m_verticesInDfsPreOrder.shrink_to_fit();
            m_subTreeSize.shrink_to_fit();
        }
    }

    void traverseUsingDfs(int& treeSize, Vertex const& vertex) {
        m_processedVertices.putVertex(vertex);
        m_verticesInDfsPreOrder.emplace_back(vertex);
        int beforeTreeSize = treeSize++;
        for (Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex)) {
            if (m_processedVertices.isNotFound(adjacentVertex)) {
                traverseUsingDfs(treeSize, adjacentVertex);
            }
        }
        m_vertexToIndexMap[vertex] = beforeTreeSize;
        m_subTreeSize[beforeTreeSize] =
            treeSize - beforeTreeSize;  // Sub tree size = "total tree size" - "before tree size"
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    Vertex m_rootOfTree;
    CheckableVerticesWithVertex m_processedVertices;
    Vertices m_verticesInDfsPreOrder;
    Counts m_subTreeSize;
    VertexToIndexMap m_vertexToIndexMap;
};

}  // namespace algorithm

}  // namespace alba
