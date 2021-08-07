#include "CountingSubGrids.hpp"

#include <bitset>

using namespace std;

namespace alba
{

CountingSubGrids::CountingSubGrids(BitGrid const& bitGrid)
    : m_bitValueGrid()
{
    initialize(bitGrid);
}

unsigned int CountingSubGrids::countSubGridsWithAllBlackCorners() const
{
    unsigned int result = 0;
    for(unsigned int row=0; row<m_bitValueGrid.getNumberOfRows(); row++)
    {
        for(unsigned int nextRow=row+1; nextRow<m_bitValueGrid.getNumberOfRows(); nextRow++)
        {
            unsigned int commonBlackColumns(0U);
            for (unsigned int i=0; i<m_bitValueGrid.getNumberOfColumns(); i++)
            {
                commonBlackColumns += BitValueUtilities::getNumberOfOnes(m_bitValueGrid.getEntry(i, row) & m_bitValueGrid.getEntry(i, nextRow));
            }
            result += commonBlackColumns*(commonBlackColumns-1)/2; // combinations of subgrids based on common black columns
        }
    }
    return result;
}

void CountingSubGrids::initialize(BitGrid const& bitGrid)
{
    if(bitGrid.getNumberOfRows() <= bitGrid.getNumberOfColumns())
    {
        unsigned int newColumns((bitGrid.getNumberOfColumns()+NUMBER_OF_BITS-1)/NUMBER_OF_BITS);
        unsigned int newRows(bitGrid.getNumberOfRows());
        m_bitValueGrid.clearAndResize(newColumns, newRows);
        bitset<NUMBER_OF_BITS> bitsetValue;
        for(unsigned int y=0; y<bitGrid.getNumberOfRows(); y++)
        {
            for(unsigned int x=0; x<bitGrid.getNumberOfColumns(); x++)
            {
                if(x%NUMBER_OF_BITS==0)
                {
                    bitsetValue.reset();
                }
                unsigned int bitPosition = NUMBER_OF_BITS-1 - x%NUMBER_OF_BITS;
                bitsetValue[bitPosition] = bitGrid.getEntry(x,y);
                if(bitPosition==NUMBER_OF_BITS-1 || x == bitGrid.getNumberOfColumns()-1)
                {
                    m_bitValueGrid.setEntry(x/NUMBER_OF_BITS, y, static_cast<BitValue>(bitsetValue.to_ullong()));
                }
            }
        }
    }
    else
    {
        unsigned int newColumns((bitGrid.getNumberOfRows()+NUMBER_OF_BITS-1)/NUMBER_OF_BITS);
        unsigned int newRows(bitGrid.getNumberOfColumns());
        m_bitValueGrid.clearAndResize(newColumns, newRows);
        bitset<NUMBER_OF_BITS> bitsetValue;
        for(unsigned int y=0; y<bitGrid.getNumberOfColumns(); y++)
        {
            for(unsigned int x=0; x<bitGrid.getNumberOfRows(); x++)
            {
                unsigned int bitPosition = x%NUMBER_OF_BITS;
                if(bitPosition==0)
                {
                    bitsetValue.reset();
                }
                bitsetValue[bitPosition] = bitGrid.getEntry(y,x);
                if(bitPosition==NUMBER_OF_BITS-1 || x == bitGrid.getNumberOfColumns()-1)
                {
                    m_bitValueGrid.setEntry(x/NUMBER_OF_BITS, y, static_cast<BitValue>(bitsetValue.to_ullong()));
                }
            }
        }
    }


}

}
