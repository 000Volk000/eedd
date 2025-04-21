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
#include <list_iterator.hpp>

template <class T>
ListIterator<T>::~ListIterator() {}

template <class T>
bool ListIterator<T>::is_valid() const
{
    bool ret_v = false;
    //
    // Hint: Do not invoke node() here because that provoques an infinite recursion.
    if (node_ != nullptr)
    {
        ret_v = true;
    }
    //
    return ret_v;
}

template <class T>
ListIterator<T>::ListIterator()
{
    //
    node_ = nullptr;
    //
    assert(!is_valid());
};

template <class T>
ListIterator<T>::ListIterator(typename DNode<T>::Ref const &n)
{
    //
    node_ = n;
    //
    assert(n == nullptr || is_valid());
    assert(n != nullptr || !is_valid());
};

template <class T>
T const &ListIterator<T>::item() const
{
    assert(is_valid());
    //
    return node_->item();
    //
}

template <class T>
ListIterator<T> ListIterator<T>::next(size_t dist) const
{
    assert(is_valid());
    ListIterator<T> ret_v;
    //
    ret_v = *this;
    ret_v.goto_next(dist);
    //
    return ret_v;
}

template <class T>
ListIterator<T> ListIterator<T>::prev(size_t dist) const
{
    assert(is_valid());
    ListIterator<T> ret_v;
    //
    ret_v = *this;
    ret_v.goto_prev(dist);
    //
    return ret_v;
}

template <class T>
size_t ListIterator<T>::distance(ListIterator<T> const &other) const
{
    assert(is_valid());
    assert(other.is_valid());
    size_t ret_v = 0;
    //
    auto aux = *this;
    while (aux != other)
    {
        ret_v++;
        aux.goto_next();
    }
    //
    return ret_v;
}

template <class T>
bool ListIterator<T>::operator==(ListIterator<T> const &o) const
{
    //
    // Remember: two iterators are equal if both point to the same node.
    return node_ == o.node();
    //
}

template <class T>
bool ListIterator<T>::operator!=(ListIterator<T> const &o) const
{
    //
    // Remember: two iterators are equal if both point to the same node.
    return node_ != o.node();
    //
}

template <class T>
void ListIterator<T>::set_item(T const &it)
{
    assert(is_valid());
    //
    node_->set_item(it);
    //
}

template <class T>
void ListIterator<T>::goto_next(size_t dist)
{
    assert(is_valid());
    //
    for (size_t i = 0; i < dist; i++)
    {
        node_ = node_->next();
    }
    //
}

template <class T>
void ListIterator<T>::goto_prev(size_t dist)
{
    assert(is_valid());
    //
    for (size_t i = 0; i < dist; i++)
    {
        node_ = node_->prev();
    }
    //
}

template <class T>
typename DNode<T>::Ref ListIterator<T>::node() const
{
    typename DNode<T>::Ref ret_v;
    //
    return node_;
    //
}

template <class T>
void ListIterator<T>::set_node(typename DNode<T>::Ref const &n)
{
    //
    node_ = n;
    //
    assert(node() == n);
}