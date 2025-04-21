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
    //
    // Remember: in an empty list, the dummy node is linked with itself.
    dummy_ = DNode<T>::create();
    dummy_->set_next(dummy_);
    dummy_->set_prev(dummy_);
    size_ = 0;
    //
    assert(is_empty());
}

template <class T>
List<T>::List(std::istream &in) noexcept(false) : List()
{

    //
    // Hint: use std::istringstream to convert from a "string" token value to a template
    // T type value.
    // Remember: throw std::runtime_error("Wrong input format.") exception when an input
    //  format error was found.
    std::string token;
    in >> token;
    if (token != "[")
    {
        throw std::runtime_error("Wrong input format.");
    }

    while ((in >> token) && (token != "]"))
    {
        {
            T valor;
            std::istringstream it(token);
            if (!(it >> valor))
            {
                throw std::runtime_error("Wrong input format.");
            }
            push_back(valor);
        }
    }

    if (token != "]")
    {
        throw std::runtime_error("Wrong input format.");
    }
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
    //
    return dummy_;
    //
}

template <class T>
bool List<T>::is_empty() const
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
size_t List<T>::size() const
{
    //
    return size_;
    //
}

template <class T>
void List<T>::set_size(size_t new_size)
{
    //
    size_ = new_size;
    //
    assert(size() == new_size);
}

template <class T>
typename List<T>::iterator List<T>::begin() const
{

    //
    return ListIterator<T>(dummy_->next());
    //
}

template <class T>
typename List<T>::iterator List<T>::end() const
{
    //
    return ListIterator<T>(dummy_);
    //
}

template <class T>
T const &List<T>::front() const
{
    assert(!is_empty());

    //
    // Hint: use iterators.
    return begin().item();
    //
}

template <class T>
T const &List<T>::back() const
{
    assert(!is_empty());

    //
    // Hint: use iterators.
    return end().prev().item();
    //
}

template <class T>
void List<T>::fold(std::ostream &out) const
{
    //
    out << "[";
    ListIterator<T> aux = begin();
    for (int i = 0; i < size_; i++)
    {
        out << " ";
        out << aux.item();
        aux = aux.next();
    }
    out << " ";
    out << "]";
    //
}

template <class T>
void List<T>::hook(typename DNode<T>::Ref n, typename DNode<T>::Ref pos)
{
#ifndef NDEBUG
    auto old_size = size();
#endif
    //
    // Remember updating the size.
    size_++;
    typename DNode<T>::Ref aux;
    aux = pos->prev();
    aux->set_next(n);
    n->set_prev(aux);
    n->set_next(pos);
    pos->set_prev(n);
    //
    assert(size() == old_size + 1);
}

template <class T>
void List<T>::unhook(typename DNode<T>::Ref pos)
{
#ifndef NDEBUG
    auto old_size = size();
#endif
    //
    // Remember updating the size.
    size_--;
    typename DNode<T>::Ref aux;
    aux = pos->prev();
    pos = pos->next();
    aux->set_next(pos);
    pos->set_prev(aux);
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
    //
    // Hint: delegate in hook.
    typename DNode<T>::Ref aux = DNode<T>::create();
    aux->set_item(it);
    hook(aux, pos.node());
    ret_v = aux;
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
    //
    // Hint: delegate in unkook
    ret_v = pos.next();
    unhook(pos.node());
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
    //
    //  Hint: delegate in insert();
    insert(begin(), new_it);
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
    //
    //  Hint: delegate in insert();
    insert(dummy_, new_it);
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
    //
    // Hint: delegate in remove.
    remove(begin());
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
    //
    // Hint: delegate in remove.
    remove(end().prev());
    //
    assert(is_empty() || end().prev() == old_end_prev_prev);
    assert(size() == (old_size - 1));
}

template <class T>
typename List<T>::iterator List<T>::find(T const &it, List<T>::iterator const &from) const
{
    iterator ret_v;
    //
    ret_v = from;
    while ((ret_v != end()) && (ret_v.item() != it))
    {
        ret_v = ret_v.next();
    }
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
    //
    // Hint: if the range [first, last) is empty, nothing must be done.
    if (first != last)
    {
        auto rangeSize = first.distance(last);
        auto posNode = pos.node();
        auto prevPosNode = posNode->prev();
        auto firstNode = first.node();
        auto prevFirstNode = firstNode->prev();
        auto lastNode = last.node();
        auto prevLastNode = lastNode->prev();

        prevPosNode->set_next(firstNode);
        firstNode->set_prev(prevPosNode);
        posNode->set_prev(prevLastNode);
        prevLastNode->set_next(posNode);

        prevFirstNode->set_next(lastNode);
        lastNode->set_prev(prevFirstNode);

        size_ += rangeSize;
        list2.size_ -= rangeSize;
    }
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
    //
    // Hint: Delegate in splice the list2 range [begin, end).
    splice(pos, list2, list2.begin(), list2.end());
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
    //
    // Hint: Delegate in splice the list2 range [i, i.next()).
    splice(pos, list2, i, i.next());
    //
    assert(size() == (old_size + 1));
    assert(list2.size() == (old_list2_size - 1));
}

template <class T>
template <class Compare>
void List<T>::merge(List<T> &other, Compare comp)
{
    //
    // Remember: The nodes of the other list are spliced into this list.
    auto it1 = begin();
    auto it2 = other.begin();

    while (it1 != end() && it2 != other.end())
    {
        if (comp(it2.item(), it1.item()))
        {
            auto next = it2.next();
            splice(it1, other, it2);
            it2 = next;
        }
        else
        {
            it1 = it1.next();
        }
    }

    if (it2 != other.end())
    {
        splice(end(), other, it2, other.end());
    }
}

template <class T>
template <class Compare>
void List<T>::sort(Compare comp)
{
    //
    // Remember: we want a complexity in to N Log(N) so mergeSort algorithm is
    // a good candidate to sort the list.
    // Hint: Do a recursive implementation, splitting the list into two halves,
    // sorting recursively each part and merging the sorted lists to obtain
    // the full sorted list.
    // The empty list and a list with only one element are sorted by default.
    if (size() > 1)
    {
        List<T> tmp;
        auto midpoint = begin();
        midpoint.goto_next(size() / 2);
        tmp.splice(tmp.begin(), *this, midpoint, end());
        sort(comp);
        tmp.sort(comp);
        merge(tmp, comp);
    }
    //
}
