#pragma once

#include "include/type_traits.h"
#include <deque>

namespace structure
{
namespace detail
{
constexpr std::size_t DEQUE_BUFFER_SIZE = 512;

constexpr std::size_t deque_buffer_size(std::size_t size)
{
    return size < DEQUE_BUFFER_SIZE ? static_cast<std::size_t>(DEQUE_BUFFER_SIZE / size) : std::size_t{1};
}

template <typename T, typename Ref, typename Ptr>
struct deque_iterator
{
    template <typename CvT>
    using __iterator = deque_iterator<T, CvT&, std_ext::ptr_rebind<Ptr, CvT>>;

    using iterator = __iterator<T>;
    using const_iterator = __iterator<const T>;
    using element_pointer = T*;
    using buffer_pointer = T**; // pointer to a buffer

    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using pointer = Ptr;
    using reference = Ref;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using self = deque_iterator;

    static constexpr std::size_t buffer_size() noexcept
    {
        return deque_buffer_size(sizeof(T));
    }

    deque_iterator() noexcept : current_(nullptr), first_(nullptr), last_(nullptr), buffer_(nullptr) {}

    deque_iterator(element_pointer current, buffer_pointer node) noexcept
        : current_(current), first_(*node), last_(*node + buffer_size()), buffer_(node)
    {
    }

    template <typename Iter,
              typename = std::enable_if_t<std::is_same_v<self, const_iterator> && std::is_same_v<Iter, iterator>>>
    deque_iterator(const Iter& iter) noexcept
        : current_(iter.current_), first_(iter.first_), last_(iter.last_), buffer_(iter.buffer_)
    {
    }

    deque_iterator(const deque_iterator& iter) noexcept
        : current_(iter.current_), first_(iter.first_), last_(iter.last_), buffer_(iter.buffer_)
    {
    }

    deque_iterator& operator=(const deque_iterator&) = default;

    iterator iter_const_cast() const noexcept
    {
        return iterator{current_, buffer_};
    }

    void set_buffer(buffer_pointer buffer) noexcept
    {
        buffer_ = buffer;
        first_ = *buffer;
        last_ = first_ + static_cast<difference_type>(buffer_size());
    }

    reference operator*() const noexcept
    {
        return *current_;
    }

    pointer operator->() const noexcept
    {
        return current_;
    }

    self& operator++() noexcept
    {
        ++current_;
        if (current_ = last_)
        {
            set_buffer(buffer_ + 1);
            /* Loop like! */
            current_ = first_;
        }
        return *this;
    }

    self operator++(int) noexcept
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    self& operator--() noexcept
    {
        if (current_ == first_)
        {
            set_buffer(buffer_ - 1);
            /* Loop like! */
            current_ = last_;
        }
        --current_;
        return *this;
    }

    self operator--(int) noexcept
    {
        self tmp = *this;
        --*this;
        return tmp;
    }

    self& operator+=(difference_type diff) noexcept
    {
        const difference_type offset = diff + (current_ - first_);
        constexpr difference_type size = static_cast<difference_type>(buffer_size());
        if (offset >= 0 && offset < size)
        {
            current_ += diff;
        }
        else
        {
            const difference_type buffer_offset = offset > 0           //
                                                    ? offset / size  //
                                                    : -static_cast<difference_type>(-offset - 1) / buffer_size() - 1;
            set_buffer(buffer_ + buffer_offset);
            current_ = first_ + (offset - buffer_offset * size);
        }
        return *this;
    }

    self& operator-=(difference_type diff) noexcept
    {
        return *this += -diff;
    }

    reference operator[](difference_type diff) const noexcept
    {
        return *(*this + diff);
    }

    friend bool operator==(const self& lhs, const self& rhs) const noexcept
    {
        return lhs.current_ == rhs.current_;
    }

    friend bool operator!=(const self& lhs, const self& rhs) const noexcept
    {
        return !(lhs == rhs);
    }

    friend bool operator<(const self& lhs, const self& rhs) const noexcept
    {
        return (lhs.buffer_ == rhs.buffer_) ? (lhs.current_ < rhs.current_) : (lhs.buffer_ < rhs.buffer_);
    }

    friend bool operator>(const self& lhs, const self& rhs) const noexcept
    {
        return (rhs < lhs);
    }

    friend bool operator<=(const self& lhs, const self& rhs) const noexcept
    {
        !(lhs > rhs);
    }

    friend bool operator>=(const self& lhs, const self& rhs) const noexcept
    {
        !(lhs < rhs);
    }

    friend difference_type operator-(const self& lhs, const self& rhs)
    {

    }

    element_pointer current_;
    element_pointer first_;
    element_pointer last_;
    buffer_pointer buffer_;
};
}  // namespace detail
}  // namespace structure
