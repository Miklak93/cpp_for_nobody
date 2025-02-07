#pragma once

#include "node.h"
#include "type_traits.h"

namespace structure
{
namespace detail
{
template <typename T>
binary_tree_traits<T>::value_type make_node(const T& t)
{
    return std::make_unique<detail::node<T>>(t);
}

template <typename Node, typename Function>
void traverse_inorder(const Node& node, Function&& function)
{
    if (!node)
    {
        return;
    }

    /* Process left */
    traverse_inorder(node->left, function);
    /* Process root */
    function(node);
    /* Process right */
    traverse_inorder(node->right, function);
}

template <typename Node, typename Function>
void traverse_preorder(const Node& node, const Function& function)
{
    if (!node)
    {
        return;
    }

    /* Process root */
    function(node);
    /* Process left */
    traverse_preorder(node->left, function);
    /* Process right */
    traverse_preorder(node->right, function);
}

template <typename Node, typename Function>
void traverse_postorder(const Node& node, const Function& function)
{
    if (!node)
    {
        return;
    }

    /* Process left */
    traverse_postorder(node->left, function);
    /* Process right */
    traverse_postorder(node->right, function);
    /* Process root */
    function(node);
}

template <typename Node1, typename Node2, typename Function>
void traverse_pairwise(Node1&& lhs, Node2&& rhs, const Function& function)
{
    if (!lhs || !rhs)
    {
        return;
    }

    function(lhs, rhs);
    traverse_pairwise(lhs->left, rhs->left, function);
    traverse_pairwise(lhs->right, rhs->right, function);
}

template <typename Node, typename Function>
void for_each(Node& node, const Function& function)
{
    if (!node)
    {
        return;
    }

    /* Process left */
    for_each(node->left, function);
    /* Process right */
    for_each(node->right, function);
    /* Possibly modify node */
    function(node);
    if (!node)
    {
        return;
    }
}

template <typename T>
void copy(const typename binary_tree_traits<T>::value_type& from, typename binary_tree_traits<T>::value_type& to)
{
    if (!from)
    {
        return;
    }
    if (from->left)
    {
        to->left = make_node<T>(from->left->data);
    }
    if (from->right)
    {
        to->right = make_node<T>(from->right->data);
    }
}

template <typename T, typename V, typename = std::enable_if_t<std::is_convertible_v<V, T>>>
void insert(typename binary_tree_traits<T>::value_type& node, V&& v)
{
    if (!node)
    {
        node = make_node(static_cast<T>(v));
        return;
    }
    static_cast<T>(v) < node->data ? insert<T, V>(node->left, std::forward<V>(v))
                                   : insert<T, V>(node->right, std::forward<V>(v));
}

template <typename T, typename Predicate,
          typename = std::enable_if<std::is_same_v<std::invoke_result_t<Predicate, T>, bool>>>
void remove_if(typename binary_tree_traits<T>::value_type& node, const Predicate& predicate)
{
    if (node && predicate(node->data))
    {
        node.reset();
    }
}
}  // namespace detail
}  // namespace structure
