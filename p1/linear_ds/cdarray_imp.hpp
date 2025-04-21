/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <sstream>
#include <cassert>
#include <cdarray.hpp>

template <class T>
size_t
CDArray<T>::capacity() const
{
    //
    return capacity_;
    //
}

template <class T>
size_t
CDArray<T>::size() const
{
    //
    return size_;
    //
}

template <class T>
bool CDArray<T>::is_empty() const
{
    //
    if (size_ == 0)
    {
        return true;
    }
    return false;
    //
}

template <class T>
bool CDArray<T>::is_full() const
{
    bool ret_v = false;
    //
    if (size_ == capacity_)
    {
        ret_v = true;
    }
    //
    assert(!ret_v || size() == capacity());
    return ret_v;
}

template <class T>
CDArray<T>::CDArray(size_t cap)
{
    assert(cap > 0);
    //
    v_ = std::shared_ptr<T[]>(new T[cap]);
    capacity_ = cap;
    size_ = 0;
    front_ = 0;
    back_ = 0;
    //
    assert(capacity() == cap);
    assert(is_empty());
    assert(size() == 0);
}

template <class T>
CDArray<T>::~CDArray()
{
    //
    // Remember: depending on your representation, it is possible that nothing
    // must be done.
    //
}

template <class T>
CDArray<T>::CDArray(std::istream &in) noexcept(false) : CDArray(1)
{
    std::string token;
    in >> token;

    // Hint: use std::istringstream to convert from "string" to template
    //  parameter T type.
    // Remember: throw std::runtime_error("Wrong input format.") exception when an input
    //  format error was found.
    if (token != "[")
    {
        throw std::runtime_error("Wrong input format.");
    }

    while ((in >> token) && (token != "]"))
    {
        T valor;
        std::istringstream num(token);
        num >> valor;
        push_back(valor);
    }

    if (token != "]")
    {
        throw std::runtime_error("Wrong input format.");
    }
    //
}

template <class T>
std::ostream &
CDArray<T>::fold(std::ostream &out) const
{
    //
    out << "[";
    for (int i = 0; i < size_; i++)
    {
        out << " ";
        out << v_[(front_ + i) % capacity_];
    }
    out << " ";
    out << "]";
    //
    return out;
}

template <class T>
T const &CDArray<T>::get(size_t pos) const
{
    //
    return v_[pos];
    //
}

template <class T>
void CDArray<T>::set(size_t pos, T const &new_v)
{
    //
    v_[pos] = new_v;
    //
    assert(new_v == get(pos));
}

size_t cInc(size_t v, size_t size)
{
    size_t ret_v;
    //
    ret_v = (v + 1) % size;
    //
    return ret_v;
}

size_t cDec(size_t v, size_t size)
{
#ifndef NDEBUG
    size_t old_v = v;
#endif
    size_t ret_v;
    //
    // Remember: v is a unsigned value, so you must cast to signed before decrementing
    ret_v = ((int)v - 1) % size;
    //
    assert(old_v == cInc(ret_v, size));
    return ret_v;
}

template <class T>
void CDArray<T>::push_front(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
    bool old_is_empty = is_empty();
    T old_front = is_empty() ? T() : get(0);
#endif
    //
    if (is_full())
    {
        grow();
    }
    for (size_t i = size_; i > 0; --i)
    {
        v_[i] = v_[i - 1];
    }
    v_[0] = new_it;
    size_++;
    //
    assert(size() == old_size + 1);
    assert(get(0) == new_it);
    assert(old_is_empty || (get(1) == old_front));
}

template <class T>
void CDArray<T>::push_back(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
    bool old_is_empty = is_empty();
    T old_back = is_empty() ? T() : get(size() - 1);
#endif
    //
    if (is_full())
    {
        grow();
    }
    back_ = cInc(back_, capacity_);
    v_[back_] = new_it;
    size_++;
    //
    assert(size() == old_size + 1);
    assert(get(size() - 1) == new_it);
    assert(old_is_empty || (get(size() - 2) == old_back));
}

template <class T>
void CDArray<T>::pop_front()
{
#ifndef NDEBUG
    size_t old_size = size();
    T old_next_front = size() > 1 ? get(1) : T();
#endif
    //
    for (size_t i = 0; i <= size(); i++)
    {
        v_[i] = v_[i + 1];
    }
    size_--;
    back_ = cDec(back_, capacity());
    //
    assert(size() == old_size - 1);
    assert(is_empty() || get(0) == old_next_front);
}

template <class T>
void CDArray<T>::pop_back()
{
#ifndef NDEBUG
    size_t old_size = size();
    T old_prev_back = size() > 1 ? get(size() - 2) : T();
#endif
    //
    back_ = cDec(back_, capacity());
    size_--;
    //
    assert(size() == old_size - 1);
    assert(is_empty() || get(size() - 1) == old_prev_back);
}

template <class T>
void CDArray<T>::insert(size_t pos, T const &v)
{
    assert(pos >= 0 && pos < size());
#ifndef NDEBUG
    size_t old_size = size();
    T old_back = get(size() - 1);
    T old_pos_v = get(pos);
#endif
    //
    // Hint: if pos==0, delegate in push_front.
    // Remember: back_ needs to be updated too.
    if (pos == 0)
        push_front(v);
    else
    {
        if (is_full())
            grow();
        for (size_t i = size_ - 1; i >= pos; i--)
        {
            set(i + 1, get(i));
        }
        size_++;
        set(pos, v);
        back_ = size_ - 1;
    }
    //
    assert(size() == old_size + 1);
    assert(get(pos) == v);
    assert(get(pos + 1) == old_pos_v);
    assert(get(size() - 1) == old_back);
}

template <class T>
void CDArray<T>::remove(size_t pos)
{
    assert(pos >= 0 && pos < size());
#ifndef NDEBUG
    size_t old_size = size();
    T old_next_pos_v = (pos <= (size() - 2)) ? get(pos + 1) : T();
#endif
    //
    // Remember: back_ needs to be updated.
    for (size_t i = pos; i <= size_ - 2; i++)
    {
        set(i, get(i + 1));
    }
    size_--;
    back_ = size_ - 1;
    // front_
    assert(size() == old_size - 1);
    assert(pos == size() || get(pos) == old_next_pos_v);
}

template <class T>
void CDArray<T>::grow()
{
#ifndef NDEBUG
    size_t old_capacity = capacity();
    T old_front = get(0);
    T old_back = get(size() - 1);
#endif
    //
    std::shared_ptr<T[]> tmp(new T[capacity() * 2]);
    for (size_t i = 0; i < size_; ++i)
    {
        tmp[i] = get(i);
    }
    v_ = tmp;
    capacity_ *= 2;
    front_ = 0;
    back_ = size_ - 1;
    //
    assert(capacity() == 2 * old_capacity);
    assert(get(0) == old_front);
    assert(get(size() - 1) == old_back);
}