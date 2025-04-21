/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include <btree_utils.hpp>

template <class T>
int compute_height(const BTree<T> &t)
{
    int height = 0;
    //
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.
    if (t.is_empty())
    {
        height = -1;
    }
    else
    {
        height = 1 + std::max(compute_height(t.left()), compute_height(t.right()));
    }
    //
    return height;
}

template <class T>
size_t compute_size(const BTree<T> &t)
{
    size_t ret_val = 0;
    //
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.
    if (t.is_empty())
    {
        ret_val = 0;
    }
    else
    {
        ret_val = 1 + compute_size(t.left()) + compute_size(t.right());
    }
    //
    return ret_val;
}

template <class T, typename Processor>
bool prefix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    //
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.
    if (!tree.is_empty())
    {
        retVal = p(tree.item());
        retVal = retVal && prefix_process(tree.left(), p);
        retVal = retVal && prefix_process(tree.right(), p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool infix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    //
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.
    if (!tree.is_empty())
    {
        retVal = infix_process(tree.left(), p);
        retVal = retVal && p(tree.item());
        retVal = retVal && infix_process(tree.right(), p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool postfix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    //
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.
    if (!tree.is_empty())
    {
        retVal = postfix_process(tree.left(), p);
        retVal = retVal && postfix_process(tree.right(), p);
        retVal = retVal && p(tree.item());
    }
    //
    return retVal;
}

template <class T, class Processor>
bool breadth_first_process(const BTree<T> &tree, Processor &p)
{
    bool go_on = true;
    //
    // Hint: think about which data structure can help you to do this kind
    //   of traversal.
    if (!tree.is_empty())
    {
        std::queue<BTree<T>> nodeQueue;
        nodeQueue.push(tree);

        while (!nodeQueue.empty() && go_on)
        {
            BTree<T> currentNode = nodeQueue.front();
            nodeQueue.pop();

            go_on = p(currentNode.item());

            if (go_on && !currentNode.left().is_empty())
            {
                nodeQueue.push(currentNode.left());
            }

            if (go_on && !currentNode.right().is_empty())
            {
                nodeQueue.push(currentNode.right());
            }
        }
    }
    //
    return go_on;
}

template <class T>
std::ostream &
print_prefix(std::ostream &out, const BTree<T> &tree)
{
    //
    // You must create a lambda function with a parameter to be printed and
    //   use a prefix_process to process the tree with this lambda.
    // Remember: the lambda must return true.
    auto print_lambda = [&out](const T &item) -> bool
    {
        out << item << " ";
        return true;
    };

    prefix_process(tree, print_lambda);
    //
    return out;
}

template <class T>
std::ostream &
print_infix(std::ostream &out, const BTree<T> &tree)
{
    //
    // You must create a lambda function with a parameter to be printed and
    //   use an infix_process to process the tree with this lambda.
    // Remember: the lambda must return true.
    auto print_lambda = [&out](const T &item) -> bool
    {
        out << item << " ";
        return true;
    };

    infix_process(tree, print_lambda);
    //
    return out;
}

template <class T>
std::ostream &
print_postfix(std::ostream &out, const BTree<T> &tree)
{
    //
    // You must create a lambda function with a parameter to be printed and
    //   use a postfix_process to process the tree with this lambda.
    // Remember: the lambda must return true.
    auto print_lambda = [&out](const T &item) -> bool
    {
        out << item << " ";
        return true;
    };

    postfix_process(tree, print_lambda);
    //
    return out;
}

template <class T>
std::ostream &
print_breadth_first(std::ostream &out, const BTree<T> &tree)
{
    //
    // You must create a lambda function with a parameter to be printed and
    //   use a breadth_first_process to process the tree with this lambda.
    // Remember: the lambda must return true.
    auto print_lambda = [&out](const T &item) -> bool
    {
        out << item << " ";
        return true;
    };

    breadth_first_process(tree, print_lambda);
    //
    return out;
}

template <class T>
bool search_prefix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    //
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the prefix_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.
    auto search_lambda = [&found, &count, &it](const T &item) -> bool
    {
        count++;
        if (item == it)
        {
            found = true;
            return false;
        }
        return true;
    };

    prefix_process(tree, search_lambda);
    //
    return found;
}

template <class T>
bool search_infix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    //
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the infix_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.
    auto search_lambda = [&found, &count, &it](const T &item) -> bool
    {
        count++;
        if (item == it)
        {
            found = true;
            return false;
        }
        return true;
    };

    infix_process(tree, search_lambda);
    //
    return found;
}

template <class T>
bool search_postfix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    //
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the postfix_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.
    auto search_lambda = [&found, &count, &it](const T &item) -> bool
    {
        count++;
        if (item == it)
        {
            found = true;
            return false;
        }
        return true;
    };

    postfix_process(tree, search_lambda);
    //
    return found;
}

template <class T>
bool search_breadth_first(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    //
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the breadth_first_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.
    auto search_lambda = [&found, &count, &it](const T &item) -> bool
    {
        count++;
        if (item == it)
        {
            found = true;
            return false;
        }
        return true;
    };

    breadth_first_process(tree, search_lambda);
    //
    return found;
}

template <class T>
bool check_btree_in_order(const BTree<T> &tree)
{
    bool ret_val = true;
    //
    // Hint: You can create a lambda function with a parameter to compare it with
    //  the last the value seen.
    //  Use the lambda with the infix_process.
    T last_value;
    bool first = true;

    auto check_lambda = [&ret_val, &last_value, &first](const T &item) -> bool
    {
        if (first)
        {
            first = false;
        }
        else if (item <= last_value)
        {
            ret_val = false;
            return false;
        }
        last_value = item;
        return true;
    };

    infix_process(tree, check_lambda);
    //
    return ret_val;
}

template <class T>
bool has_in_order(const BTree<T> &tree, T const &v)
{
    assert(check_btree_in_order<T>(tree));
    bool ret_val = false;
    //
    if (!tree.is_empty())
    {
        if (v < tree.item())
        {
            ret_val = has_in_order(tree.left(), v);
        }
        else if (v > tree.item())
        {
            ret_val = has_in_order(tree.right(), v);
        }
        else
        {
            ret_val = true;
        }
    }
    //
    return ret_val;
}

template <class T>
void insert_in_order(BTree<T> &&tree, T const &v)
{
    assert(check_btree_in_order<T>(tree));
    //
    if (tree.is_empty())
    {
        tree = BTree<T>(v);
    }
    else if (v < tree.item())
    {
        BTree<T> left = tree.left();
        insert_in_order(std::move(left), v);
        tree.set_left(std::move(left));
    }
    else if (v > tree.item())
    {
        BTree<T> right = tree.right();
        insert_in_order(std::move(right), v);
        tree.set_right(std::move(right));
    }
    //
    assert(has_in_order<T>(tree, v));
}

template <class T>
void insert_in_order(BTree<T> &tree, T const &v)
{
    insert_in_order(std::move(tree), v);
}