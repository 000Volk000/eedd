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
#include <exception>
#include <memory>
#include <iostream>
#include <sstream>

#include "btree.hpp"

template <class T>
bool BTree<T>::is_empty() const
{
    bool ret_v = false;
    //
    if (_root == nullptr)
    {
        ret_v = true;
    }
    //
    return ret_v;
}

template <class T>
BTree<T>::BTree()
{
    //
    _root = nullptr;
    //
    assert(is_empty());
}

template <class T>
BTree<T>::BTree(const T &it)
{
    //
    create_root(it);
    //
    assert(!is_empty());
    assert(item() == it);
    assert(left().is_empty());
    assert(right().is_empty());
}

template <class T>
BTree<T>::BTree(std::istream &in) noexcept(false)
    : BTree<T>()
{
    //
    // Remember: throw std:runtime_error exception with text
    //"Wrong input format." when an input format error is found.
    std::string token;
    in >> token;
    T valor;
    if (token == "[]")
    {
        _root = nullptr;
        _root = nullptr;
        _root = nullptr;
    }
    else if (token == "[")
    {
        if (!(in >> valor))
        {
            throw std::runtime_error("Wrong input format.");
        }
        create_root(valor);
        _root->set_left(BTree(in).root());
        _root->set_right(BTree(in).root());
        in >> token;
        if (token != "]")
        {
            throw std::runtime_error("Wrong input format.");
        }
    }
    else
        throw std::runtime_error("Wrong input format.");

    //
}

template <class T>
T BTree<T>::item() const
{
    assert(!is_empty());
    T ret_v;
    //
    ret_v = _root->item();
    //
    return ret_v;
}

template <class T>
BTree<T> BTree<T>::left() const
{
    assert(!is_empty());
    BTree<T> subtree;
    //
    // Hint: use the private constructor given a root node.
    subtree = _root->left();
    //
    return subtree;
}

template <class T>
BTree<T> BTree<T>::right() const
{
    assert(!is_empty());
    BTree<T> subtree;
    //
    // Hint: use the private constructor given a root node.
    subtree = _root->right();
    //
    return subtree;
}

template <class T>
std::ostream &BTree<T>::fold(std::ostream &out) const
{
    //
    if (_root == nullptr)
    {
        out << "[]";
    }
    else
    {
        out << "[ " << item() << " ";
        left().fold(out);
        out << " ";
        right().fold(out);
        out << " ]";
    }
    //
    return out;
}

template <class T>
void BTree<T>::create_root(const T &it)
{
    assert(is_empty());
    //
    _root = BTNode<T>::create(it);
    //
    assert(!is_empty());
    assert(item() == it);
    assert(left().is_empty());
    assert(right().is_empty());
}

template <class T>
void BTree<T>::set_item(const T &new_it)
{
    assert(!is_empty());
    //
    _root->set_item(new_it);
    //
    assert(item() == new_it);
}

template <class T>
void BTree<T>::set_left(const BTree<T> &new_left)
{
    assert(!is_empty());
    //
    auto aux = BTree<T>(new_left);
    _root->set_left(aux.root());
    //
    assert(left().root() == new_left.root());
}

template <class T>
void BTree<T>::set_right(const BTree<T> &new_right)
{
    assert(!is_empty());
    //
    _root->set_right(new_right.root());
    //
    assert(right().root() == new_right.root());
}

template <class T>
BTree<T>::BTree(const typename BTNode<T>::Ref &n)
{
    //
    _root = n;
    //
    assert(root() == n);
}

template <class T>
typename BTNode<T>::Ref BTree<T>::root() const
{
    typename BTNode<T>::Ref node;
    //
    node = _root;
    //
    return node;
}

template <class T>
void BTree<T>::set_root(const typename BTNode<T>::Ref &new_root)
{
    //
    _root = new_root;
    //
    assert(root() == new_root);
}

template <class T>
BTree<T>::BTree(const BTree<T> &other)
{
    set_root(other.root());
}

template <class T>
BTree<T>::BTree(BTree<T> &&other)
{
    set_root(other.root());
}

template <class T>
BTree<T> &BTree<T>::operator=(const BTree<T> &other)
{
    set_root(other.root());
    return *this;
}

template <class T>
BTree<T> &BTree<T>::operator=(BTree<T> &&other)
{
    set_root(other.root());
    return *this;
}
