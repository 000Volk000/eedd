/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once
#include <exception>
#include <cassert>
#include <algorithm>
#include <heap.hpp>

/**
 * @brief Compute the parent's index of a given child.
 *
 * @param i is the index of the child in the heap.
 * @return size_t
 */
inline size_t parent(size_t i)
{
    assert(i > 0);
    //
    return (i - 1) / 2;
    //
}

/**
 * @brief Compute the left child's index of a given parent.
 *
 * @param i is the index of the parent in the heap.
 * @return the index of the left child.
 */
inline size_t left(size_t i)
{
    //
    return (i * 2) + 1;
    //
}

/**
 * @brief Compute the right child's index of a given parent.
 *
 * @param i is the index of the parent in the heap.
 * @return the index of the right child.
 */
inline size_t right(size_t i)
{
    //
    return (i * 2) + 2;
    //
}

template <class T>
void Heap<T>::shift_up(size_t i)
{
    //
    if (i > 0 && comp_((*values_)[i], (*values_)[parent(i)]))
    {
        std::swap(values_[i], values_[parent(i)]);
        shift_up(parent(i));
    }
    //
}

template <class T>
void Heap<T>::shift_down(size_t i)
{
    //
    size_t n = i;
    size_t lC = left(i);
    size_t rC = right(i);

    if (lC < last_item_ && comp_((*values_)[lC], (*values_)[n]))
    {
        n = lC;
    }

    if (rC < last_item_ && comp_((*values_)[rC], (*values_)[n]))
    {
        n = rC;
    }

    if (i != n)
    {
        std::swap(values_[i], values_[n]);
        shift_down(n);
    }
    //
}

template <class T>
bool Heap<T>::is_a_heap(size_t root) const
{
    bool ret_val = true;
    //
    // Remember: the tree is a heap if both children are heaps and the root is
    // comp(parent, child) if true for both children.
    // Remember: a leaf is a heap.
    size_t l = left(root);
    size_t r = right(root);
    if (!(l > last_item_ && r > last_item_))
    {
        if (!is_a_heap(l))
        {
            ret_val = false;
        }
        else if (r < last_item_ && !is_a_heap(r))
        {
            ret_val = false;
        }
        else if (!(comp_(root, l) && comp_(root, r)))
        {
            ret_val = false;
        }
    }
    //
    return ret_val;
}

template <class T>
void Heap<T>::heapify()
{
    //
    // Remember: we want O(N) here.
    if (size() > 0)
    { // FIXME Puede ser que i sea >=
        for (int i = (size() / 2) - 1; i > 0; i--)
        {
            shift_down(i);
        }
    }
    //
    assert(is_a_heap());
}

template <class T>
Heap<T>::Heap(std::vector<T> &values, Comp const &comp) : values_(&values), comp_(comp)
{
    //
    // Hint: use the heapify function
    last_item_ = (*values_).size();
    heapify();
    //
    assert(is_a_heap());
    assert(size() == values.size());
}

template <class T>
Heap<T>::~Heap()
{
}

template <class T>
bool Heap<T>::is_empty() const
{
    //
    if (last_item_ == 0)
    {
        return true;
    }
    return false;
    //
}

template <class T>
size_t Heap<T>::size() const
{
    //
    return last_item_;
    //
}

template <class T>
T const &Heap<T>::item() const
{
    assert(!is_empty());
    //
    return (*values_)[0];
    //
}

template <class T>
void Heap<T>::insert(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    //
    // Remember: we are using a dynamic array, so we need to check if the array
    // is full to push_back the new value if it is needed.
    if (last_item_ == (*values_).size())
    {
        (*values_).push_back(new_it);
    }
    else
    {
        (*values_)[last_item_] = new_it;
    }

    shift_up(last_item_);
    last_item_++;
    //
    assert(is_a_heap());
    assert(size() == old_size + 1);
}

template <class T>
void Heap<T>::remove()
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    assert(!is_empty());
    //
    last_item_--;
    if (last_item_ > 0)
    {
        std::swap((*values_)[0], (*values_)[last_item_]);
        shift_down(0);
    }
    //
    assert(is_a_heap());
    assert(size() == old_size - 1);
}

template <class T>
void heapsort(std::vector<T> &values, std::function<bool(T const &a, T const &b)> const &comp)
{
    // TODO
    // Remember: we want O(N log N) here.

    //
#ifndef NDEBUG
    for (size_t i = 1; i < values.size(); ++i)
        assert(comp(values[i], values[i - 1]));
#endif
}