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
#include <queue.hpp>

template <class T>
Queue<T>::Queue()
{
    // TODO

    //
    assert(is_empty());
}

template <class T>
bool Queue<T>::is_empty() const
{
    // TODO: recode with respect to your representation.
    return false;
    //
}

template <class T>
size_t
Queue<T>::size() const
{
    // TODO: recode with respect to your representation.
    return 0;
    //
}

template <class T>
T const &Queue<T>::front() const
{
    assert(!is_empty());

    // TODO: recode with respect to your representation.
    T fixme{};
    return fixme;
    //
}

template <class T>
T const &Queue<T>::back() const
{
    assert(!is_empty());

    // TODO: recode with respect to your representation.
    T fixme{};
    return fixme;
    //
}

template <class T>
void Queue<T>::enque(const T &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO

    //
    assert(back() == new_it);
    assert(size() == (old_size + 1));
}

template <class T>
void Queue<T>::deque()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO

    //
    assert(size() == (old_size - 1));
}
