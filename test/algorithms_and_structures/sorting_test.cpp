#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <functional>
#include "algorithm/sort/sort.h"

using Range = std::vector<int>;

template <typename T>
using sort_function = std::function<void(T&)>;

struct sort_fixture : public testing::TestWithParam<sort_function<Range>>
{
};

INSTANTIATE_TEST_SUITE_P(sort_fixture, sort_fixture,
                         testing::Values(algorithm::bubble_sort<Range>,
                                         algorithm::insertion_sort<Range>,
                                         algorithm::selection_sort<Range>,
                                         algorithm::quick_sort<Range>,
                                         algorithm::merge_sort<Range>));

TEST_P(sort_fixture, sort_empty_range)
{
    sort_function<Range> sorter = GetParam();

    Range empty{};
    sorter(empty);
    EXPECT_THAT(empty, testing::IsEmpty());
}

TEST_P(sort_fixture, sort_one_element_range)
{
    sort_function<Range> sorter = GetParam();

    Range one_element{0};
    sorter(one_element);
    EXPECT_THAT(one_element, testing::ElementsAre(0));
}

TEST_P(sort_fixture, sort_same_element_range)
{
    sort_function<Range> sorter = GetParam();

    Range same_element{0, 0};
    sorter(same_element);
    EXPECT_THAT(same_element, testing::ElementsAre(0, 0));
}

TEST_P(sort_fixture, sort_two_sorted_elements_range)
{
    sort_function<Range> sorter = GetParam();

    Range two_sorted_elements{0, 1};
    sorter(two_sorted_elements);
    EXPECT_THAT(two_sorted_elements, testing::ElementsAre(0, 1));
}

TEST_P(sort_fixture, sort_two_unsorted_elements_range)
{
    sort_function<Range> sorter = GetParam();

    Range two_unsorted_elements{1, 0};
    sorter(two_unsorted_elements);
    EXPECT_THAT(two_unsorted_elements, testing::ElementsAre(0, 1));
}

TEST_P(sort_fixture, sort_many_sorted_elements_range)
{
    sort_function<Range> sorter = GetParam();

    Range many_sorted_elements{-2, -1, 0, 1, 2};
    sorter(many_sorted_elements);
    EXPECT_THAT(many_sorted_elements, testing::ElementsAre(-2, -1, 0, 1, 2));
}

TEST_P(sort_fixture, sort_many_unsorted_elements_range)
{
    sort_function<Range> sorter = GetParam();

    Range many_unsorted_elements{2, -1, 1, -2, 0};
    sorter(many_unsorted_elements);
    EXPECT_THAT(many_unsorted_elements, testing::ElementsAre(-2, -1, 0, 1, 2));
}

TEST_P(sort_fixture, sort_many_reverse_sorted_elements_range)
{
    sort_function<Range> sorter = GetParam();

    Range many_unsorted_elements{2, 1, 0, -1, -2};
    sorter(many_unsorted_elements);
    EXPECT_THAT(many_unsorted_elements, testing::ElementsAre(-2, -1, 0, 1, 2));
}

TEST_P(sort_fixture, experiment)
{
    sort_function<Range> sorter = GetParam();

    Range many_unsorted_elements{2, 8, 7, 1, 3, 5, 6, 4};
    sorter(many_unsorted_elements);
    EXPECT_THAT(many_unsorted_elements, testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8));
}
