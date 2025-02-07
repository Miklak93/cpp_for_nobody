#pragma once

#include "include/type_traits.h"

namespace algorithm
{
namespace detail
{
/* Is comparable must be implemented */
template <typename Range>
constexpr bool is_sortable_v = std::is_base_of_v<std::bidirectional_iterator_tag, typename std_ext::iterator_t<Range>::iterator_category>;

template <typename Range>
using enable_if_sortable_t = std::enable_if_t<is_sortable_v<Range>, bool>;
}  // namespace detail
}  // namespace algorithm
