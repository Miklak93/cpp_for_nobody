#pragma once

#include <set>
#include "detail/type_traits.h"

namespace algorithm
{
namespace detail
{
namespace impl
{
template <typename Range, typename Action, typename NeighborGetter>
struct dfs
{
    void operator()()
    {
        for (const auto& vertex : range)
        {
            if (!visited.contains(&vertex))
            {
                (*this)(vertex);
            }
        }
    }

    template <typename Vertex>
    void operator()(const Vertex& vertex)
    {
        visited.insert(&vertex);
        action(vertex);

        for (const auto& neighbor : getter(vertex))
        {
            if (!visited.contains(&neighbor))
            {
                (*this)(neighbor);
            }
        }
    }

    const Range& range;
    const Action& action;
    const NeighborGetter& getter;
    std::set<const vertex_t<Range>*> visited;
};
}  // namespace impl

template <typename Range, typename Action, typename NeighborGetter,
          typename = std::enable_if_t<are_for_graph_search_v<Range, Action, NeighborGetter>>>
void dfs(const Range& range, const Action& action, const NeighborGetter& getter)
{
    impl::dfs<Range, Action, NeighborGetter> algorithm{range, action, getter};
    algorithm();
}
}  // namespace detail
}  // namespace algorithm
