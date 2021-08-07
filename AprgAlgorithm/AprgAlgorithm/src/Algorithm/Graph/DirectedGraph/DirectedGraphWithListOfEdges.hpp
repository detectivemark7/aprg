#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>

#include <algorithm>
#include <sstream>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class DirectedGraphWithListOfEdges : public BaseDirectedGraph<Vertex>
{
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using SetOfEdges = typename GraphTypes<Vertex>::SetOfEdges;

    DirectedGraphWithListOfEdges()
        : m_numberOfEdges(0U)
    {}

    bool isEmpty() const
    {
        return m_edges.empty();
    }

    bool isDirectlyConnected(Vertex const& sourceVertex, Vertex const& destinationVertex) const override
    {
        return m_edges.find({sourceVertex, destinationVertex}) != m_edges.cend();
    }

    unsigned int getNumberOfVertices() const override
    {
        return getUniqueVertices().size();
    }

    unsigned int getNumberOfEdges() const override
    {
        return m_numberOfEdges;
    }

    Vertices getAdjacentVerticesAt(Vertex const& vertex) const override
    {
        Vertices result;
        for(auto it = m_edges.lower_bound({vertex, Vertex{}}); it!=m_edges.cend() && it->first==vertex; it++)
        {
            result.emplace_back(it->second);
        };
        return result;
    }

    Vertices getVertices() const override
    {
        SetOfVertices uniqueVertices(getUniqueVertices());
        return Vertices(uniqueVertices.cbegin(), uniqueVertices.cend());
    }

    Edges getEdges() const override
    {
        Edges result;
        result.reserve(m_edges.size());
        std::transform(m_edges.cbegin(), m_edges.cend(), std::back_inserter(result), [](Edge const& edge)
        {
            return edge;
        });
        return result;
    }

    std::string getDisplayableString() const override
    {
        std::stringstream ss;
        ss << "Edges: {";
        for(auto const& edge : m_edges)
        {
            ss << edge.first << "->" << edge.second << ", ";
        }
        ss << "}";
        return ss.str();
    }

    void connect(Vertex const& sourceVertex, Vertex const& destinationVertex) override
    {
        if(!isDirectlyConnected(sourceVertex, destinationVertex))
        {
            m_numberOfEdges++;
            m_edges.emplace(sourceVertex, destinationVertex);
        }
    }

    void disconnect(Vertex const& sourceVertex, Vertex const& destinationVertex) override
    {
        if(isDirectlyConnected(sourceVertex, destinationVertex))
        {
            m_numberOfEdges--;
            m_edges.erase({sourceVertex, destinationVertex});
        }
    }

    void clear()
    {
        m_numberOfEdges = 0;
        m_edges.clear();
    }

protected:
    SetOfVertices getUniqueVertices() const
    {
        SetOfVertices uniqueVertices;
        for(auto const& edge : m_edges)
        {
            uniqueVertices.emplace(edge.first);
            uniqueVertices.emplace(edge.second);
        }
        return uniqueVertices;
    }
    unsigned int m_numberOfEdges;
    SetOfEdges m_edges;
};

}

}
