#include "KnightsTour.hpp"

#include <Algorithm/Graph/PathSearch/HamiltonianPaths/HamiltonianPathSearchWithDfs.hpp>

using namespace alba::algorithm;
using namespace std;

namespace alba
{

KnightsTour::KnightsTour(
        unsigned int const chessBoardX,
        unsigned int const chessBoardY)
    : m_chessBoardX(chessBoardX)
    , m_chessBoardY(chessBoardY)
    , m_neighborMatrix(chessBoardX, chessBoardY)
{
    initialize();
}

KnightsTour::ChessBoardIndexes KnightsTour::getAnOpenKnightsTour() const
{
    ChessBoardIndexes result;
    HamiltonianPathSearchWithDfs<VertexOfKnightsTour> hamiltonianPathSearch(m_graph);
    for(VertexOfKnightsTour const& vertex : hamiltonianPathSearch.getOneHamiltonianPath())
    {
        result.emplace_back(vertex.second);
    }
    return result;
}

KnightsTour::ChessBoardIndexes KnightsTour::getAClosedKnightsTour() const
{
    ChessBoardIndexes result;
    HamiltonianPathSearchWithDfs<VertexOfKnightsTour> hamiltonianPathSearch(m_graph);
    for(VertexOfKnightsTour const& vertex : hamiltonianPathSearch.getOneHamiltonianCycle())
    {
        result.emplace_back(vertex.second);
    }
    return result;
}

void KnightsTour::initialize()
{
    initializeNeighborMatrix();
    initializeGraph();
}

void KnightsTour::initializeNeighborMatrix()
{
    for(int y=0; y<static_cast<int>(m_chessBoardY); y++)
    {
        for(int x=0; x<static_cast<int>(m_chessBoardX); x++)
        {
            m_neighborMatrix.setEntry(x, y, countNumberOfNeighbors(x, y));
        }
    }
}

void KnightsTour::initializeGraph()
{
    for(int y=0; y<static_cast<int>(m_chessBoardY); y++)
    {
        for(int x=0; x<static_cast<int>(m_chessBoardX); x++)
        {
            connectAllAt(x, y);
        }
    }
}

void KnightsTour::connectAllAt(
        int const x,
        int const y)
{
    unsigned int sourceNeighbors = getNumberOfNeighbors(x, y);
    unsigned int sourceIndex = getChessBoardIndex(x, y);
    connectIfNeeded(sourceNeighbors, sourceIndex, x-2, y-1);
    connectIfNeeded(sourceNeighbors, sourceIndex, x-2, y+1);
    connectIfNeeded(sourceNeighbors, sourceIndex, x-1, y-2);
    connectIfNeeded(sourceNeighbors, sourceIndex, x-1, y+2);
    connectIfNeeded(sourceNeighbors, sourceIndex, x+1, y-2);
    connectIfNeeded(sourceNeighbors, sourceIndex, x+1, y+2);
    connectIfNeeded(sourceNeighbors, sourceIndex, x+2, y-1);
    connectIfNeeded(sourceNeighbors, sourceIndex, x+2, y+1);
}

void KnightsTour::connectIfNeeded(
        unsigned int const sourceNeighbors,
        unsigned int const sourceIndex,
        int const x,
        int const y)
{
    // Number of neighbors are included because of Warnsdorf’s rule.
    // -> Warnsdorf’s rule is a simple and effective heuristic for finding a knight’s tour.
    // -> Using the rule, it is possible to efficiently construct a tour even on a large board.
    // -> The idea is to always move the knight so that it ends up in a square where the number of possible moves is as small as possible.

    if(isInside(x, y))
    {
        unsigned int destinationNeighbors = getNumberOfNeighbors(x, y);
        unsigned int destinationIndex = getChessBoardIndex(x, y);
        m_graph.connect({sourceNeighbors, sourceIndex}, {destinationNeighbors, destinationIndex});
    }
}

bool KnightsTour::isInside(
        int const x,
        int const y) const
{
    return x>=0 && x<static_cast<int>(m_chessBoardX) && y>=0 && y<static_cast<int>(m_chessBoardY);
}

unsigned int KnightsTour::getNumberOfNeighbors(
        int const x,
        int const y) const
{
    return m_neighborMatrix.getEntry(x, y);
}

unsigned int KnightsTour::countNumberOfNeighbors(
        int const x,
        int const y) const
{
    unsigned int numberOfNeighbors(0);
    if(isInside(x-2, y-1)){numberOfNeighbors++;}
    if(isInside(x-2, y+1)){numberOfNeighbors++;}
    if(isInside(x-1, y-2)){numberOfNeighbors++;}
    if(isInside(x-1, y+2)){numberOfNeighbors++;}
    if(isInside(x+1, y-2)){numberOfNeighbors++;}
    if(isInside(x+1, y+2)){numberOfNeighbors++;}
    if(isInside(x+2, y-1)){numberOfNeighbors++;}
    if(isInside(x+2, y+1)){numberOfNeighbors++;}
    return numberOfNeighbors;
}

unsigned int KnightsTour::getChessBoardIndex(
        int const x,
        int const y) const
{
    return static_cast<unsigned int>(m_chessBoardX*y + x);
}

}
