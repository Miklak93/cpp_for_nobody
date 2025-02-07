#pragma once

#include "detail/type_traits.h"

/* Operation iterator +/- n requires random access iterator, we have bidirectorial one so we use std::next, std::prev */
namespace algorithm
{
namespace detail
{
template <typename Iterator>
void selection_sort(Iterator begin, Iterator end)
{
   for (auto left = begin; left != std::prev(end); ++left)
   {
      auto min = left;
      for (auto right = left + 1; right != end; ++right)
      {
         /* Find minimal element in the right side of the range */
         if (*right < *min)
         {
            min = right;
         }
      }
      /* Move minimal element to the possible left position of the range */
      std::swap(*left, *min);
   }
}
}  // namespace detail

template <typename Range, typename = detail::enable_if_sortable_t<Range>>
void selection_sort(Range& range)
{
    auto begin = std::begin(range);
    auto end = std::end(range);

    if (begin == end)
    {
        return;
    }

    detail::selection_sort(begin, end);
}
}  // namespace algorithm

