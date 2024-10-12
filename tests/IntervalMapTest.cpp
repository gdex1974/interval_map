#include "interval_map.h"
#include <gtest/gtest.h>

TEST( IntervalMapTest, BasicTests )
{
    nonstd::interval_map<int, unsigned> testMap(0);
    EXPECT_EQ(testMap.size(), 1);
    EXPECT_EQ(testMap[std::numeric_limits<int>::min()], 0);
    EXPECT_EQ(testMap[std::numeric_limits<int>::max()], 0);
    testMap.assign(1,3, 1);
    EXPECT_EQ(testMap.size(), 3);
    EXPECT_EQ(testMap[0], 0);
    EXPECT_EQ(testMap[1], 1);
    EXPECT_EQ(testMap[2], 1);
    EXPECT_EQ(testMap[3], 0);
    testMap.assign(1,3, 2);
    EXPECT_EQ(testMap.size(), 3);
    EXPECT_EQ(testMap[0], 0);
    EXPECT_EQ(testMap[1], 2);
    EXPECT_EQ(testMap[2], 2);
    EXPECT_EQ(testMap[3], 0);
    testMap.assign(std::numeric_limits<int>::lowest(),1, -1);
    EXPECT_EQ(testMap.size(), 3);
    EXPECT_EQ(testMap[0], -1);
    EXPECT_EQ(testMap[1], 2);
    testMap.assign(1,3, 0);
    EXPECT_EQ(testMap.size(), 2);
    EXPECT_EQ(testMap[2], 0);
    testMap.assign(std::numeric_limits<int>::lowest(),1, 0);
    EXPECT_EQ(testMap, (nonstd::interval_map<int, unsigned>(0)));
    testMap.assign(2,3, 2);
    EXPECT_EQ(testMap, decltype(testMap)(0, {{2,2},{3,0}}));
    testMap.assign(1,3, 1);
    EXPECT_EQ(testMap, decltype(testMap)(0, {{1, 1},{3,0}}));
    testMap.assign(2,4, 2);
    EXPECT_EQ(testMap, decltype(testMap)(0, {{1, 1},{2,2},{4,0}}));
    testMap.assign(1,3, 1);
    EXPECT_EQ(testMap, decltype(testMap)(0, {{1, 1},{3,2},{4,0}}));
    testMap.assign(5,8, 10);
    EXPECT_EQ(testMap, decltype(testMap)(0, {{1, 1},{3,2},{4,0},{5,10},{8,0}}));
    testMap.assign(6,8, 5);
    EXPECT_EQ(testMap, decltype(testMap)(0, {{1, 1},{3,2},{4,0},{5,10},{6,5},{8,0}}));
    testMap.assign(1,8, 0);
    EXPECT_EQ(testMap, decltype(testMap)(0));
    EXPECT_EQ(decltype(testMap)(0, {{4,0},{3,2},{1, 1}}), decltype(testMap)(0, {{1, 1},{3,2},{4,0}}));

}
