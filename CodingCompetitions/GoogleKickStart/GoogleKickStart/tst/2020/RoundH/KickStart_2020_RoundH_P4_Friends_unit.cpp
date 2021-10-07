#include "KickStart_2020_RoundH_P4_Friends.hpp"

#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2020_RoundH_P4_Friends
{

TEST(KickStart_2020_RoundH_P4_FriendsTest, Test1)
{
    stringstream & inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream & outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream
            << "2                              " "\n"
            << "5 2                            " "\n"
            << "LIZZIE KEVIN BOHDAN LALIT RUOYU" "\n"
            << "1 2                            " "\n"
            << "1 3                            " "\n"
            << "2 2                            " "\n"
            << "KICK START                     " "\n"
            << "1 2                            " "\n"
            << "1 2                            " "\n"
            << endl;

    main();

    EXPECT_EQ(
                "Case #1: 2 3" "\n"
                "Case #2: -1 -1" "\n"
                , outputStringStream.str());
}

}

/*
Problem

There are N people in the world numbered 1 to N. The i-th person has a distinct name Si that is a string of uppercase English letters.

Two people are friends if and only if there is some letter that appears at least once in each of their names. Any such letter does not need to be at the same position in both names. After all, friendship requires having something in common!

A friendship chain of length n between person A and person B is a sequence of people X1, X2, ..., Xn such that X1 = A, Xn = B, and Xi and Xi+1 are friends, for i=1 to n-1. Note that any two people can have zero or more friendship chains between them.

For each of the given Q pairs of people, can you find the length of the shortest friendship chain between them? If there is no friendship chain between a pair, output -1.
Input

The first line of the input gives the number of test cases, T. T test cases follow. The first line of each test case contains the two integers N and Q. The second line contains N strings, which are people's names. The i-th string (starting from 1) is Si. Then, Q lines follow, describing the queries. The i-th of these lines contains the two integers Xi and Yi, which are the indexes (counting starting from 1) of a pair of people in the list of names.
Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is a list of the answers for the Q queries in order, separated by spaces.
Limits

Time limit: 40 seconds per test set.
Memory limit: 1GB.
1 ≤ T ≤ 100.
1 ≤ Q ≤ 5 × 104.
Si consists of uppercase English letters, for all i.
1 ≤ length of Si ≤ 20, for all i.
All Si are distinct.
1 ≤ Xi <Yi ≤ N, for all i.
Test Set 1

2 ≤ N ≤ 100.
Test Set 2

103 < N ≤ 5 × 104 in at most 10 cases.
2 ≤ N ≤ 103 in all other cases.
Sample

Input

Output


2
5 2
LIZZIE KEVIN BOHDAN LALIT RUOYU
1 2
1 3
2 2
KICK START
1 2
1 2





Case #1: 2 3
Case #2: -1 -1



In Sample Case #1, there are two queries:

    In the first query, LIZZIE and KEVIN are friends (because they share the letter E in their names). So, the shortest friendship chain length is 2.
    In the second query, LIZZIE and BOHDAN are not friends, but have two possible shortest friendship chains (either via KEVIN or LALIT). So, the shortest friendship chain length is 3. Note that there are other friendship chains as well, but they are longer.

In Sample Case #2, there are two queries:

    In the first query, KICK and START are not connected by a chain of friends.
    The second query is the same as the first query. Note that queries are not guaranteed to be distinct.

*/
