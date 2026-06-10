// Copyright 2026 Alewa8131

#include <gtest/gtest.h>
#include <stdexcept>
#include "../lib_avltree/AVLTree.h"

TEST(AVLTreeTest, Constructor_EmptyTree) {
    AVLTree<int, int> tree;
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(nullptr, tree.get_root());
}

TEST(AVLTreeTest, InsertOneElement) {
    AVLTree<int, int> tree;

    tree.insert(5, 10);

    ASSERT_FALSE(tree.is_empty());

    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(5, root->_data.first);
    EXPECT_EQ(10, root->_data.second);
    EXPECT_EQ(nullptr, root->_left);
    EXPECT_EQ(nullptr, root->_right);
}

TEST(AVLTreeTest, InsertSeveralElements) {
    //      5
    //     / \
    //    2   8
    //   / \
    //  1   3
    AVLTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(8, 80);
    tree.insert(1, 10);
    tree.insert(3, 30);

    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(5, root->_data.first);


    auto* L = root->_left;
    ASSERT_NE(nullptr, L);
    EXPECT_EQ(2, L->_data.first);

    ASSERT_NE(nullptr, L->_left);
    EXPECT_EQ(1, L->_left->_data.first);

    ASSERT_NE(nullptr, L->_right);
    EXPECT_EQ(3, L->_right->_data.first);


    auto* R = root->_right;
    ASSERT_NE(nullptr, R);
    EXPECT_EQ(8, R->_data.first);
    EXPECT_EQ(nullptr, R->_left);
    EXPECT_EQ(nullptr, R->_right);
}

TEST(AVLTreeTest, InsertDuplicateKey) {
    AVLTree<int, int> tree;

    tree.insert(5, 10);
    EXPECT_THROW(tree.insert(5, 20), std::logic_error);
}

TEST(AVLTreeTest, FindNonExisting) {
    AVLTree<int, int> tree;

    tree.insert(5, 10);
    tree.insert(3, 20);

    EXPECT_EQ(nullptr, tree.find(100));
}

TEST(AVLTreeTest, EraseLeaf) {
    //      5
    //     / \
    //   [2]  8
    AVLTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(8, 80);

    tree.erase(2);

    //      5
    //       \
    //        8
    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(5, root->_data.first);
    EXPECT_EQ(nullptr, root->_left);

    ASSERT_NE(nullptr, root->_right);
    EXPECT_EQ(8, root->_right->_data.first);
}

TEST(AVLTreeTest, EraseNodeWithOneChild) {
    //      10
    //     /  \
    //    5   [20]
    AVLTree<int, int> tree;

    tree.insert(20, 200);
    tree.insert(10, 100);
    tree.insert(5, 50);

    tree.erase(20);

    //      10
    //     /
    //    5
    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(10, root->_data.first);
    EXPECT_EQ(nullptr, root->_right);

    ASSERT_NE(nullptr, root->_left);
    EXPECT_EQ(5, root->_left->_data.first);
}

TEST(AVLTreeTest, EraseNodeWithTwoChildren) {
    //          5
    //        /   \
    //      [2]    8
    //      / \
    //     1   3
    AVLTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(8, 80);
    tree.insert(1, 10);
    tree.insert(3, 30);

    tree.erase(2);

    //          5
    //        /   \
    //       1     8
    //        \
    //         3
    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(5, root->_data.first);

    auto* L = root->_left;
    ASSERT_NE(nullptr, L);
    EXPECT_EQ(1, L->_data.first);
    EXPECT_EQ(nullptr, L->_left);

    ASSERT_NE(nullptr, L->_right);
    EXPECT_EQ(3, L->_right->_data.first);

    ASSERT_NE(nullptr, root->_right);
    EXPECT_EQ(8, root->_right->_data.first);
}

TEST(AVLTreeTest, EraseRoot) {
    //      [5]  
    //     /   \ 
    //    2     8
    AVLTree<int, int> tree;

    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(8, 80);

    tree.erase(5);

    //      2
    //       \
    //        8
    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(2, root->_data.first);
    EXPECT_EQ(nullptr, root->_left);

    ASSERT_NE(nullptr, root->_right);
    EXPECT_EQ(8, root->_right->_data.first);
}

TEST(AVLTreeTest, EraseNonExisting) {
    AVLTree<int, int> tree;

    tree.insert(5, 50);

    EXPECT_THROW(tree.erase(100), std::out_of_range);
}

TEST(AVLTreeTest, Rotation_LL) {
    // Дисбаланс:         (R):
    //        3            2
    //       /            / \
    //      2     -->    1   3
    //     /
    //    1
    AVLTree<int, int> tree;

    tree.insert(3, 30);
    tree.insert(2, 20);
    tree.insert(1, 10);

    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(2, root->_data.first);

    ASSERT_NE(nullptr, root->_left);
    EXPECT_EQ(1, root->_left->_data.first);

    ASSERT_NE(nullptr, root->_right);
    EXPECT_EQ(3, root->_right->_data.first);
}

TEST(AVLTreeTest, Rotation_RR) {
    // Дисбаланс:           (L):
    //      1                2
    //       \              / \
    //        2     -->    1   3
    //         \
    //          3
    AVLTree<int, int> tree;

    tree.insert(1, 10);
    tree.insert(2, 20);
    tree.insert(3, 30);

    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(2, root->_data.first);

    ASSERT_NE(nullptr, root->_left);
    EXPECT_EQ(1, root->_left->_data.first);

    ASSERT_NE(nullptr, root->_right);
    EXPECT_EQ(3, root->_right->_data.first);
}

TEST(AVLTreeTest, Rotation_LR) {
    // Дисбаланс:            (L):            (R):
    //        3               3               2
    //       /               /               / \
    //      1     -->       2     -->       1   3
    //       \             /
    //        2           1
    AVLTree<int, int> tree;

    tree.insert(3, 30);
    tree.insert(1, 10);
    tree.insert(2, 20);

    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(2, root->_data.first);

    ASSERT_NE(nullptr, root->_left);
    EXPECT_EQ(1, root->_left->_data.first);

    ASSERT_NE(nullptr, root->_right);
    EXPECT_EQ(3, root->_right->_data.first);
}

TEST(AVLTreeTest, Rotation_RL) {
    // Дисбаланс:         (R):                (L):
    //      1              1                   2
    //       \              \                 / \
    //        3     -->      2     -->       1   3
    //       /                \
    //      2                  3
    AVLTree<int, int> tree;

    tree.insert(1, 10);
    tree.insert(3, 30);
    tree.insert(2, 20);

    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(2, root->_data.first);

    ASSERT_NE(nullptr, root->_left);
    EXPECT_EQ(1, root->_left->_data.first);

    ASSERT_NE(nullptr, root->_right);
    EXPECT_EQ(3, root->_right->_data.first);
}

TEST(AVLTreeTest, ComplexOperations_WithCascadeBalances) {
    //           10
    //        /      \
    //       5        15
    //      / \      /  \
    //     3   7    12  18
    AVLTree<int, int> tree;

    tree.insert(10, 100);
    tree.insert(5, 50);
    tree.insert(15, 150);
    tree.insert(3, 30);
    tree.insert(7, 70);
    tree.insert(12, 120);
    tree.insert(18, 180);

    tree.erase(5);
    tree.erase(15);

    //            10
    //          /    \
    //         3      12
    //          \       \
    //           7       18
    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(10, root->_data.first);

    auto* L = root->_left;
    ASSERT_NE(nullptr, L);
    EXPECT_EQ(3, L->_data.first);
    ASSERT_NE(nullptr, L->_right);
    EXPECT_EQ(7, L->_right->_data.first);
    EXPECT_EQ(nullptr, L->_left);

    auto* R = root->_right;
    ASSERT_NE(nullptr, R);
    EXPECT_EQ(12, R->_data.first);
    EXPECT_EQ(nullptr, R->_left);
    ASSERT_NE(nullptr, R->_right);
    EXPECT_EQ(18, R->_right->_data.first);
}

TEST(AVLTreeTest, LargeTree_EraseTriggersRootRotation) {
    //             50
    //           /    \
    //         25      75
    //        /  \    /  \
    //       12  35  65  85
    //      / \  / \
    //     6  18 30 40
    AVLTree<int, int> tree;

    tree.insert(50, 500);
    tree.insert(25, 250);
    tree.insert(75, 750);
    tree.insert(12, 120);
    tree.insert(35, 350);
    tree.insert(65, 650);
    tree.insert(85, 850);
    tree.insert(6, 60);
    tree.insert(18, 180);
    tree.insert(30, 300);
    tree.insert(40, 400);

    tree.erase(65);
    tree.erase(85);

    //          25
    //        /    \
    //       12     50
    //      / \    /  \
    //     6  18  35   75
    //           /  \
    //          30  40
    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(25, root->_data.first);

    // Уровень 1
    auto* L = root->_left;
    auto* R = root->_right;
    ASSERT_NE(nullptr, L);
    ASSERT_NE(nullptr, R);
    EXPECT_EQ(12, L->_data.first);
    EXPECT_EQ(50, R->_data.first);

    // Левая ветка уровня 2
    EXPECT_NE(nullptr, L->_left);
    EXPECT_EQ(6, L->_left->_data.first);
    EXPECT_NE(nullptr, L->_right);
    EXPECT_EQ(18, L->_right->_data.first);

    // Правая ветка уровня 2
    auto* R_L = R->_left;
    auto* R_R = R->_right;
    ASSERT_NE(nullptr, R_L);
    ASSERT_NE(nullptr, R_R);
    EXPECT_EQ(35, R_L->_data.first);
    EXPECT_EQ(75, R_R->_data.first);

    // Уровень 3 (дети узла 35)
    EXPECT_NE(nullptr, R_L->_left);
    EXPECT_EQ(30, R_L->_left->_data.first);
    EXPECT_NE(nullptr, R_L->_right);
    EXPECT_EQ(40, R_L->_right->_data.first);
}

TEST(AVLTreeTest, LargeTree_EraseTriggersDoubleRotation) {
    //              40
    //           /       \
    //         20          60
    //        /  \       /   \
    //       15  25     50    70
    //      /          /  \   / \
    //     5          45  55 65 80
    //                         /
    //                        75
    AVLTree<int, int> tree;

    tree.insert(40, 400);
    tree.insert(20, 200);
    tree.insert(60, 600);
    tree.insert(15, 150);
    tree.insert(25, 250);
    tree.insert(50, 500);
    tree.insert(70, 700);
    tree.insert(5, 50);
    tree.insert(45, 450);
    tree.insert(55, 550);
    tree.insert(65, 650);
    tree.insert(80, 800);
    tree.insert(75, 750);

    tree.erase(25);

    //            60
    //          /    \
    //        40      70
    //       /  \    /  \
    //     15   50  65   80
    //    / \  / \      /
    //   5  20 45 55   75
    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(60, root->_data.first);

    // Уровень 1
    auto* L = root->_left;
    auto* R = root->_right;
    ASSERT_NE(nullptr, L);
    ASSERT_NE(nullptr, R);
    EXPECT_EQ(40, L->_data.first);
    EXPECT_EQ(70, R->_data.first);

    // Дети узла 40
    auto* L_L = L->_left;
    auto* L_R = L->_right;
    ASSERT_NE(nullptr, L_L);
    ASSERT_NE(nullptr, L_R);
    EXPECT_EQ(15, L_L->_data.first);
    EXPECT_EQ(50, L_R->_data.first);

    // Дети узла 15
    EXPECT_NE(nullptr, L_L->_left);
    EXPECT_EQ(5, L_L->_left->_data.first);
    EXPECT_NE(nullptr, L_L->_right);
    EXPECT_EQ(20, L_L->_right->_data.first);

    // Дети узла 50
    EXPECT_NE(nullptr, L_R->_left);
    EXPECT_EQ(45, L_R->_left->_data.first);
    EXPECT_NE(nullptr, L_R->_right);
    EXPECT_EQ(55, L_R->_right->_data.first);

    // Дети узла 70
    EXPECT_NE(nullptr, R->_left);
    EXPECT_EQ(65, R->_left->_data.first);

    auto* R_R = R->_right;
    ASSERT_NE(nullptr, R_R);
    EXPECT_EQ(80, R_R->_data.first);

    // Ребенок узла 80
    EXPECT_NE(nullptr, R_R->_left);
    EXPECT_EQ(75, R_R->_left->_data.first);
}

TEST(AVLTreeTest, LargeTree_SequentialInsertStress) {
    //           8
    //        /     \
    //       4       12
    //      / \     /  \
    //     2   6   10   14
    //    / \ / \  / \  / \
    //    1 3 5 7  9 11 13 15
    AVLTree<int, int> tree;

    for (int i = 1; i <= 15; ++i) {
        tree.insert(i, i * 10);
    }

    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(8, root->_data.first);

    // уровень 1 (4 и 12)
    auto* L = root->_left;
    auto* R = root->_right;
    ASSERT_NE(nullptr, L);
    ASSERT_NE(nullptr, R);
    EXPECT_EQ(4, L->_data.first);
    EXPECT_EQ(12, R->_data.first);

    // уровень 2 (2, 6, 10, 14)
    ASSERT_NE(nullptr, L->_left);
    ASSERT_NE(nullptr, L->_right);
    ASSERT_NE(nullptr, R->_left);
    ASSERT_NE(nullptr, R->_right);
    EXPECT_EQ(2, L->_left->_data.first);
    EXPECT_EQ(6, L->_right->_data.first);
    EXPECT_EQ(10, R->_left->_data.first);
    EXPECT_EQ(14, R->_right->_data.first);
}

TEST(AVLTreeTest, Insert_RecalcHeightsToRootWithoutRotation) {
    //             8
    //          /     \
    //         4       12
    //        / \     /  \
    //       2   6   10   14
    //
    AVLTree<int, int> tree;

    tree.insert(8, 80);
    tree.insert(4, 40);
    tree.insert(12, 120);
    tree.insert(2, 20);
    tree.insert(6, 60);
    tree.insert(10, 100);
    tree.insert(14, 140);

    tree.insert(1, 10);

    //             8  
    //          /     \
    //         4       12 
    //        / \     /  \
    //       2   6   10   14
    //      /
    //     1 
    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);
    EXPECT_EQ(8, root->_data.first);

    auto* L = root->_left;
    ASSERT_NE(nullptr, L);
    EXPECT_EQ(4, L->_data.first);

    auto* L_L = L->_left;
    ASSERT_NE(nullptr, L_L);
    EXPECT_EQ(2, L_L->_data.first);

    EXPECT_NE(nullptr, L_L->_left);
    EXPECT_EQ(1, L_L->_left->_data.first);
}

TEST(AVLTreeTest, LargeTree_MassiveWaveErase) {
    AVLTree<int, int> tree;

    for (int i = 1; i <= 15; ++i) {
        tree.insert(i, i * 100);
        if (i != 30 - i) {
            tree.insert(30 - i, (30 - i) * 100);
        }
    }

    for (int i = 2; i <= 28; i += 2) {
        tree.erase(i);
    }

    auto* root = tree.get_root();
    ASSERT_NE(nullptr, root);

    for (int i = 1; i <= 29; ++i) {
        if (i % 2 == 0) {
            EXPECT_EQ(nullptr, tree.find(i));
        }
        else {
            ASSERT_NE(nullptr, tree.find(i));
            EXPECT_EQ(i * 100, *tree.find(i));
        }
    }
}
