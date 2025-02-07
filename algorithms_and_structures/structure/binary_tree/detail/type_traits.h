#pragma once

#include "node.h"
#include "include/type_traits.h"

namespace structure
{
namespace detail
{
template <typename T>
struct binary_tree_traits
{
    using value_type = std::unique_ptr<node<T>>;
};

template <typename T, typename Function, typename = void>
struct is_invocable_with_cref : std::false_type
{
};

template <typename T, typename Function>
struct is_invocable_with_cref<T, Function, std::enable_if_t<std::is_invocable_v<Function, const T&>>> : std::true_type
{
};

template <typename T, typename Function>
constexpr bool is_invocable_with_cref_v = is_invocable_with_cref<T, Function>::value;
}  // namespace detail
}  // namespace structure
