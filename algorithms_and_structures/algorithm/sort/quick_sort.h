#pragma once

#include "detail/type_traits.h"

/* Operation iterator +/- n requires random access iterator, we have bidirectorial one so we use std::next, std::prev */
namespace algorithm
{
namespace detail
{
template <typename Iterator>
Iterator partition(Iterator begin, Iterator end)
{
    /* Choose the last element as the pivot (can be any random) */
    auto pivot = std::prev(end);

    /* The left iterator, which will track the boundary between smaller and larger elements */
    auto left = begin;
    for (auto current = begin; current != std::prev(end); ++current)
    {
        /* Move through the range and rearrange elements smaller than the pivot to the left */
        if (*current < *pivot)
        {
            std::swap(*left, *current);
            ++left;
        }
    }

    /* The pivot has the smallest value now so move it to the most-left position */
    std::swap(*left, *pivot);

    /* Return the pivot's final position */
    return left;
}

template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return;
    }

    /* Partition the range and get the pivot position */
    auto pivot = partition(begin, end);

    /* Sort elements before the pivot */
    quick_sort(begin, pivot);

    /* Sort elements after the pivot */
    quick_sort(std::next(pivot), end);
}
}  // namespace detail

template <typename Range, typename = detail::enable_if_sortable_t<Range>>
void quick_sort(Range& range)
{
    detail::quick_sort(std::begin(range), std::end(range));
}
}  // namespace algorithm
