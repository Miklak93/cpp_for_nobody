#pragma once

#include "include/type_traits.h"

/* Operation iterator +/- n requires random access iterator, we have bidirectorial one so we use std::next, std::prev */
namespace algorithm
{
namespace detail
{
void heapify() {}

template <typename Iterator>
void heap_sort(Iterator begin, Iterator end)
{
   auto distance = std::distance(begin, end);

   /* Build a maximal heap */
   for(auto it = std::next(begin, distance/2 - 1) ; std::distance(it, begin) >= 0; --it)
   {
      heapify(it, end);
   }

   /* One by one extract elements from the heap */
   for (auto it = std::prev(end); it != begin; --it)
   {
      std::swap(*begin, *it);
      heapify(begin, it);
   }
}

}  // namespace detail

template <typename Range, typename = detail::enable_if_sortable_t<Range>>
void heap_sort(Range& range)
{
    auto begin = std::begin(range);
    auto end = std::end(range);

    if (begin == end)
    {
        return;
    }
    detail::heap_sort(begin, end);
}
}  // namespace algorithm
