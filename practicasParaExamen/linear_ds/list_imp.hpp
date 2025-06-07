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
#include <stdexcept>
#include <cassert>

#include <list.hpp>

template <class T>
List<T>::List()
{
    // TODO
    // Remember: in an empty list, the dummy node is linked with itself.

    //
    assert(is_empty());
}

template <class T>
List<T>::List(std::istream &in) noexcept(false) : List()
{

    // TODO
    // Hint: use std::istringstream to convert from a "string" token value to a template
    // T type value.
    // Remember: throw std::runtime_error("Wrong input format.") exception when an input
    //  format error was found.

    //
}

template <class T>
List<T>::~List()
{
    // Think. We are using smart pointers (shared_ptr) so the nodes will
    // released automatically when the references going off.
}

template <class T>
typename DNode<T>::Ref List<T>::dummy() const
{
    // TODO: recode with respect to your representation.
    return nullptr;
    //
}

template <class T>
bool List<T>::is_empty() const
{
    // TODO: recode with respect to your representation.
    return false;
    //
}

template <class T>
size_t List<T>::size() const
{
    // TODO: recode with respect to your representation.
    return 0;
    //
}

template <class T>
void List<T>::set_size(size_t new_size)
{
    // TODO

    //
    assert(size() == new_size);
}

template <class T>
typename List<T>::iterator List<T>::begin() const
{

    // TODO: recode with respect to your representation.
    return ListIterator<T>();
    //
}

template <class T>
typename List<T>::iterator List<T>::end() const
{
    // TODO: recode with respect to your representation.

    return ListIterator<T>();
    //
}

template <class T>
T const &List<T>::front() const
{
    assert(!is_empty());

    // TODO: recode with respect to your representation.
    // Hint: use iterators.
    T fixme{};
    return fixme;
    //
}

template <class T>
T const &List<T>::back() const
{
    assert(!is_empty());

    // TODO: recode with respect to your representation.
    // Hint: use iterators.
    T fixme{};
    return fixme;
    //
}

template <class T>
void List<T>::fold(std::ostream &out) const
{
    // TODO

    //
}

template <class T>
void List<T>::hook(typename DNode<T>::Ref n, typename DNode<T>::Ref pos)
{
#ifndef NDEBUG
    auto old_size = size();
#endif
    // TODO
    // Remember updating the size.

    //
    assert(size() == old_size + 1);
}

template <class T>
void List<T>::unhook(typename DNode<T>::Ref pos)
{
#ifndef NDEBUG
    auto old_size = size();
#endif
    // TODO
    // Remember updating the size.

    //
    assert(size() == old_size - 1);
}

template <class T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator const &pos,
                                           T const &it)
{
#ifndef NDEBUG
    auto old_is_empty = is_empty();
    auto old_size = size();
    auto old_pos_prev = pos.prev();
#endif
    iterator ret_v;
    // TODO
    // Hint: delegate in hook.

    //
    assert(!old_is_empty || (front() == it && back() == it));
    assert(old_is_empty || ret_v.next() == pos);
    assert(old_is_empty || old_pos_prev == ret_v.prev());
    assert(size() == (old_size + 1));
    return ret_v;
}

template <class T>
typename List<T>::iterator List<T>::remove(List<T>::iterator const &pos)
{
    assert(!is_empty());
#ifndef NDEBUG
    auto old_size = size();
    auto old_pos_next = pos.next();
    auto old_pos_prev = pos.prev();
#endif
    iterator ret_v;
    // TODO
    // Hint: delegate in unkook

    //
    assert(ret_v == old_pos_next);
    assert(ret_v.prev() == old_pos_prev);
    assert(size() == (old_size - 1));
    return ret_v;
}

template <class T>
void List<T>::push_front(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    //  Hint: delegate in insert();

    //
    assert(front() == new_it);
    assert(size() == (old_size + 1));
}

template <class T>
void List<T>::push_back(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    //  Hint: delegate in insert();

    //
    assert(back() == new_it);
    assert(size() == (old_size + 1));
}

template <class T>
void List<T>::pop_front()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    // Hint: delegate in remove.

    //
    assert(size() == (old_size - 1));
}

template <class T>
void List<T>::pop_back()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    auto old_end_prev_prev = end().prev().prev();
#endif
    // TODO
    // Hint: delegate in remove.

    //
    assert(is_empty() || end().prev() == old_end_prev_prev);
    assert(size() == (old_size - 1));
}

template <class T>
typename List<T>::iterator List<T>::find(T const &it, List<T>::iterator const &from) const
{
    iterator ret_v;
    // TODO

    //
    assert(ret_v == end() || ret_v.item() == it);
    return ret_v;
}

template <class T>
void List<T>::splice(iterator const &pos, List<T> &list2,
                     iterator const &first, iterator const &last)
{
#ifndef NDEBUG
    size_t old_size = size();
    size_t old_l2_size = list2.size();
    auto old_range_size = first.distance(last);
#endif
    // TODO
    // Hint: if the range [first, last) is empty, nothing must be done.

    //
    assert(size() == (old_size + old_range_size));
    assert(list2.size() == (old_l2_size - old_range_size));
}

template <class T>
void List<T>::splice(iterator const &pos, List<T> &list2)
{
#ifndef NDEBUG
    size_t old_size = size();
    auto old_list2_size = list2.size();
#endif
    // TODO
    // Hint: Delegate in splice the list2 range [begin, end).

    //
    assert(size() == (old_size + old_list2_size));
    assert(list2.size() == 0);
    assert(list2.is_empty());
}

template <class T>
void List<T>::splice(iterator const &pos, List<T> &list2, iterator const &i)
{
#ifndef NDEBUG
    size_t old_size = size();
    auto old_list2_size = list2.size();
#endif
    // TODO
    // Hint: Delegate in splice the list2 range [i, i.next()).

    //
    assert(size() == (old_size + 1));
    assert(list2.size() == (old_list2_size - 1));
}

template <class T>
template <class Compare>
void List<T>::merge(List<T> &other, Compare comp)
{
    // TODO
    // Remember: The nodes of the other list are spliced into this list.

    //
}

template <class T>
template <class Compare>
void List<T>::sort(Compare comp)
{
    // TODO
    // Remember: we want a complexity in to N Log(N) so mergeSort algorithm is
    // a good candidate to sort the list.
    // Hint: Do a recursive implementation, splitting the list into two halves,
    // sorting recursively each part and merging the sorted lists to obtain
    // the full sorted list.

    // The empty list and a list with only one element are sorted by default.

    //
}
