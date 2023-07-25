#include "GameWithGraph.hpp"

#include <Math/GameTheory/Common/GameUtilities.hpp>

using namespace std;

namespace alba {

namespace math {

GameWithGraph::GameWithGraph(Graph const& graph) : m_graph(graph) {}

UnsignedInteger GameWithGraph::getGrundyNumberAt(Vertex const vertex) {
    UnsignedInteger result{};
    auto it = m_vertexToGrundyNumberMap.find(vertex);
    if (it != m_vertexToGrundyNumberMap.cend()) {
        result = it->second;
    } else {
        // possible infinite recursion for cycles
        result = getGrundyNumber(getNextGrundyNumbers(vertex));
        m_vertexToGrundyNumberMap[vertex] = result;
    }
    return result;
}

GameState GameWithGraph::getGameStateAt(Vertex const vertex) {
    return getGameStateFromGrundyNumber(getGrundyNumberAt(vertex));
}

GameWithGraph::Vertex GameWithGraph::getOptimalNextVertexAt(Vertex const vertex) {
    Vertex result{};
    GameState gameState = getGameStateFromGrundyNumber(getGrundyNumberAt(vertex));
    if (GameState::Losing == gameState) {
        bool isFirst(true);
        UnsignedInteger maxGrundyNumber(0U);
        for (Vertex const nextVertex : m_graph.getAdjacentVerticesAt(vertex)) {
            UnsignedInteger grundyNumber(getGrundyNumberAt(vertex));
            if (isFirst || maxGrundyNumber < grundyNumber) {
                isFirst = false;
                maxGrundyNumber = grundyNumber;
                result =
                    nextVertex;  // pick vertex with max grundy number because it might higher distance to losing state
            }
        }
    } else if (GameState::Winning == gameState) {
        for (Vertex const nextVertex : m_graph.getAdjacentVerticesAt(vertex)) {
            if (0U == getGrundyNumberAt(nextVertex))  // force your opponent to losing state
            {
                result = nextVertex;
                break;
            }
        }
    }
    return result;
}

SetOfUnsignedIntegers GameWithGraph::getNextGrundyNumbers(Vertex const vertex) {
    SetOfUnsignedIntegers result;
    Vertices nextVertices(m_graph.getAdjacentVerticesAt(vertex));
    transform(
        nextVertices.cbegin(), nextVertices.cend(), inserter(result, result.begin()),
        [&](Vertex const nextVertex) { return getGrundyNumberAt(nextVertex); });
    return result;
}

}  // namespace math

}  // namespace alba
