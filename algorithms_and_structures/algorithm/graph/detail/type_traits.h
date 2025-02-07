#pragma once

#include "include/type_traits.h"

namespace algorithm
{
namespace detail
{
namespace impl
{
template <typename Vertex, typename Action>
constexpr bool is_action_invocable_v =
    std::is_invocable_v<Action, const Vertex&> || std::is_invocable_v<Action, Vertex>;

template <typename Vertex, typename NeighborGetter>
constexpr bool is_neighbor_getter_invocable_v = std::is_invocable_v<NeighborGetter, const Vertex&>;

}  // namespace impl

template <typename Range, typename Action, typename NeighborGetter>
constexpr bool are_for_graph_search_v =
    impl::is_action_invocable_v<std_ext::range_type_t<Range>, Action> &&
    impl::is_neighbor_getter_invocable_v<std_ext::range_type_t<Range>, NeighborGetter>;
}  // namespace detail

template <typename Range>
using vertex_t = std_ext::range_type_t<Range>;
}  // namespace algorithm
