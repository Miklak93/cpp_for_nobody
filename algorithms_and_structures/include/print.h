#pragma once

#include <iostream>

namespace utilities
{
namespace detail
{
// Can be printed
}  // namespace detail

enum class print_mode
{
    Debug,
    Release
};

template <print_mode mode>
struct print
{
    template <typename T>
    std::ostream& operator<<(const T& t)
    {
        std::cout << t;
        return *this;
    }

    /*  Overload for std::endl like objects from std::ostream */
    print& operator<<(std::ostream& (*pf)(std::ostream&))
    {
        pf(std::cout);
        return *this;
    }
};

template <>
struct print<print_mode::Release>
{
    template <typename T>
    std::ostream& operator<<(const T&)
    {
        return *this;
    }

    /*  Overload for std::endl like objects from std::ostream */
    print& operator<<(std::ostream& (*)(std::ostream&))
    {
        return *this;
    }
};
}  // namespace utilities
