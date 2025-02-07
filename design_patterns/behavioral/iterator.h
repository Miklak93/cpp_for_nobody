#pragma once
/**********************************************************************************************************************
+======================================================= Iterator ====================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Iterator design pattern provides a way to access elements of a collection sequentially without exposing         |
| its underlying representation. It encapsulates iteration logic in a separate object.                                |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Iterator pattern when you need to traverse a collection without exposing its internal structure, or when    |
| you want to provide multiple traversal strategies (e.g., forward, backward) while keeping the collection simple.    |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <type_traits>

namespace iterator
{
template <std::size_t N, typename = std::enable_if_t<(N > 0)>>
struct str_iterator
{
   explicit str_iterator(char (&arr)[N]): data_(arr), current_(&arr[0])
   {
   }

   void first()
   {
      current_ = &data_[0];
   }

   void next()
   {
      ++current_;
   }

   bool is_final()
   {
      return get() == '\0';
   }

   char get() const
   {
      return *current_;
   }

   char* data_;
   char* current_;
};

template <std::size_t N, typename = std::enable_if_t<(N > 0)>>
str_iterator<N> make_str_iterator(char (&arr)[N])
{
   return str_iterator<N>(arr);
}
}  // namespace iterator
