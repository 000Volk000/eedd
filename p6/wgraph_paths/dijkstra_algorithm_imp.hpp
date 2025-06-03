/**
 * @file dijkstra_algorithm_imp.hpp
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
#include <tuple>
#include <functional>
#include <limits>

#include <dijkstra_algorithm.hpp>
#include <priority_queue.hpp>

template <class T>
void dijkstra_algorithm(Graph<T, float> &g,
                        typename Graph<T, float>::VertexRef const &source,
                        std::vector<size_t> &predecessors,
                        std::vector<float> &distances)
{
    assert(g.has(source));

    /** @brief the Dijkstra tuple.
     * We use the tuple (dist,u's label,v's label) format to represent an edge.
     * Remember: tuples use lexicographic comparisons.
     */
    using Tuple = std::tuple<float, size_t, size_t>;

    // Reset visited flags.
    g.reset(false);

    // initialize the predecessors and distances vectors.
    // Remember: each vertex is predecessor of itself with distance infinite.
    typename Graph<T, float>::VertexRef u, v;
    EdgeIterator<T, float> e;
    Tuple t;

    auto less = [](const Tuple &a, const Tuple &b)
    {
        return a < b;
    };
    std::vector<Tuple> qVec;
    PriorityQueue<Tuple> q(qVec, less);

    predecessors.resize(g.num_vertices());
    distances.resize(g.num_vertices());

    for (size_t i = 0; i < predecessors.size(); i++)
    {
        predecessors[i] = i;
    }

    for (auto &it : distances)
        it = std::numeric_limits<float>::infinity();
    //

    // implement the Dijkstra algorithm.
    // Note: you can use std::priority_queue if you have not implemented
    // the ADT PriorityQueue.
    q.enqueue(Tuple(0.0, source->label(), source->label()));

    while (!q.is_empty())
    {
        t = q.front();
        q.dequeue();
        u = g.vertex(std::get<1>(t));

        if (!u->is_visited())
        {
            predecessors[std::get<1>(t)] = std::get<2>(t);
            distances[std::get<1>(t)] = std::get<0>(t);
            u->set_visited(true);
            e = g.edges_begin(g.get_iterator(u));

            while (e != g.edges_end(g.get_iterator(u)))
            {
                v = (*e)->other(u);
                if (!v->is_visited())
                    q.enqueue(Tuple(distances[u->label()] + (*e)->item(), v->label(), u->label()));
                e++;
            }
        }
    }
    //
}

inline std::list<size_t>
dijkstra_path(size_t src, size_t dst,
              std::vector<size_t> const &predecessors)
{
    assert(src < predecessors.size());
    assert(dst < predecessors.size());
    assert(predecessors[src] == src);
    std::list<size_t> path;
    //
    // Remember: if the destination is unreachable, return an empty list.
    if (predecessors[dst] != dst || dst == src)
    {
        size_t pred = dst;
        do
        {
            path.push_front(pred);
            pred = predecessors[pred];
        } while (pred != predecessors[pred]);
        path.push_front(src);
    }
    //
    return path;
}
