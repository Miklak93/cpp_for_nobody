#pragma once

#include <memory>
#include <iostream>

namespace structure
{
namespace detail
{
template <typename T>
struct node
{
    T data;
    std::unique_ptr<node<T>> left;
    std::unique_ptr<node<T>> right;
};
}  // namespace detail
}  // namespace structure
