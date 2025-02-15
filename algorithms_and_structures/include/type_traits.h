#pragma once

#include <type_traits>

namespace std_ext
{
template <typename Range>
using iterator_t = decltype(std::begin(std::declval<Range&>()));
}  // namespace std_ext
