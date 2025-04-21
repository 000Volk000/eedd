/**
 * @file avltree_node_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <cassert>
#include <avltree_node.hpp>

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::This() const
{
    return This_;
}

template <class T>
AVLTNode<T>::AVLTNode(T const &it)
{
    //
    item_ = it;
    left_ = nullptr;
    right_ = nullptr;
    parent_ = nullptr;
    height_ = 0;
    //
    assert(item() == it);
    assert(left() == nullptr);
    assert(right() == nullptr);
#ifndef __ONLY_BSTREE__
    assert(parent() == nullptr);
    assert(height() == 0);
    assert(check_height_invariant());
#endif
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::create(T const &it)
{
    auto This = typename AVLTNode<T>::Ref(new AVLTNode(it));
    This->This_ = This;
    return This;
}

template <class T>
const T &AVLTNode<T>::item() const
{
    //
    return item_;
    //
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTNode<T>::left() const
{
    //
    return left_;
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTNode<T>::left()
{
    //
    return left_;
    //
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTNode<T>::right() const
{
    //
    return right_;
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTNode<T>::right()
{
    //
    return right_;
    //
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTNode<T>::child(int dir) const
{
    assert(dir == 0 || dir == 1);
    //
    // Remember: this operation is only necessary for the AVLTree.
    if (dir == 0)
        return left();

    if (dir == 1)
        return right();
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTNode<T>::child(int dir)
{
    assert(dir == 0 || dir == 1);
    //
    // Remember: this operation is only necessary for the AVLTree.
    if (dir == 0)
        return left();

    if (dir == 1)
        return right();
    //
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTNode<T>::parent() const
{
    //
    // Remember: this operation is only necessary for the AVLTree.
    //
    return parent_;
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTNode<T>::parent()
{
    //
    // Remember: this operation is only necessary for the AVLTree.
    //
    return parent_;
    //
}

template <class T>
int AVLTNode<T>::height() const
{
    //
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: we want O(1) here.
    return height_;
    //
}

template <class T>
int AVLTNode<T>::balance_factor() const
{
    int bf = 0;
    //
    // Remember: this operation is only necessary for the AVLTree.
    int lh, rh;
    if (left() == nullptr)
        lh = -1;
    else
        lh = left_->height();

    if (right() == nullptr)
        rh = -1;
    else
        rh = right_->height();

    bf = rh - lh;
    //
    return bf;
}

template <class T>
bool AVLTNode<T>::check_height_invariant() const
{
    bool ret_val = false;
#ifdef __ONLY_BSTREE__
    ret_val = true; // In a BSTree we do not need to check the height invariant.
#else
    //
    // Remember: the height of a node is one more than the maximum of the heights of its children.
    int lh, rh;
    if (left() == nullptr)
        lh = -1;
    else
        lh = left_->height();

    if (right() == nullptr)
        rh = -1;
    else
        rh = right_->height();

    if (height_ == std::max(rh, lh) + 1)
        ret_val = true;
    //
#endif
    return ret_val;
}

template <class T>
void AVLTNode<T>::update_height()
{
    //
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: we want O(1) here.
    // Remember: the height of a node is one more than the maximum of the heights of its children.
    // Remember: the height of a "void" node is -1.
    int lh, rh;
    if (left() == nullptr)
        lh = -1;
    else
        lh = left_->height();

    if (right() == nullptr)
        rh = -1;
    else
        rh = right_->height();

    height_ = std::max(rh, lh) + 1;
    //
    assert(check_height_invariant());
}

template <class T>
void AVLTNode<T>::set_item(const T &new_it)
{
    //
    item_ = new_it;
    //
    assert(item() == new_it);
}

template <class T>
void AVLTNode<T>::set_parent(AVLTNode<T>::Ref new_parent)
{
    //
    // Remember: this operation is only necessary for the AVLTree.
    parent_ = new_parent;
    //
    assert(parent() == new_parent);
}

template <class T>
void AVLTNode<T>::set_left(Ref new_child)
{
    //
    // Remember: When implementing the AVL Tree, the child's parent link is needed to be
    // updated to point to this node. Use This() method to get a Reference to this.
    // Remember: When implementing the AVL Tree, the node height must be updated at the end.
    left_ = new_child;
    if (new_child != nullptr)
    {
        left_->set_parent(This());
    }
    update_height();
    //
    assert(left() == new_child);
#ifndef __ONLY_BSTREE__
    assert(check_height_invariant());
    assert(!new_child || new_child->parent() == This());
#endif
}

template <class T>
void AVLTNode<T>::set_right(AVLTNode<T>::Ref new_child)
{
    //
    // Remember: for the AVLTree the child's parent link is needed to be
    // updated to point to this node. Use This() method to get a Reference to this.
    // Remember: for the AVLTree the height of the node must be updated at the end.
    right_ = new_child;
    if (new_child != nullptr)
    {
        right_->set_parent(This());
    }
    update_height();
    //
    assert(right() == new_child);
#ifndef __ONLY_BSTREE__
    assert(check_height_invariant());
    assert(!new_child || new_child->parent() == This());
#endif
}

template <class T>
void AVLTNode<T>::set_child(int dir, Ref new_child)
{
    assert(dir == 0 || dir == 1);
    //
    // Remember: this operation is only necessary for the AVLTree.
    if (dir == 0)
        return set_left(new_child);

    if (dir == 1)
        return set_right(new_child);
    //
    assert(check_height_invariant());
    assert(dir == 0 || right() == new_child);
    assert(dir == 1 || left() == new_child);
    assert(!new_child || new_child->parent() == This());
}
