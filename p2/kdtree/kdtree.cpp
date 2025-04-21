/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <algorithm>
#include <limits>

#include "kdtree.hpp"

bool operator==(const Pattern &a, const Pattern &b)
{
    return a.class_label() == b.class_label() &&
           a.dim() == b.dim() &&
           (a.values() == b.values()).min();
}

KDTree::~KDTree()
{
}

bool KDTree::is_empty() const
{
    bool empty = true;
    // TODO

    //
    return empty;
}

Pattern KDTree::item() const
{
    assert(!is_empty());
    Pattern ret_v;
    // TODO

    //
    return ret_v;
}

KDTree KDTree::left() const
{
    assert(!is_empty());
    KDTree ret_v;
    // TODO

    //
    return ret_v;
}

KDTree KDTree::right() const
{
    assert(!is_empty());
    KDTree ret_v;
    // TODO

    //
    return ret_v;
}

size_t
KDTree::get_k() const
{
    size_t k = 0;
    // TODO

    //
    return k;
}

KDTree::KDTree()
{
    // TODO

    //
    assert(is_empty());
}

KDTree::KDTree(const BTree<Pattern> &tree, size_t k)
{
    // TODO

    //
}

BTree<Pattern> KDTree::btree() const
{
    BTree<Pattern> ret_v;
    // TODO

    //
    return ret_v;
}

void KDTree::set_btree(const BTree<Pattern> &new_tree)
{
    // TODO

    //
}

void KDTree::set_k(size_t k)
{
    // TODO

    //
    assert(get_k() == k);
}

/**
 * @brief Create a level of the kdtree object.
 *
 * Create a binary tree in a recursive way splitting each dimension into two
 * parts using the median as pivot and calling recursively for each part.
 * The pivot will be the root of the binary tree.
 *
 * @param begin is the an iterator at the begin of patterns seq.
 * @param end is the an iterator at the end of patterns seq.
 * @param level is the current level of this subtree.
 * @param k is the number of dimensions of the pattern's space.
 * @return a ref to the binary tree created of this level.
 */
static BTree<Pattern>
create_kdtree(std::vector<Pattern>::iterator begin,
              std::vector<Pattern>::iterator end,
              size_t level, size_t k)
{
    BTree<Pattern> btree;
    const size_t size = std::distance(begin, end);

    if (size > 0)
    {
        // TODO

        // First: locate the median pattern.
        // Hint: use a lambda to implement the pattern comparison algorithm.

        // Second: create the root of the binary tree with the median pattern.

        // Third: Set the left and right subtrees (if needed) by recursion using
        // the begin and end iterators to set the range of the patterns for each subtree.
        // Remember: increment the level parameter.

        //
    }
    return btree;
}

void KDTree::fit(std::vector<Pattern> &dataset)
{
    assert(dataset.size() > 0);
    // TODO
    // Hint: use the create_kdtree function to create the binary tree.

    //
    assert(get_k() == dataset[0].dim());
}

KDTree::KDTree(std::vector<Pattern> &dataset)
{
    assert(dataset.size() > 0);
    // TODO
    // Hint: use the fit method.

    //
    assert(dataset.size() == 0 || !is_empty());
}

KDTree::KDTree(std::istream &in) noexcept(false)
    : KDTree()
{
    // TODO

    //
}

std::ostream &KDTree::fold(std::ostream &out) const
{
    // TODO

    //
    return out;
}

std::tuple<float, Pattern>
KDTree::find_nn(Pattern const &p, const KDTree::distance_function_t &dist,
                size_t level) const
{
    // Which dimension is splitted here.
    size_t axis = level % p.dim();

    Pattern curr = item();
    float curr_dist = dist(p, curr);

    auto curr2 = curr;
    auto curr2_dist = curr_dist;

    // TODO: step 1: find candidate in the corresponding subtree.
    // Hint: use std::tie to set the return values to curr2 and curr2_dist.

    //

    // TODO: step 2: update the current candidate if needed.

    //

    // TODO: step 3: find candidate in the other subtree or cut the search.

    //

    // TODO: step 4: update the current candidate if needed.

    //

    return std::make_tuple(curr_dist, curr);
}

std::tuple<float, Pattern>
KDTree::find_nn(Pattern const &p, const KDTree::distance_function_t &dist) const
{
    assert(!is_empty());
    assert(p.dim() == get_k());
    return find_nn(p, dist, 0);
}
