#pragma once

#include <vector>
#include "include/type_traits.h"

namespace algorithm
{
namespace detail
{
template <typename Iterator>
void merge(Iterator begin, Iterator middle, Iterator end)
{
    using value_type = std::remove_cvref_t<decltype(*begin)>;

    /* Copy the left part of the range to the array */
    std::vector<value_type> left{begin, middle};

    /* Copy the right part of the range to the array */
    std::vector<value_type> right{middle, end};

    /* The left_it value is the smallest remaining index of the element in the left array */
    auto left_it = std::begin(left);

    /* The right_it value is the smallest remaining index of the element in the right array */
    auto right_it = std::begin(right);

    /* Position from where we start filling the range */
    auto current = begin;

    auto left_end = std::end(left);
    auto right_end = std::end(right);
    while (left_it != left_end && right_it != right_end)
    {
        /* If left half contains smaller element, insert it to the range */
        if (*left_it < *right_it)
        {
            *current = *left_it;
            ++left_it;
        }
        /* Otherwise insert right half element to the range */
        else
        {
            *current = *right_it;
            ++right_it;
        }
        ++current;
    }

    /* Some elements could left so copy them to the array */
    while (left_it != left_end)
    {
        *current = *left_it;
        ++left_it;
        ++current;
    }
    while (right_it != right_end)
    {
        *current = *right_it;
        ++right_it;
        ++current;
    }
}

template <typename Iterator>
void merge_sort(Iterator begin, Iterator end)
{
    if (std::distance(begin, end) <= 1)
    {
        return;
    }

    /* Select the middle point */
    auto middle = std::next(begin, std::distance(begin, end) / 2);

    /* Sort the left part of the range */
    merge_sort(begin, middle);

    /* Sort the right part of the range */
    merge_sort(middle, end);

    /* Merge two halves */
    merge(begin, middle, end);
}
}  // namespace detail

template <typename Range, typename = detail::enable_if_sortable_t<Range>>
void merge_sort(Range& range)
{
    detail::merge_sort(std::begin(range), std::end(range));
}
}  // namespace algorithm
