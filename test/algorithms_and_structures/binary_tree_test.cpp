#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <functional>
#include "structure/binary_tree/binary_tree.h"

struct binary_tree_fixture : testing::Test
{
};

TEST(binary_tree_fixture, empty_tree)
{
    structure::binary_tree<int> tree;
    EXPECT_THAT(tree.empty(), true);
    EXPECT_THAT(tree.size(), 0);
}

TEST(binary_tree_fixture, root_only_tree)
{
    structure::binary_tree<int> tree_from_constructor{0};
    EXPECT_THAT(tree_from_constructor.empty(), false);
    EXPECT_THAT(tree_from_constructor.size(), 1);

    structure::binary_tree<int> tree_from_insert{};
    tree_from_insert.insert(0);
    EXPECT_THAT(tree_from_insert.empty(), false);
    EXPECT_THAT(tree_from_insert.size(), 1);
}

/*
 * Overview
 *       3
 *      / \
 *     1   4
 *    / \   \
 *   0   2   5
 */
TEST(binary_tree_fixture, traverse_tree)
{
    structure::binary_tree<int> tree{3, 1, 0, 2, 4, 5};

    std::vector<int> inorder{};
    tree.traverse_inorder([&](const auto& value) { inorder.push_back(value); });
    EXPECT_THAT(inorder, testing::ElementsAre(0, 1, 2, 3, 4, 5));

    std::vector<int> preorder{};
    tree.traverse_preorder([&](const auto& value) { preorder.push_back(value); });
    EXPECT_THAT(preorder, testing::ElementsAre(3, 1, 0, 2, 4, 5));

    std::vector<int> postorder{};
    tree.traverse_postorder([&](const auto& value) { postorder.push_back(value); });
    EXPECT_THAT(postorder, testing::ElementsAre(0, 2, 1, 5, 4, 3));
}

TEST(binary_tree_fixture, copy_constructor)
{
    structure::binary_tree<int> tree{3, 1, 0, 2, 4, 5};
    structure::binary_tree<int> copied{tree};

    EXPECT_THAT(copied.empty(), false);
    EXPECT_THAT(copied.size(), 6);

    std::vector<int> inorder{};
    std::vector<int> copied_inorder{};
    tree.traverse_inorder([&](const auto& value) { inorder.push_back(value); });
    copied.traverse_inorder([&](const auto& value) { copied_inorder.push_back(value); });
    EXPECT_THAT(inorder, testing::Eq(copied_inorder));

    std::vector<int> preorder{};
    std::vector<int> copied_preorder{};
    tree.traverse_preorder([&](const auto& value) { preorder.push_back(value); });
    copied.traverse_preorder([&](const auto& value) { copied_preorder.push_back(value); });
    EXPECT_THAT(preorder, testing::Eq(copied_preorder));

    std::vector<int> postorder{};
    std::vector<int> copied_postorder{};
    tree.traverse_postorder([&](const auto& value) { postorder.push_back(value); });
    copied.traverse_postorder([&](const auto& value) { copied_postorder.push_back(value); });
    EXPECT_THAT(postorder, testing::Eq(copied_postorder));
}

TEST(binary_tree_fixture, copy_assignment)
{
    structure::binary_tree<int> tree{3, 1, 0, 2, 4, 5};
    structure::binary_tree<int> copied{0};

    copied = tree;

    EXPECT_THAT(copied.empty(), false);
    EXPECT_THAT(copied.size(), 6);

    std::vector<int> inorder{};
    std::vector<int> copied_inorder{};
    tree.traverse_inorder([&](const auto& value) { inorder.push_back(value); });
    copied.traverse_inorder([&](const auto& value) { copied_inorder.push_back(value); });
    EXPECT_THAT(inorder, testing::Eq(copied_inorder));

    std::vector<int> preorder{};
    std::vector<int> copied_preorder{};
    tree.traverse_preorder([&](const auto& value) { preorder.push_back(value); });
    copied.traverse_preorder([&](const auto& value) { copied_preorder.push_back(value); });
    EXPECT_THAT(preorder, testing::Eq(copied_preorder));

    std::vector<int> postorder{};
    std::vector<int> copied_postorder{};
    tree.traverse_postorder([&](const auto& value) { postorder.push_back(value); });
    copied.traverse_postorder([&](const auto& value) { copied_postorder.push_back(value); });
    EXPECT_THAT(postorder, testing::Eq(copied_postorder));
}

TEST(binary_tree_fixture, move_constructor)
{
    structure::binary_tree<int> tree{3, 1, 0, 2, 4, 5};
    structure::binary_tree<int> moved{std::move(tree)};

    EXPECT_THAT(tree.empty(), true);
    EXPECT_THAT(tree.size(), 0);
    EXPECT_THAT(moved.empty(), false);
    EXPECT_THAT(moved.size(), 6);

    std::vector<int> inorder{};
    moved.traverse_inorder([&](const auto& value) { inorder.push_back(value); });
    EXPECT_THAT(inorder, testing::ElementsAre(0, 1, 2, 3, 4, 5));

    std::vector<int> preorder{};
    moved.traverse_preorder([&](const auto& value) { preorder.push_back(value); });
    EXPECT_THAT(preorder, testing::ElementsAre(3, 1, 0, 2, 4, 5));

    std::vector<int> postorder{};
    moved.traverse_postorder([&](const auto& value) { postorder.push_back(value); });
    EXPECT_THAT(postorder, testing::ElementsAre(0, 2, 1, 5, 4, 3));
}

TEST(binary_tree_fixture, move_assignment)
{
    structure::binary_tree<int> tree{3, 1, 0, 2, 4, 5};
    structure::binary_tree<int> moved{0};

    moved = std::move(tree);

    EXPECT_THAT(tree.empty(), true);
    EXPECT_THAT(tree.size(), 0);
    EXPECT_THAT(moved.empty(), false);
    EXPECT_THAT(moved.size(), 6);

    std::vector<int> inorder{};
    moved.traverse_inorder([&](const auto& value) { inorder.push_back(value); });
    EXPECT_THAT(inorder, testing::ElementsAre(0, 1, 2, 3, 4, 5));

    std::vector<int> preorder{};
    moved.traverse_preorder([&](const auto& value) { preorder.push_back(value); });
    EXPECT_THAT(preorder, testing::ElementsAre(3, 1, 0, 2, 4, 5));

    std::vector<int> postorder{};
    moved.traverse_postorder([&](const auto& value) { postorder.push_back(value); });
    EXPECT_THAT(postorder, testing::ElementsAre(0, 2, 1, 5, 4, 3));
}

TEST(binary_tree_fixture, insert_and_remove)
{
    structure::binary_tree<int> tree{};

    /*
     *       3
     *      / \
     *     1   4
     *    / \   \
     *   0   2   5
     */
    tree.insert(3, 1, 0, 2, 4, 5);

    std::vector<int> after_insert{};
    tree.traverse_preorder([&](const auto& value) { after_insert.push_back(value); });
    EXPECT_THAT(after_insert, testing::ElementsAre(3, 1, 0, 2, 4, 5));
    EXPECT_THAT(tree.size(), 6);
    EXPECT_THAT(tree.empty(), false);

    /*
     *       3
     *      /
     *     1
     *    / \
     *   0   2
     */
    tree.remove_if([](int value) -> bool { return value >= 4; });

    std::vector<int> after_remove1{};
    tree.traverse_preorder([&](const auto& value) { after_remove1.push_back(value); });
    EXPECT_THAT(after_remove1, testing::ElementsAre(3, 1, 0, 2));
    EXPECT_THAT(tree.size(), 4);
    EXPECT_THAT(tree.empty(), false);

    /*
     *       3
     *      /
     *     1
     */
    tree.remove_if([](int value) -> bool { return value == 0 || value == 2; });
    std::vector<int> after_remove2{};
    tree.traverse_preorder([&](const auto& value) { after_remove2.push_back(value); });
    EXPECT_THAT(after_remove2, testing::ElementsAre(3, 1));
    EXPECT_THAT(tree.size(), 2);
    EXPECT_THAT(tree.empty(), false);

    /* Tree completely removed */
    tree.remove_if([](int value) -> bool { return value <= 5; });
    EXPECT_THAT(tree.size(), 0);
    EXPECT_THAT(tree.empty(), true);
}
