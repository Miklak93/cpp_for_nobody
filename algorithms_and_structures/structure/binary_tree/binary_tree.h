#pragma once

#include "detail/algorithm.h"

namespace structure
{
template <typename T>
class binary_tree
{
    public:
    using value_type = T;
    using node_type = typename detail::binary_tree_traits<T>::value_type;

    binary_tree() : root_(nullptr), size_(0) {}

    template <typename... Values, typename = std::enable_if_t<(std::is_convertible_v<Values, T> && ...)>>
    explicit binary_tree(Values&&... values) : root_(nullptr), size_(sizeof...(Values))
    {
        (detail::insert<T, Values>(root_, std::forward<Values>(values)), ...);
    }

    binary_tree(const binary_tree<T>& other) : root_(detail::make_node<T>(other.root_->data)), size_(other.size_)
    {
        static const auto processor = [](const node_type& from, node_type& to) { detail::copy<T>(from, to); };
        detail::traverse_pairwise(other.root_, root_, processor);
    }

    binary_tree(binary_tree<T>&& other) : root_(std::move(other.root_)), size_(std::move(other.size_))
    {
        other.size_ = 0;
    };

    binary_tree<T>& operator=(const binary_tree<T>& other)
    {
        if (this == &other)
        {
            return *this;
        }

        root_.reset();

        static const auto processor = [](const node_type& from, node_type& to) { detail::copy<T>(from, to); };
        root_ = detail::make_node<T>(other.root_->data);
        detail::traverse_pairwise(other.root_, root_, processor);

        size_ = other.size_;

        return *this;
    }

    binary_tree<T>& operator=(binary_tree<T>&& other)
    {
        if (this == &other)
        {
            return *this;
        }

        root_.reset();

        root_ = std::move(other.root_);
        size_ = other.size_;
        other.size_ = 0;

        return *this;
    }

    /* We are using unique pointers so they will be removed automatically */
    ~binary_tree() = default;

    template <typename... Values, typename = std::enable_if_t<(std::is_convertible_v<Values, T> && ...)>>
    void insert(Values&&... values)
    {
        (detail::insert<T, Values>(root_, std::forward<Values>(values)), ...);
        size_ += sizeof...(Values);
    }

    template <typename Predicate, typename = std::enable_if<std::is_same_v<std::invoke_result_t<Predicate, T>, bool>>>
    void remove_if(Predicate&& predicate)
    {
        detail::for_each(
            root_, [&](node_type& node) { detail::remove_if<T, Predicate>(node, std::forward<Predicate>(predicate)); });

        /* Recalculate size*/
        size_ = 0;
        detail::traverse_inorder(root_, [&](const node_type& node) { ++size_; });
    }

    template <typename Function, typename = std::enable_if_t<detail::is_invocable_with_cref_v<T, Function>>>
    void traverse_inorder(Function&& function) const
    {
        detail::traverse_inorder(root_,
                                 [&](const node_type& node) { return std::forward<Function>(function)(node->data); });
    }

    template <typename Function, typename = std::enable_if_t<detail::is_invocable_with_cref_v<T, Function>>>
    void traverse_preorder(Function&& function) const
    {
        detail::traverse_preorder(root_,
                                  [&](const node_type& node) { return std::forward<Function>(function)(node->data); });
    }

    template <typename Function, typename = std::enable_if_t<detail::is_invocable_with_cref_v<T, Function>>>
    void traverse_postorder(Function&& function) const
    {
        detail::traverse_postorder(root_,
                                   [&](const node_type& node) { return std::forward<Function>(function)(node->data); });
    }

    bool empty() const noexcept
    {
        return root_ == nullptr;
    }

    std::size_t size() const noexcept
    {
        return size_;
    }

    private:
    node_type root_;
    std::size_t size_;
};
}  // namespace structure
