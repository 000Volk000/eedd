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
#include <list_node.hpp>

template <class T>
bool DNode<T>::is_dummy() const
{
    // TODO: recode with respect to your representation.
    return false;
    //
}

template <class T>
DNode<T>::DNode()
{
    // TODO

    //
    assert(is_dummy());
}

template <class T>
DNode<T>::DNode(T const &it)
{
    // TODO

    //
    assert(!is_dummy());
    assert(next() == nullptr);
    assert(prev() == nullptr);
}

template <class T>
DNode<T>::DNode(T const &it, Ref next_n)
{
    // TODO

    //
    assert(!is_dummy());
    assert(next() == next_n);
    assert(prev() == nullptr);
}

template <class T>
DNode<T>::DNode(T const &it, Ref next_n, Ref prev_n)
{
    // TODO

    //
    assert(!is_dummy());
    assert(next() == next_n);
    assert(prev() == prev_n);
}

template <class T>
typename DNode<T>::Ref DNode<T>::create()
{
    auto ret_v = std::shared_ptr<DNode<T>>(new DNode<T>());
    ret_v->This_ = ret_v;
    assert(ret_v == ret_v->This());
    return ret_v;
}

template <class T>
typename DNode<T>::Ref DNode<T>::create(T const &it)
{
    auto ret_v = std::shared_ptr<DNode<T>>(new DNode<T>(it));
    ret_v->This_ = ret_v;
    assert(ret_v == ret_v->This());
    return ret_v;
}

template <class T>
typename DNode<T>::Ref DNode<T>::create(T const &it, Ref const &next_n)
{
    auto ret_v = std::shared_ptr<DNode<T>>(new DNode<T>(it, next_n));
    ret_v->This_ = ret_v;
    assert(ret_v == ret_v->This());
    return ret_v;
}

template <class T>
typename DNode<T>::Ref DNode<T>::create(T const &it, Ref const &next_n, Ref const &prev_n)
{
    auto ret_v = std::shared_ptr<DNode<T>>(new DNode<T>(it, next_n, prev_n));
    ret_v->This_ = ret_v;
    assert(ret_v == ret_v->This());
    return ret_v;
}

template <class T>
typename DNode<T>::Ref DNode<T>::This()
{
    return This_;
}

template <class T>
DNode<T>::~DNode()
{
    // TODO
    // Hint: if std::shared_ptr is used for the references,
    //   there is nothing todo.

    //
}

template <class T>
T const &DNode<T>::item() const
{
    assert(!is_dummy());

    // TODO: recode with respect to your representation.
    T fixme{};
    return fixme;
    //
}

template <class T>
typename DNode<T>::Ref DNode<T>::prev() const
{
    // TODO: recode with respect to your representation.
    return nullptr;
    //
}

template <class T>
typename DNode<T>::Ref DNode<T>::next() const
{
    // TODO: recode with respect to your representation.
    return nullptr;
    //
}

template <class T>
void DNode<T>::set_item(const T &new_it)
{
    // TODO

    //
}

template <class T>
void DNode<T>::set_prev(DNode<T>::Ref n)
{
    // TODO

    //
    assert(n == prev());
}

template <class T>
void DNode<T>::set_next(DNode<T>::Ref n)
{
    // TODO

    //
    assert(n == next());
}
