#pragma once

#include <algorithm>
#include "detail/type_traits.h"

/* Operation iterator +/- n requires random access iterator, we have bidirectorial one so we use std::next, std::prev */
namespace algorithm
{
namespace detail
{
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    /* Start iteration from the right */
    for (auto right = std::prev(end); right != begin; --right)
    {
        /* Use second iterator for comparing values from the left */
        for (auto left = begin; left != right; ++left)
        {
            if (*left > *right)
            {
                std::swap(*left, *right);
            }
        }
    }
}
}  // namespace detail

template <typename Range, typename = detail::enable_if_sortable_t<Range>>
void bubble_sort(Range& range)
{
    auto begin = std::begin(range);
    auto end = std::end(range);

    if (begin == end)
    {
        return;
    }

    detail::bubble_sort(begin, end);
}
}  // namespace algorithm
