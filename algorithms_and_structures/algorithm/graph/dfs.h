#pragma once

#include "detail/dfs.h"

namespace algorithm
{
template <typename Range, typename Action, typename NeighborGetter,
          typename = std::enable_if_t<detail::are_for_graph_search_v<Range, Action, NeighborGetter>>>
void dfs(const Range& range, const Action& action, const NeighborGetter& getter)
{
    return detail::dfs(range, action, getter);
}
}  // namespace algorithm
