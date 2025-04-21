/**
 * @file avltree_iterator_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <avltree_iterator.hpp>

template <class T>
const typename AVLTNode<T>::Ref &AVLTreeIterator<T>::node() const
{
    //
    return node_;
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTreeIterator<T>::node()
{
    //
    return node_;
    //
}

template <class T>
AVLTreeIterator<T>::AVLTreeIterator()
{
    //
    node_ = nullptr;
    //
    assert(node() == nullptr);
}

template <class T>
AVLTreeIterator<T>::AVLTreeIterator(typename AVLTNode<T>::Ref const &node)
{
    //
    node_ = node;
    //
    assert(this->node() == node);
}

template <class T>
bool AVLTreeIterator<T>::operator==(AVLTreeIterator<T> const &other) const
{
    bool equal = false;
    // TODO

    //
    return equal;
}

template <class T>
bool AVLTreeIterator<T>::operator!=(AVLTreeIterator<T> const &other) const
{
    bool different = false;
    // TODO

    //
    return different;
}

template <class T>
T const &AVLTreeIterator<T>::operator*() const
{
    assert(node());
    return node()->item();
}

template <class T>
const T *AVLTreeIterator<T>::operator->() const
{
    assert(node());
    return &node()->item();
}

template <class T>
AVLTreeIterator<T> &AVLTreeIterator<T>::operator++()
{
    assert(node());
    // TODO

    //
    return *this;
}

template <class T>
AVLTreeIterator<T> AVLTreeIterator<T>::operator++(int)
{
    AVLTreeIterator<T> old = *this;
    ++(*this);
    return old;
}

template <class T>
AVLTreeIterator<T> &AVLTreeIterator<T>::operator--()
{
    assert(node());
    // TODO

    //
    return *this;
}

template <class T>
AVLTreeIterator<T> AVLTreeIterator<T>::operator--(int)
{
    AVLTreeIterator<T> old = *this;
    --(*this);
    return old;
}
