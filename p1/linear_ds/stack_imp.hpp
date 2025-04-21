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
#include <stack.hpp>

template <class T>
Stack<T>::Stack()
{
    //
    //
    assert(is_empty());
}

template <class T>
bool Stack<T>::is_empty() const
{
    //
    return l_.is_empty();
    //
}

template <class T>
size_t Stack<T>::size() const
{
    //
    return l_.size();
    //
}

template <class T>
T const &Stack<T>::top() const
{
    assert(!is_empty());

    //
    return l_.begin().item();
    //
}

template <class T>
void Stack<T>::push(const T &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    //
    l_.push_front(new_it);
    //
    assert(top() == new_it);
    assert(size() == (old_size + 1));
}

template <class T>
void Stack<T>::pop()
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    assert(!is_empty());
    //
    l_.pop_front();
    //
    assert(size() == (old_size - 1));
}
