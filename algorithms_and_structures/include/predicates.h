#pragma once

#include <boost/none_t.hpp>
#include <functional>
#include <tuple>
#include <optional>
#include "type_traits.h"

namespace predicates
{

namespace detail
{

template <class Func, class... Args>
using is_invocable_impl = decltype(std::declval<Func>()(std::declval<Args>()...));

template <class L, class R>
using is_equality_comparable_impl = decltype(std::declval<L>() == std::declval<R>());

template <class Func, class... Args>
struct is_invocable : std_ext::is_detected<is_invocable_impl, Func, Args...>
{
};

template <class L, class R>
struct is_equality_comparable : std_ext::is_detected<is_equality_comparable_impl, L, R>
{
};

template <class P, class Type = void>
class PredicateWrapper
{
public:
   PredicateWrapper() = delete;

   explicit PredicateWrapper(P pred)
    : pred_(std::move(pred))
   {}

   PredicateWrapper(const PredicateWrapper&) = default;
   PredicateWrapper(PredicateWrapper&&) = default;

   template <class T>
   bool operator()(const T& item) const
   {
      return call(item);
   }

private:
   template <class T, typename std::enable_if<is_invocable<P, T>::value && is_equality_comparable<T, P>::value, int>::type = 0>
   bool call(const T& item) const
   {
      return pred_(item);
   }

   template <class T, typename std::enable_if<is_invocable<P, T>::value && !is_equality_comparable<T, P>::value, int>::type = 0>
   bool call(const T& item) const
   {
      return pred_(item);
   }

   template <class T, typename std::enable_if<!is_invocable<P, T>::value && is_equality_comparable<T, P>::value, int>::type = 0>
   bool call(const T& item) const
   {
      return item == static_cast<T>(pred_);
   }

   template <class T, typename std::enable_if<!is_invocable<P, T>::value && !is_equality_comparable<T, P>::value, int>::type = 0>
   void call(const T&) const
   {
      static_assert(std_ext::always_false<T>(), "Predicate should be either callable or equality comparable with the argument.");
   }

   P pred_;
};

template <class P>
PredicateWrapper<P> as_predicate(P pred)
{
   return PredicateWrapper<P>{ std::move(pred) };
}

template <class... Args>
PredicateWrapper<Args...> as_predicate(PredicateWrapper<Args...> predicate)
{
   return predicate;
}

template <class T>
class PredicateWrapper<void, T>
{
public:
   template <class P, typename std::enable_if<is_invocable<P, T>::value || is_equality_comparable<T, P>::value, int>::type = 0>
   // clang-format off
   // cppcheck-suppress noExplicitConstructor
   PredicateWrapper(P pred) : pred_(as_predicate(std::move(pred))) {}  // NOLINT(runtime/explicit)
   // clang-format on

   PredicateWrapper(const PredicateWrapper&) = default;
   PredicateWrapper(PredicateWrapper&&) = default;

   bool operator()(T item) const { return pred_ && pred_(item); }

private:
   std::function<bool(T)> pred_;
};

template <class T, class... Args>
bool operator|(const T& item, const PredicateWrapper<Args...>& predicate)
{
   return predicate(item);
}

template <class T>
using Predicate = PredicateWrapper<void, T>;

template <class T>
struct is_predicate : std::false_type
{
};

template <class... Args>
struct is_predicate<PredicateWrapper<Args...>> : std::true_type
{
};

class Negation
{
   template <class P>
   struct Impl
   {
      P inner_;

      explicit Impl(P inner)
       : inner_(std::move(inner))
      {}

      template <class T>
      bool operator()(const T& item) const
      {
         return !inner_(item);
      }
   };

   template <class P>
   static Impl<P> make(P pred)
   {
      return Impl<P>{ std::move(pred) };
   }

public:
   template <class P>
   auto operator()(P inner) const -> decltype(as_predicate(make(as_predicate(inner))))
   {
      return as_predicate(make(as_predicate(inner)));
   }
};

template <std::size_t M, std::size_t N>
struct Tag
{
};

template <class Fn, bool DefVal>
class Compound
{
   template <class... Ps>
   struct Impl
   {
      explicit Impl(Ps... predicates)
       : predicates_{ std::move(predicates)... }
      {}

      template <class T>
      bool operator()(const T& item) const
      {
         return call(Tag<0, sizeof...(Ps)>{}, item);
      }

      template <std::size_t N, std::size_t S, class T>
      bool call(Tag<N, S>, const T& item) const
      {
         return Fn{}(std::get<N>(predicates_)(item), call(Tag<N + 1, S>{}, item));
      }

      template <std::size_t S, class T>
      static bool call(Tag<S, S>, const T&)
      {
         return DefVal;
      }

      std::tuple<Ps...> predicates_;
   };

   template <class... Ps>
   static Impl<Ps...> make(Ps... predicates)
   {
      return Impl<Ps...>{ std::move(predicates)... };
   }

public:
   template <class... Ps>
   auto operator()(Ps... predicates) const -> decltype(as_predicate(make(as_predicate(predicates)...)))
   {
      return as_predicate(make(as_predicate(predicates)...));
   }
};

constexpr auto negation = Negation{};
constexpr auto all = Compound<std::logical_and<bool>, true>{};
constexpr auto any = Compound<std::logical_or<bool>, false>{};

template <class... Args>
auto operator!(PredicateWrapper<Args...> predicate) -> decltype(negation(std::move(predicate)))
{
   return negation(std::move(predicate));
}

template <class... L, class... R>
auto operator&&(PredicateWrapper<L...> lhs, PredicateWrapper<R...> rhs) -> decltype(all(std::move(lhs), std::move(rhs)))
{
   return all(std::move(lhs), std::move(rhs));
}

template <class... L, class... R>
auto operator||(PredicateWrapper<L...> lhs, PredicateWrapper<R...> rhs) -> decltype(any(std::move(lhs), std::move(rhs)))
{
   return any(std::move(lhs), std::move(rhs));
}

template <template <class> class Op>
class Compare
{
   template <class V>
   struct Impl
   {
      V value_;

      template <class T>
      bool operator()(const T& item) const
      {
         return Op<T>{}(item, static_cast<T>(value_));
      }
   };

   template <class V>
   static Impl<V> make(V value)
   {
      return Impl<V>{ std::move(value) };
   }

public:
   template <class V>
   auto operator()(V value) const -> decltype(as_predicate(make(std::move(value))))
   {
      return as_predicate(make(std::move(value)));
   }
};

class Each
{
   template <class P>
   struct Impl
   {
      P inner_;

      template <class T>
      bool operator()(const T& item) const
      {
         return std::all_of(std::begin(item), std::end(item), inner_);
      }
   };

   template <class P>
   static Impl<P> make(P pred)
   {
      return Impl<P>{ std::move(pred) };
   }

public:
   template <class P>
   auto operator()(P pred) const -> decltype(as_predicate(make(as_predicate(pred))))
   {
      return as_predicate(make(as_predicate(pred)));
   }
};

class Contains
{
   template <class P, class N>
   struct Impl
   {
      P inner_;
      N number_;

      template <class T>
      bool operator()(const T& item) const
      {
         return number_(std::count_if(std::begin(item), std::end(item), inner_));
      }
   };

   template <class P>
   struct Impl<P, void>
   {
      P inner_;

      template <class T>
      bool operator()(const T& item) const
      {
         return std::any_of(std::begin(item), std::end(item), inner_);
      }
   };

   template <class P, class N>
   static Impl<P, N> make(P pred, N number)
   {
      return Impl<P, N>{ std::move(pred), std::move(number) };
   }

   template <class P>
   static Impl<P, void> make(P pred)
   {
      return Impl<P, void>{ std::move(pred) };
   }

public:
   template <class P, class N>
   auto operator()(P pred, N number) const -> decltype(as_predicate(make(as_predicate(std::move(pred)), as_predicate(std::move(number)))))
   {
      return as_predicate(make(as_predicate(std::move(pred)), as_predicate(std::move(number))));
   }

   template <class P>
   auto operator()(P pred) const -> decltype(as_predicate(make(as_predicate(std::move(pred)))))
   {
      return as_predicate(make(as_predicate(std::move(pred))));
   }
};

class SizeIs
{
   template <class P>
   struct Impl
   {
      P inner_;

      template <class T>
      bool operator()(const T& item) const
      {
         return inner_(std::distance(std::begin(item), std::end(item)));
      }
   };

   template <class P>
   static Impl<P> make(P pred)
   {
      return Impl<P>{ std::move(pred) };
   }

public:
   template <class P>
   auto operator()(P pred) const -> decltype(as_predicate(make(as_predicate(std::move(pred)))))
   {
      return as_predicate(make(as_predicate(std::move(pred))));
   }
};

class IsEmpty
{
   struct Impl
   {
      template <class T>
      bool operator()(const T& item) const
      {
         return std::begin(item) == std::end(item);
      }
   };

   static Impl make() { return {}; }

public:
   auto operator()() const -> decltype(as_predicate(make())) { return as_predicate(make()); }
};

template <bool Value>
class Constant
{
   struct Impl
   {
      template <class T>
      bool operator()(const T&) const
      {
         return Value;
      }
   };

   static Impl make() { return {}; }

public:
   auto operator()() const -> decltype(as_predicate(make())) { return as_predicate(make()); }
};

static constexpr auto always = Constant<true>{};
static constexpr auto never = Constant<false>{};

class ResultOf
{
   template <class Func, class P>
   struct Impl
   {
      Func func_;
      P pred_;

      template <class T>
      bool operator()(const T& item) const
      {
         return pred_(func_(item));
      }
   };

   template <class Func, class P>
   static Impl<Func, P> make(Func func, P pred)
   {
      return Impl<Func, P>{ std::move(func), std::move(pred) };
   }

public:
   template <class Func, class P>
   auto operator()(Func func, P pred) const -> decltype(as_predicate(make(std::move(func), as_predicate(std::move(pred)))))
   {
      return as_predicate(make(std::move(func), as_predicate(std::move(pred))));
   }
};

class Member
{
   template <class M, class P>
   struct Impl
   {
      M member_;
      P pred_;

      template <class T>
      bool operator()(const T& item) const
      {
         return pred_(member_(item));
      }
   };

   template <class M, class P>
   static Impl<M, P> make(M member, P pred)
   {
      return Impl<M, P>{ std::move(member), std::move(pred) };
   }

public:
   template <class M, class P>
   auto operator()(M member, P pred) const -> decltype(as_predicate(make(std::mem_fn(member), as_predicate(std::move(pred)))))
   {
      return as_predicate(make(std::mem_fn(member), as_predicate(std::move(pred))));
   }
};

template <std::size_t N>
class Element
{
   template <class P>
   struct Impl
   {
      P pred_;

      template <class T>
      bool operator()(const T& item) const
      {
         return pred_(std::get<N>(item));
      }
   };

   template <class P>
   static Impl<P> make(P pred)
   {
      return Impl<P>{ std::move(pred) };
   }

public:
   template <class P>
   auto operator()(P pred) const -> decltype(as_predicate(make(as_predicate(std::move(pred)))))
   {
      return as_predicate(make(as_predicate(std::move(pred))));
   }
};

class FieldsAre
{
   template <class... Preds>
   struct Impl
   {
      std::tuple<Preds...> preds_;

      template <class T>
      bool operator()(const T& item) const
      {
         return call(Tag<0, sizeof...(Preds)>{}, item);
      }

      template <std::size_t N, std::size_t S, class T>
      bool call(Tag<N, S>, const T& item) const
      {
         return std::get<N>(preds_)(std::get<N>(item)) && call(Tag<N + 1, S>{}, item);
      }

      template <std::size_t S, class T>
      static bool call(Tag<S, S>, const T&)
      {
         return true;
      }
   };

   template <class... Preds>
   static Impl<Preds...> make(Preds... preds)
   {
      return Impl<Preds...>{ std::tuple<Preds...>(std::move(preds)...) };
   }

public:
   template <class... Preds>
   auto operator()(Preds... preds) const -> decltype(as_predicate(make(as_predicate(std::move(preds))...)))
   {
      return as_predicate(make(as_predicate(std::move(preds))...));
   }
};

class HasValue
{
   template <class P>
   struct Impl
   {
      P pred_;

      template <class T>
      bool operator()(const T& item) const
      {
         return static_cast<bool>(item) && pred_(*item);
      }

      bool operator()(std::nullptr_t) const { return false; }

      bool operator()(std::nullopt_t) const { return false; }

      bool operator()(boost::none_t) const { return false; }
   };

   template <class P>
   static Impl<P> make(P pred)
   {
      return Impl<P>{ std::move(pred) };
   }

   static auto make() -> decltype(make(always())) { return make(always()); }

public:
   template <class P>
   auto operator()(P pred) const -> decltype(as_predicate(make(as_predicate(std::move(pred)))))
   {
      return as_predicate(make(as_predicate(std::move(pred))));
   }

   auto operator()() const -> decltype(as_predicate(make())) { return as_predicate(make()); }
};

}  // namespace detail

using detail::Predicate;

using detail::as_predicate;

/*
   negation(value_or_predicate)(object)

   Returns 'true' if 'object' does not match 'value_or_predicate'.
*/
using detail::negation;

/*
   all(values_or_predicates...)(object)

   Checks if 'object' matches all 'values_or_predicates'.
*/
using detail::all;

/*
   any(values_or_predicates...)(object)

   Checks if 'object' matches at least one of 'values_or_predicates'.
*/
using detail::any;

/*
   always()(object)

   Always returns 'true'.
*/
using detail::always;

/*
   never()(object)

   Always returns 'false'.
*/
using detail::never;

/*
   equal_to(value)(object)

   Checks if 'object' == 'value'.
   Equivalent of testing::Eq(v)
*/
constexpr auto equal_to = detail::Compare<std::equal_to>{};

/*
   not_equal_to(value)(object)

   Checks if 'object' != 'value'.
   Equivalent of testing::Ne(v)
*/
constexpr auto not_equal_to = detail::Compare<std::not_equal_to>{};

/*
   less(value)(object)

   Checks if 'object' < 'value'.
   Equivalent of testing::Lt(v)
*/
constexpr auto less = detail::Compare<std::less>{};

/*
   greater(value)(object)

   Checks if 'object' > 'value'.
   Equivalent of testing::Gt(v)
*/
constexpr auto greater = detail::Compare<std::greater>{};

/*
   less_equal(value)(object)

   Checks if 'object' <= 'value'.
   Equivalent of testing::Le(v)
*/
constexpr auto less_equal = detail::Compare<std::less_equal>{};

/*
   greater_equal(value)(object)

   Checks if 'object' >= 'value'.
   Equivalent of testing::Ge(v)
*/
constexpr auto greater_equal = detail::Compare<std::greater_equal>{};

/*
   [1] contains(item_value_or_predicate)(container)

   Checks if 'container' has at least one item which matches 'value_or_predicate'.
   Equivalent of testing::Contains(e).Times(n)

   [2] contains(item_value_or_predicate, number_value_or_predicate)(container)

   Checks if the number of items of the 'container' which match 'item_value_or_predicate', matches 'number_value_or_predicate'.
   Equivalent of testing::Contains(e)
*/
constexpr auto contains = detail::Contains{};

/*
   each(item_value_or_predicate)(container)

   Checks if every item of the 'container' matches 'item_value_or_predicate'. Returns 'true' if 'container' is empty.
   Equivalent of testing::Each(e)
*/
constexpr auto each = detail::Each{};

/*
   size_is(size_value_or_predicate)(container)

   Checks if size of the 'container' matches 'size_value_or_predicate'.
   Equivalent of testing::SizeIs(m)
*/
constexpr auto size_is = detail::SizeIs{};

/*
   is_empty()(container)

   Checks if 'container' has no items.
   Equivalent of testing::IsEmpty()
*/
constexpr auto is_empty = detail::IsEmpty{};

/*
   result_of(function, result_value_or_predicate)(object)

   Checks if the result of the 'function(object)' matches 'result_value_or_predicate'.
   Equivalent of testing::ResultOf(f, m)
*/
constexpr auto result_of = detail::ResultOf{};

/*
   field(member, value_or_predicate)(object)

   Checks if 'object.member' matches 'value_or_predicate'.
   Equivalent of testing::Field(f, m)
*/
constexpr auto field = detail::Member{};

/*
   property(member, value_or_predicate)(object)

   Checks if 'object.member()' matches 'value_or_predicate'.
   Equivalent of testing::Property(f, m)
*/
constexpr auto property = detail::Member{};

/*
   [1] has_value()(optional)

   Checks if 'optional' (optional/pointer) has value.

   [2] has_value(value_or_predicate)(optional)

   Checks if 'optional' (optional/pointer) has value and its value matches 'value_or_predicate'.
*/
constexpr auto has_value = detail::HasValue{};

/*
   first(value_or_predicate)(tuple)

   Checks if the result of std::get<0>(tuple) matches 'value_or_predicate'.
*/
constexpr auto first = detail::Element<0>{};

/*
   second(value_or_predicate)(tuple)

   Checks if the result of std::get<1>(tuple) matches 'value_or_predicate'.
*/
constexpr auto second = detail::Element<1>{};

constexpr auto map_key = first;
constexpr auto map_value = second;

/*
   fields_are(value_or_predicate...)(tuple)

   Checks if all tuple's elements match corresponding matchers or values.
   Equivalent of testing::FieldsAre(e0, e1, ..., en)
*/
constexpr auto fields_are = detail::FieldsAre{};

template <class T, class P>
bool matches(const T& item, const P& pred)
{
   return pred(item);
}

template <class... Args>
auto contains_any(Args... args) -> decltype(any(contains(std::move(args))...))
{
   return any(contains(std::move(args))...);
}

template <class... Args>
auto contains_all(Args... args) -> decltype(all(contains(std::move(args))...))
{
   return all(contains(std::move(args))...);
}

}  // namespace predicates
