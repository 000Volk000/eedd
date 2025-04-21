/**
 * @file avltree_imp.hpp
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
#include <numeric>
#include <functional>
#include <limits>
#include <vector>
#include <algorithm>
#include <avltree.hpp>

template <class T>
AVLTree<T>::AVLTree()
{
    //
    root_ = nullptr;
    parent_ = nullptr;
    curr_ = nullptr;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(is_empty());
    assert(!current_exists());
#ifndef __ONLY_BSTREE__
    assert(height() == -1);
#endif
}

template <class T>
AVLTree<T>::AVLTree(T const &item)
{
    //
    root_ = AVLTNode<T>::create(item);
    parent_ = nullptr;
    curr_ = root_;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(item() == item);
    assert(current_exists());
    assert(current() == item);
#ifndef __ONLY_BSTREE__
    assert(current_level() == 0);
    assert(height() == 0);
#endif
}

template <class T>
AVLTree<T>::AVLTree(std::istream &in) noexcept(false)
{
    //
    std::string token;
    in >> token;
    if (token == "[]")
    {
        root_ = nullptr;
        curr_ = nullptr;
        parent_ = nullptr;
    }
    else if (token == "[")
    {
        T item;
        if (!(in >> item))
            throw std::runtime_error("Wrong input format.");
        create_root(item);

        AVLTree<T> left_subtree(in);
        set_left(left_subtree);

        AVLTree<T> right_subtree(in);
        set_right(right_subtree);

        if (!(in >> token) || (token != "]"))
            throw std::runtime_error("Wrong input format.");
    }
    else
    {
        throw std::runtime_error("Wrong input format.");
    }
    //
    if (!is_a_binary_search_tree())
        throw std::runtime_error("It is not a binary search tree");
    if (!is_a_balanced_tree())
        throw std::runtime_error("It is not an avl tree");
}

template <class T>
AVLTree<T>::~AVLTree()
{
    //
    // Think if it is necessary to do something here regarding your representation.
    //
}

#ifdef __ONLY_BSTREE__
/**
 * @brief Create an perfectly balanced BSTree by inserting the median of
 *        an ordered sub sequence data[begin, end).
 * @param data is the ordered sequence of values.
 * @param begin,
 * @param end specify a [begin, end) indexing interval of array data to use.
 * @pre 0 <= begin <= end <=data.size()
 * @pre begin==end || data[begin]<data[end];
 */
template <class T>
void create_inserting_median(std::vector<T> const &data,
                             size_t begin,
                             size_t end,
                             AVLTree<T> &tree)
{
    assert(begin <= end);
    assert(end <= data.size());
    assert(begin == end || data[begin] <= data[end - 1]);

    //
    // Hint: if (end==begin) none thing must be done (it is an empty sub array)
    //  else, insert the median in the tree and (recursively) process
    //  the two sub sequences [begin, median_idx) and [median_idx+1, end)
    if (end > begin)
    {
        tree.insert(data[begin + ((end - begin) / 2)]);
        create_inserting_median(data, begin, begin + ((end - begin) / 2), tree);
        create_inserting_median(data, (begin + ((end - begin) / 2)) + 1, end, tree);
    }

    //
}

template <class T>
AVLTree<T>
create_perfectly_balanced_bstree(std::vector<T> &data)
{
    AVLTree<T> tree;
    //
    // Remember: the empty tree is perfectly balanced.
    // Remember: first, an ordered sequence (using < order) of values is needed.
    // Then you should use the above create_inserting_median function
    // on a empty tree to recursively create the perfectly balanced bstree.
    std::sort(data.begin(), data.end());
    create_inserting_median(data, 0, data.size(), tree);
    //
    return tree;
}
#endif //__ONLY_BSTREE__

template <class T>
bool AVLTree<T>::is_empty() const
{
    //
    if (root_ == nullptr)
    {
        return true;
    }
    return false;
    //
}

template <class T>
T const &AVLTree<T>::item() const
{
    assert(!is_empty());
    //
    return root_->item();
    //
}

template <class T>
std::ostream &AVLTree<T>::fold(std::ostream &out) const
{
    // FIXME
    if (is_empty())
    {
        out << "[]";
    }
    else
    {
        out << "[ ";
        out << item();
        out << " ";
        left().fold(out);
        out << " ";
        right().fold(out);
        out << " ]";
    }
    //
    return out;
}

template <class T>
bool AVLTree<T>::current_exists() const
{
    //
    if (curr_ != nullptr)
    {
        return true;
    }
    return false;
    //
}

template <class T>
T const &AVLTree<T>::current() const
{
    assert(current_exists());
    //
    return curr_->item();
    //
}

template <class T>
int AVLTree<T>::current_level() const
{
    assert(current_exists());
    int level = 0;
    //
    auto aux = parent_;
    while (aux != nullptr)
    {
        level++;
        aux = aux->parent();
    }
    //
    return level;
}

template <class T>
AVLTree<T> AVLTree<T>::left() const
{
    assert(!is_empty());
    //
    // Hint: use the private AVLTree constructor given a node as root.
    return root_->left();
    //
}

template <class T>
AVLTree<T> AVLTree<T>::right() const
{
    assert(!is_empty());
    //
    // Hint: use the private AVLTree constructor given a node as root.
    return root_->right();
    //
}

template <class T>
size_t AVLTree<T>::size() const
{
    size_t s = 0;
    //
    if (!is_empty())
    {
        s = 1 + left().size() + right().size();
    }
    //
    return s;
}

template <class T>
int AVLTree<T>::height() const
{
    int h = -1;
    //
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: we want O(1) here.
    if (!is_empty())
    {
        h = root_->height();
    }
    //
    return h;
}

template <class T>
int AVLTree<T>::balance_factor() const
{
    int bf = 0;
    //
    // Remember: this operation is only necessary for the AVLTree.
    bf = root_node()->balance_factor();
    //
    return bf;
}

template <class T>
bool AVLTree<T>::has(const T &k) const
{
#ifndef NDEBUG
    bool old_current_exists = current_exists();
    T old_current;
    if (old_current_exists)
        old_current = current();
#endif

    bool found = true;

    //
    // Hint: you can reuse the search method for this but in this case you will
    //       need to use "const_cast" to remove constness of "this" and
    //       save/restore the old state of current before returning.
    auto old = current_node();
    AVLTree<T> *nonConstThis = const_cast<AVLTree<T> *>(this);
    found = nonConstThis->search(k);
    nonConstThis->set_current_node(old);
    //

#ifndef NDEBUG
    assert(!old_current_exists || old_current == current());
#endif
    return found;
}

/**
 * @brief infix process of a node.
 * The Processor must allow to be used as a function with a parameter  (the
 * item to be processed) and returning true if the process must continue or
 * false if not.
 * @param node is the node to be processed.
 * @param p is the Processor.
 * @return true if all the tree was in-fix processed.
 */
template <class T, class Processor>
bool infix_process(typename AVLTNode<T>::Ref node, Processor &p)
{
    bool retVal = true;
    //
    // Remember: if node is nullptr return true.
    if (node != nullptr)
    {
        retVal = infix_process<T>(node->left(), p);
        retVal = retVal && p(node->item());
        retVal = retVal && infix_process<T>(node->right(), p);
    }
    //
    return retVal;
}

template <class T>
bool AVLTree<T>::is_a_binary_search_tree() const
{
    bool is_bst = true;
    //
    // Remember: a empty tree is a binary search tree.
    //
    // Remember: for a non empty binary search tree, the in-fix traversal from
    // the root node must follow an ordered sequence of items.
    //
    // Remember: use a lambda function with signature '(T v) -> bool' to
    //  implement the Processor.
    //
    if (!is_empty())
    {
        std::vector<T> v;
        auto p = [&v](T const &it)
        {
            v.push_back(it);
            return std::is_sorted(v.begin(), v.end());
        };
        is_bst = infix_process<T>(root_node(), p);
    }
    //
    return is_bst;
}

template <class T>
bool AVLTree<T>::is_a_balanced_tree() const
{
    bool is_balanced = true;
#ifndef __ONLY_BSTREE__
    //
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: a empty tree is balanced.
    //
    // Remember: A non empty tree is balanced if both children are balanced
    // and the absolute value of the balance factor of the tree is less or
    // equal to one.
    if (!is_empty())
    {
        is_balanced = std::abs(balance_factor()) <= 1;
        is_balanced = is_balanced && left().is_a_balanced_tree();
        is_balanced = is_balanced && right().is_a_balanced_tree();
    }
    //
#endif
    return is_balanced;
}

template <class T>
void AVLTree<T>::create_root(T const &v)
{
    assert(is_empty());
    //
    root_ = AVLTNode<T>::create(v);
    curr_ = root_;
    parent_ = nullptr;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(item() == v);
    assert(current_exists());
    assert(current() == v);
#ifndef __ONLY_BSTREE__
    assert(current_level() == 0);
    assert(height() == 0);
#endif
}

template <class T>
bool AVLTree<T>::search(T const &k)
{
    bool found = false;
    //
    set_current_node(root_);
    set_parent_node(nullptr);
    while (current_node() != nullptr && !found)
    {
        if (current_node()->item() == k)
        {
            found = true;
        }
        else
        {
            set_parent_node(current_node());
            if (current_node()->item() > k)
            {
                set_current_node(current_node()->left());
            }
            else
            {
                set_current_node(current_node()->right());
            }
        }
    }
    //
    assert(!found || current() == k);
    assert(found || !current_exists());
    return found;
}

template <class T>
void AVLTree<T>::insert(T const &k)
{
    // Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());

    if (!search(k))
    {
        //
        curr_ = AVLTNode<T>::create(k);

        if (parent_node() == nullptr)
            set_root_node(current_node());

        else if (current_node()->item() < parent_node()->item())
            parent_node()->set_left(current_node());

        else
            parent_node()->set_right(current_node());

        current_node()->set_parent(parent_node());
        //
        assert(check_parent_chains());
        make_balanced();
        assert(check_parent_chains());
    }
    // Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());

    // check postconditions.
    assert(current_exists());
    assert(current() == k);
}

template <class T>
void AVLTree<T>::remove()
{
    // check preconditions.
    assert(current_exists());

#ifndef NDEBUG
    // the invariants only must be checked for the first recursive call.
    // We use a static variable to count the recursion levels.
    // see section "Static variables in a Function" in
    // ref https://www.geeksforgeeks.org/static-keyword-cpp/ for more info.
    static int recursion_count = 0;
    recursion_count++;
    if (recursion_count == 1)
    {
        // Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_balanced_tree());
    }
#endif // NDEBUG

    bool replace_with_subtree = true;
    typename AVLTNode<T>::Ref subtree;

    //
    //  Check which of cases 0,1,2,3 we have (see theory class slides).
    if (current_node()->right() == nullptr && current_node()->left() == nullptr)
        subtree = nullptr;

    else if (current_node()->left() == nullptr)
        subtree = current_node()->right();

    else if (current_node()->right() == nullptr)
        subtree = current_node()->left();

    else
        replace_with_subtree = false;
    //

    if (replace_with_subtree)
    {
        //
        // Manage cases 0,1,2
        // Remember: update subtree to parent links too.
        if (parent_node() == nullptr)
            set_root_node(subtree);

        else if (current_node() == parent_node()->left())
            parent_node()->set_left(subtree);

        else if (current_node() == parent_node()->right())
            parent_node()->set_right(subtree);

        set_current_node(nullptr);
        //
        assert(check_parent_chains());
        make_balanced();
        assert(check_parent_chains());
    }
    else
    {
        //
        // Manage case 3.
        auto sig = current_node();
        find_inorder_sucessor();

        sig->set_item(current_node()->item());
        remove();
        //
    }

#ifndef NDEBUG
    // We come back so the recursion count must be decreased.
    recursion_count--;
    assert(recursion_count >= 0);
    if (recursion_count == 0)
    {
        // Only check for the last return.
        // Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_balanced_tree());

        // Check postconditions.
        assert(!current_exists());
    }
#endif
}

template <class T>
AVLTree<T>::AVLTree(typename AVLTNode<T>::Ref const &root)
{
    //
    set_root_node(root);
    set_current_node(root_);
    set_parent_node(nullptr);
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(root_node() == root);
    assert(current_node() == root);
    assert(parent_node() == nullptr);
}

template <class T>
void AVLTree<T>::set_left(AVLTree<T> &subtree)
{
    assert(!is_empty());
    //
    root_->set_left(subtree.root_node());
    if (!subtree.is_empty())
    {
        subtree.root_node()->set_parent(root_node());
    }
    //
    assert(subtree.is_empty() || left().item() == subtree.item());
    assert(!subtree.is_empty() || left().is_empty());
}

template <class T>
void AVLTree<T>::set_right(AVLTree<T> &subtree)
{
    assert(!is_empty());
    //
    // Remember to set parent's link of the subtree root to this.
    root_->set_right(subtree.root_node());
    if (!subtree.is_empty())
    {
        subtree.root_node()->set_parent(root_node());
    }
    //
    assert(subtree.is_empty() || right().item() == subtree.item());
    assert(!subtree.is_empty() || right().is_empty());
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTree<T>::current_node() const
{
    //
    return curr_;
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTree<T>::current_node()
{
    //
    return curr_;
    //
}

template <class T>
void AVLTree<T>::set_current_node(typename AVLTNode<T>::Ref const &new_c)
{
    //
    curr_ = new_c;
    //
    assert(current_node() == new_c);
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTree<T>::root_node() const
{
    //
    return root_;
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTree<T>::root_node()
{
    //
    return root_;
    //
}

template <class T>
void AVLTree<T>::set_root_node(typename AVLTNode<T>::Ref const &new_root)
{
    //
    root_ = new_root;
    //
    assert(root_node() == new_root);
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTree<T>::parent_node() const
{
    //
    return parent_;
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTree<T>::parent_node()
{
    //
    return parent_;
    //
}

template <class T>
void AVLTree<T>::set_parent_node(typename AVLTNode<T>::Ref const &new_p)
{
    //
    parent_ = new_p;
    //
    assert(parent_node() == new_p);
}

template <class T>
void AVLTree<T>::find_inorder_sucessor()
{
    assert(current_exists());
    assert(is_a_binary_search_tree());

#ifndef NDEBUG
    T old_curr = current();
#endif
    //
    set_parent_node(current_node());
    set_current_node(current_node()->right());
    while (current_node()->left() != nullptr)
    {
        set_parent_node(current_node());
        set_current_node(current_node()->left());
    }
    //
    assert(current_exists() && current_node()->left() == nullptr);
#ifndef NDEBUG
    assert(current() > old_curr);
#endif
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::rotate(typename AVLTNode<T>::Ref &P, int dir)
{
    assert(P != nullptr);
    assert(dir == 0 || dir == 1);
    assert(P->child(1 - dir) != nullptr);
    auto N = P->child(1 - dir); // the child to promote.
#ifdef __DEBUG__
    if (__DEBUG__ > 1)
        std::clog << "Rotating to " << (dir == 0 ? "left" : "right") << " on key " << P->item() << std::endl;
#endif
    //
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: if P has not a parent (it is the tree's current root),
    // the promoted node N will be the new root of the tree.
    // Hint: you can see wikipedia: https://en.wikipedia.org/wiki/Tree_rotation
    auto G = P->parent();

    N = P->child(1 - dir);

    auto CN = N->child(dir);

    P->set_child(1 - dir, CN);

    N->set_child(dir, P);
    if (G != nullptr)
    {

        int gpDir = G->child(0) == P ? 0 : 1;
        G->set_child(gpDir, N);
    }
    else
    {

        N->set_parent(nullptr);
        set_root_node(N);
    }
    //
    return N;
}

template <class T>
void AVLTree<T>::make_balanced()
{
#ifdef __ONLY_BSTREE__
    return; // for a BSTree there is no need to balance.
#else
    auto P = parent_node(); // the subtree root node.

    while (P)
    {
        //
        // Check the subtree balance factor to do rotations if needed.
        P->update_height();
        // First, update subtree root node height because we have just done
        // an insertion/deletion in the subtree.
        //
        int bfP = P->balance_factor();
        // Second, compute balance factor.
        //
        if (std::abs(bfP) > 1)
        {
            int dir = (bfP < 0) ? 0 : 1;
            auto N = P->child(dir);

            int bfN = N->balance_factor();

            if (bfP * bfN >= 0)
            {

                P = rotate(P, 1 - dir);
            }
            else
            {

                rotate(N, dir);

                P = rotate(P, 1 - dir);
            }
        }
        // Third, check the balance factor to do rotations if needed.
        // Remember: update subtree_root if any rotation is done.
        //

        P = P->parent(); // going up.
    }
    // Update the cursor's parent_ node if needed.
    if (current_exists())
        set_parent_node(current_node()->parent());
    assert(!current_exists() || current_node()->parent() == parent_node());
#endif //__ONLY_BSTREE__
}

template <class T>
bool AVLTree<T>::check_parent_chains() const
{
#ifdef __ONLY_BSTREE__
    return true; // for a BSTree there is no need to check this.
#else
    if (!is_empty())
    {
        std::function<void(typename AVLTNode<T>::Ref, std::vector<typename AVLTNode<T>::Ref>)> go_down;
        go_down = [&go_down](typename AVLTNode<T>::Ref node, std::vector<typename AVLTNode<T>::Ref> branch) -> void
        {
            if (node->left() != nullptr || node->right() != nullptr)
            {
                branch.push_back(node);
                if (node->left())
                    // go down by the left
                    go_down(node->left(), branch);
                if (node->right())
                    // go down by the right
                    go_down(node->right(), branch);
            }
            else
            {
                // The node is a leaf node, so check the branch
                // to the tree root node.
                typename AVLTNode<T>::Ref parent = node->parent();
                int idx = static_cast<int>(branch.size()) - 1;
                while (parent && idx >= 0)
                {
                    assert(parent == branch[idx]);
                    --idx;
                    parent = parent->parent();
                }
                assert(idx == -1 && parent == nullptr);
            }
        };
        std::vector<typename AVLTNode<T>::Ref> branch;
        go_down(root_node(), branch);
    }
    return true;
#endif
}

template <class T>
std::tuple<int, int>
compute_min_max_branch_length(AVLTree<T> const &tree)
{
    int min_path_l = std::numeric_limits<int>::max();
    int max_path_l = 0;

    // TODO
    //  Hint: you can use a lambda function to recursive go down through the tree.
    //  A new recursion increase the level in the tree. When a subtree is empty
    //  you have achieved a the leaf of a branch and the current level is e
    //  the branch length ending in this leaf node so we can update
    //  the min/max length values according before returning.
    //  @see: https://stackoverflow.com/questions/2067988/recursive-lambda-functions-in-c11
    //  or check_parent_chains() function the to study similar cases.

    //

    return std::make_tuple(min_path_l, max_path_l);
}
template <class T>
AVLTreeIterator<T> AVLTree<T>::begin() const
{
    typename AVLTNode<T>::Ref node;
    // TODO

    //
    return AVLTreeIterator<T>(node);
}

template <class T>
AVLTreeIterator<T> AVLTree<T>::end() const
{
    return AVLTreeIterator<T>(nullptr);
}
