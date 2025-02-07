#pragma once

#include <type_traits>
#include <tuple>

namespace std_ext
{
template <typename...>
struct types;

namespace detail
{
template <typename AlwaysVoid, template <class...> typename Op, typename... Args>
struct detector : std::false_type
{
};

template <template <class...> typename Op, typename... Args>
struct detector<std::void_t<Op<Args...>>, Op, Args...> : std::true_type
{
};

template <typename Functor>
struct functor_traits : functor_traits<decltype(&Functor::operator())>
{
};

template <typename Functor, typename ReturnType, typename... Args>
struct functor_traits<ReturnType (Functor::*)(Args...) const>
{
   using return_type = ReturnType;
   using arg_types = types<Args...>;

   template <std::size_t Idx>
   struct arg
   {
      using type = typename std::tuple_element<Idx, std::tuple<Args...>>::type;
   };
};

template <typename T>
using has_eq_operator_t = decltype(std::declval<T>() == std::declval<T>());
}  // detail

template <typename...>
using always_false = std::false_type;

template <typename... Args>
constexpr bool always_false_v = always_false<Args...>::value;

template <bool... Args>
constexpr bool always_true_v = (Args && ...);

template <>
constexpr bool always_true_v<> = false;

template <bool B>
using require = std::enable_if_t<B, int>;

template <template <class...> typename Op, class... Args>
struct is_detected : detail::detector<void, Op, Args...>
{
};

template <typename T>
using iter_value_t = typename std::iterator_traits<T>::value_type;

template <typename Range>
using iterator_t = decltype(std::begin(std::declval<Range&>()));

template <typename Range>
using range_type_t = typename std::iterator_traits<iterator_t<Range>>::value_type;

template <class T>
using range_value_t = iter_value_t<iterator_t<T>>;

template <typename Functor, std::size_t Idx>
using arg_type_t = typename detail::functor_traits<Functor>::template arg<Idx>::type;

template <typename Functor>
using arg_types_t = typename detail::functor_traits<Functor>::arg_types;

template <typename Functor>
using return_type_t = typename detail::functor_traits<Functor>::return_type;

template <template <class...> typename Op, class... Args>
constexpr bool is_detected_v = is_detected<Op, Args...>::value;

template <typename T>
constexpr bool has_eq_operator_v = is_detected_v<detail::has_eq_operator_t, T>;

template <typename Range, typename Exp>
constexpr bool is_range_of_v = std::is_same_v<range_type_t<Range>, Exp>;

template <typename T>
constexpr bool is_iterable_v = is_detected_v<iterator_t, T>;

template <typename Ptr, typename T>
using ptr_rebind = typename std::pointer_traits<Ptr>::template rebind<T>;
}  // std_ext
