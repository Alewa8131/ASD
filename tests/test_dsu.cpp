// Copyright 2025 Alewa8131

#include <gtest/gtest.h>
#include <stdexcept>
#include "../lib_dsu/dsu.h"


TEST(DSUTest, Constructor_ValidSize) {
    DSU dsu(10);
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(i, dsu.find(i));
    }
}

TEST(DSUTest, Constructor_ZeroSize) {
    EXPECT_THROW(DSU dsu(0), std::invalid_argument);
}


TEST(DSUTest, Find_Simple) {
    DSU dsu(5);

    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(i, dsu.find(i));
    }
}

TEST(DSUTest, Find_Error_OutOfRange) {
    DSU dsu(3);

    EXPECT_THROW(dsu.find(-1), std::out_of_range);
    EXPECT_THROW(dsu.find(3), std::out_of_range);
}

TEST(DSUTest, FindRec_Simple) {
    DSU dsu(5);

    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(i, dsu.find_rec(i));
    }
}


TEST(DSUTest, Union_TwoElements) {
    DSU dsu(5);

    dsu.uni0n(1, 2);

    int root1 = dsu.find(1);
    int root2 = dsu.find(2);

    ASSERT_EQ(root1, root2);
}

TEST(DSUTest, Union_Self) {
    DSU dsu(5);

    dsu.uni0n(3, 3);

    ASSERT_EQ(3, dsu.find(3));
}

TEST(DSUTest, Union_Chain) {
    DSU dsu(6);

    dsu.uni0n(0, 1);
    dsu.uni0n(1, 2);
    dsu.uni0n(2, 3);

    int r0 = dsu.find(0);
    int r3 = dsu.find(3);

    ASSERT_EQ(r0, r3);
}

TEST(DSUTest, Union_Error_OutOfRange) {
    DSU dsu(5);

    EXPECT_THROW(dsu.uni0n(-1, 2), std::out_of_range);
    EXPECT_THROW(dsu.uni0n(1, 5), std::out_of_range);
}


TEST(DSUTest, PathCompression_Works) {
    DSU dsu(6);

    dsu.uni0n(0, 1);
    dsu.uni0n(1, 2);
    dsu.uni0n(2, 3);
    dsu.uni0n(3, 4);
    dsu.uni0n(4, 5);

    int root_before = dsu.find(5);

    for (int i = 0; i <= 5; ++i) {
        ASSERT_EQ(root_before, dsu.find(i));
    }
}

TEST(DSUTest, MultipleIndependentSets) {
    DSU dsu(8);

    dsu.uni0n(0, 1);
    dsu.uni0n(1, 2);

    dsu.uni0n(4, 5);
    dsu.uni0n(5, 6);

    ASSERT_EQ(dsu.find(0), dsu.find(2));
    ASSERT_EQ(dsu.find(4), dsu.find(6));

    ASSERT_NE(dsu.find(0), dsu.find(4));
}

TEST(DSUTest, FindAndFindRecSameRoot) {
    DSU dsu(7);

    dsu.uni0n(0, 1);
    dsu.uni0n(1, 2);
    dsu.uni0n(3, 4);

    ASSERT_EQ(dsu.find(2), dsu.find_rec(2));
    ASSERT_EQ(dsu.find(4), dsu.find_rec(4));
}

TEST(DSUTest, Union_AlreadyUnited) {
    DSU dsu(5);

    dsu.uni0n(1, 2);
    dsu.uni0n(2, 3);

    int before = dsu.find(3);

    dsu.uni0n(1, 3);

    int after = dsu.find(3);
    ASSERT_EQ(before, after);
}





TEST(IslandsTemplateTest, AllWater) {
    int grid[3][3] = {
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };

    ASSERT_EQ(0, count_islands(grid));
}

TEST(IslandsTemplateTest, AllLand) {
    int grid[2][2] = {
        {1,1},
        {1,1}
    };

    ASSERT_EQ(1, count_islands(grid));
}

TEST(IslandsTemplateTest, BigSolidIsland) {
    int grid[6][6] = {
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1},
        {1,1,1,1,1,1}
    };

    ASSERT_EQ(1, count_islands(grid));
}

TEST(IslandsTemplateTest, SingleLand) {
    int grid[1][1] = {
        {1}
    };

    ASSERT_EQ(1, count_islands(grid));
}

TEST(IslandsTemplateTest, SingleWater) {
    int grid[1][1] = {
        {0}
    };

    ASSERT_EQ(0, count_islands(grid));
}


TEST(IslandsTemplateTest, DiagonalNotConnected) {
    int grid[3][3] = {
        {1,0,1},
        {0,1,0},
        {1,0,1}
    };

    ASSERT_EQ(5, count_islands(grid));
}

TEST(IslandsTemplateTest, HorizontalLine) {
    int grid[1][5] = {
        {1,1,1,1,1}
    };

    ASSERT_EQ(1, count_islands(grid));
}

TEST(IslandsTemplateTest, VerticalLine) {
    int grid[5][1] = {
        {1},
        {1},
        {1},
        {1},
        {1}
    };

    ASSERT_EQ(1, count_islands(grid));
}


TEST(IslandsTemplateTest, GivenExample) {
    int grid[5][5] = {
        {0,1,0,0,1},
        {0,1,1,0,1},
        {1,1,0,1,1},
        {0,0,0,0,1},
        {1,0,1,1,1}
    };

    ASSERT_EQ(3, count_islands(grid));
}

TEST(IslandsTemplateTest, MultipleIslands) {
    int grid[4][5] = {
        {1,0,1,0,1},
        {0,0,0,0,0},
        {1,0,1,0,1},
        {0,0,0,1,0}
    };

    ASSERT_EQ(7, count_islands(grid));
}

TEST(IslandsTemplateTest, SnakeIsland) {
    int grid[5][5] = {
        {1,1,0,0,0},
        {0,1,1,0,0},
        {0,0,1,1,0},
        {0,0,0,1,1},
        {0,0,0,0,1}
    };

    ASSERT_EQ(1, count_islands(grid));
}


TEST(IslandsTemplateTest, CornersOnly) {
    int grid[3][3] = {
        {1,0,1},
        {0,0,0},
        {1,0,1}
    };

    ASSERT_EQ(4, count_islands(grid));
}

TEST(IslandsTemplateTest, Checkerboard) {
    int grid[4][4] = {
        {1,0,1,0},
        {0,1,0,1},
        {1,0,1,0},
        {0,1,0,1}
    };

    ASSERT_EQ(8, count_islands(grid));
}
