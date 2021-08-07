#pragma once

#include <Algorithm/Search/GetFreeIndex/Common/GetFreeIndexWithUnionFind.hpp>

namespace alba
{

namespace algorithm
{

template <typename Index>
class GetPreviousFreeIndexWithUnionFind : public GetFreeIndexWithUnionFind<Index>
{
public:
    using BaseClass = GetFreeIndexWithUnionFind<Index>;
    using UnionFind = typename BaseClass::UnionFind;

    GetPreviousFreeIndexWithUnionFind(Index const numberOfIndexes)
        : BaseClass(numberOfIndexes)
        , b_numberOfIndexes(BaseClass::m_numberOfIndexes)
        , b_unionFind(BaseClass::m_unionFind)
    {}

    Index getPreviousFreeIndexAt(Index const index)
    {
        return BaseClass::getFreeIndexAt(index);
    }

    void setAsNotFree(Index const index)
    {
        if(index>0 && index<b_numberOfIndexes)
        {
            b_unionFind.connect(index, index-1);
        }
    }

    void setAsFree(Index const index)
    {
        // NOTE: This is linear

        Index rootOfIndex(b_unionFind.getRoot(index));
        if(index<b_numberOfIndexes && rootOfIndex != index)
        {
            auto & relativeRoots(b_unionFind.getRelativeRootVectorReference());

            relativeRoots[index] = index;
            for(Index i=index+1; i<relativeRoots.size(); i++)
            {
                if(relativeRoots.at(i) == rootOfIndex)
                {
                    relativeRoots[i] = index;
                }
            }
        }
    }

private:
    Index & b_numberOfIndexes;
    UnionFind & b_unionFind;
};

}

}
