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
    // TODO: recode with respect to your representation.
    // Hint: Do not invoke node() here because that provoques an infinite recursion.
    return false;
    //
}

template <class T>
ListIterator<T>::ListIterator()
{
    // TODO

    //
    assert(!is_valid());
};

template <class T>
ListIterator<T>::ListIterator(typename DNode<T>::Ref const &n)
{
    // TODO

    //
    assert(n == nullptr || is_valid());
    assert(n != nullptr || !is_valid());
};

template <class T>
T const &ListIterator<T>::item() const
{
    assert(is_valid());
    // TODO: recode with respect to your representation.
    T fixme{};
    return fixme;
    //
}

template <class T>
ListIterator<T> ListIterator<T>::next(size_t dist) const
{
    assert(is_valid());
    ListIterator<T> ret_v;
    // TODO

    //
    return ret_v;
}

template <class T>
ListIterator<T> ListIterator<T>::prev(size_t dist) const
{
    assert(is_valid());
    ListIterator<T> ret_v;
    // TODO

    //
    return ret_v;
}

template <class T>
size_t ListIterator<T>::distance(ListIterator<T> const &other) const
{
    assert(is_valid());
    assert(other.is_valid());
    size_t ret_v = 0;
    // TODO

    //
    return ret_v;
}

template <class T>
bool ListIterator<T>::operator==(ListIterator<T> const &o) const
{
    // TODO: recode with respect to your representation.
    // Remember: two iterators are equal if both point to the same node.
    return false;
    //
}

template <class T>
bool ListIterator<T>::operator!=(ListIterator<T> const &o) const
{
    bool ret_v = false;

    // TODO: recode with respect to your representation.
    // Remember: two iterators are equal if both point to the same node.
    return false;
    //
}

template <class T>
void ListIterator<T>::set_item(T const &it)
{
    assert(is_valid());
    // TODO

    //
}

template <class T>
void ListIterator<T>::goto_next(size_t dist)
{
    assert(is_valid());
    // TODO

    //
}

template <class T>
void ListIterator<T>::goto_prev(size_t dist)
{
    assert(is_valid());
    // TODO

    //
}

template <class T>
typename DNode<T>::Ref ListIterator<T>::node() const
{
    typename DNode<T>::Ref ret_v;
    // TODO: recode with respect to your representation.
    return nullptr;
    //
}

template <class T>
void ListIterator<T>::set_node(typename DNode<T>::Ref const &n)
{
    // TODO

    //
    assert(node() == n);
}