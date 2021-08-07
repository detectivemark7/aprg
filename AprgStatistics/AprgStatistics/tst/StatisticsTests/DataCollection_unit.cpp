#include <Statistics/DataCollection.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

using DataCollectionOfDoubles = DataCollection<double>;

TEST(DataCollectionTest, CollectionDataAreCorrect)
{
    DataCollectionOfDoubles collection;
    collection.addData(-100);
    collection.addData(-10);
    collection.addData(-1);
    collection.addData(1);
    collection.addData(10);
    collection.addData(70);
    collection.addData(100);

    EXPECT_EQ(-100, collection.getMinimum());
    EXPECT_EQ(100, collection.getMaximum());
    EXPECT_EQ(70, collection.getSum());
    EXPECT_EQ(7U, collection.getCount());
    EXPECT_EQ(10, collection.getAverage());
    EXPECT_EQ(10, collection.getAverageWithDoubleFormat());
}

}
