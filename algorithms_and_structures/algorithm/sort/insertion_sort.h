#pragma once

#include "detail/type_traits.h"

/* Operation iterator +/- n requires random access iterator, we have bidirectorial one so we use std::next, std::prev */
namespace algorithm
{
namespace detail
{
template <typename Iterator>
void insertion_sort(Iterator begin, Iterator end)
{
    for (auto right = std::next(begin); right != end; ++right)
    {
        const auto to_insert = *right;
        auto left = right;

        /* Move elements to the right as long as they are greater than to_insert value */
        while (left != begin && *(std::prev(left)) > to_insert)
        {
            *left = *(std::prev(left));  // Shift element to the right
            left = std::prev(left);      // Move left iterator one position left
        }

        /* Place right_value in the correct position as being the lowest in the range now */
        *left = to_insert;
    }
}
}  // namespace detail

template <typename Range, typename = detail::enable_if_sortable_t<Range>>
void insertion_sort(Range& range)
{
    auto begin = std::begin(range);
    auto end = std::end(range);

    if (begin == end)
    {
        return;
    }

    detail::insertion_sort(begin, end);
}
}  // namespace algorithm
