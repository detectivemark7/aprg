#include "CodeJam_2020_WorldFinals_P3_HexacoinJam.hpp"

#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace CodeJam_2020_WorldFinals_P3_HexacoinJam
{

TEST(CodeJam_2020_WorldFinals_P3_HexacoinJamTest, Test1)
{
    stringstream & inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream & outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream
            << "" "\n"
            << "" "\n"
            << "" "\n"
            << "" "\n"
            << endl;

    main();

    EXPECT_EQ(
                "" "\n"
                "" "\n"
                "" "\n"
                "" "\n"
                , outputStringStream.str());
}

}

