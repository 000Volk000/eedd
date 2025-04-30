/**
 * @file hash_table_imp.hpp
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

#include <hash_table.hpp>
#include <hash_table_iterator.hpp>

template <class K, class V>
HashTable<K, V>::HashTable(size_t m,
                           const Key_to_uint64_t &key_to_int,
                           OACollisionResolution::Ref hash)
{
    assert(m == hash->m());
    // TODO

    //
    assert(size() == m);
}

template <class K, class V>
size_t
HashTable<K, V>::size() const
{
    size_t ret_v = 0;
    // TODO

    //
    return ret_v;
}

template <class K, class V>
float HashTable<K, V>::load_factor() const
{
    float ret_v = 0.0f;
    // TODO

    //
    return ret_v;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::begin() const
{
    HashTableIterator<K, V> ret_v;
    // TODO
    // Remember: the iterator should point to the first valid entry.
    // Hint: you must use const_cast to remove the const qualifier from this.

    //
    return ret_v;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::end() const
{
    HashTableIterator<K, V> ret_v;
    // TODO
    // Remember: the iterator should point one position pass the end of the table.
    // Hint: you must use const_cast to remove the const qualifier from this.
    ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V> *>(this), size());
    //
    assert(!ret_v.is_valid());
    return ret_v;
}

template <class K, class V>
size_t HashTable<K, V>::find_position(K const &k) const
{
    assert(load_factor() < 1.0f);
    size_t idx = 0;
    // TODO

    //
    assert(0 <= idx && idx < size());
    return idx;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::find(K const &k) const
{
    HashTableIterator<K, V> ret_v = end();
    // TODO
    // Hint: use find_position.
    // Hint: you must use const_cast to remove the const qualifier from this.
    size_t idx = find_position(k);
    if (entry(idx).is_valid())
        ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V> *>(this), idx);
    else
        ret_v = end();
    //
    assert(ret_v == end() || (ret_v.is_valid() && ret_v.key() == k));
    return ret_v;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::insert(K const &k, V const &v)
{
    assert(load_factor() <= 0.5f);
    HashTableIterator<K, V> ret_v = end();
    const size_t current_size = size();
    // TODO
    // Remember: increment the number of used entries only when an
    //    empty entry was used.
    // Remember: you must call to rehash before inserting a new entry to avoid
    //    a load factor greater than 0.5.
    // Remember: if a rehashing was done (current_size != new size returned by
    //    rehash function), you need to find the new location of the inserted key.

    //
    assert(ret_v.is_valid());
    assert(ret_v.key() == k);
    assert(ret_v.value() == v);
    assert(load_factor() <= 0.5f);
    return ret_v;
}

template <class K, class V>
void HashTable<K, V>::remove(HashTableIterator<K, V> &iter)
{
#ifndef NDEBUG
    assert(iter.is_valid());
    K old_k = iter.key();
#endif
    // TODO
    // Remember: we are using a mark to sign "deleted".

    //
    assert(!iter.is_valid());
    assert(find(old_k) == end());
}

template <class K, class V>
size_t HashTable<K, V>::rehash()
{
    // TODO
    // Remember: rehash when load_factor > 0.5
    // Remember: we use a 2 factor to grown the current size.
    // Remember: a new hash function will be picked at random from the Universal Family.
    // Remember: reset the number of used entries to zero before inserting the old valid
    // entries in the new table.

    //
    assert(load_factor() <= 0.5);
    return size();
}

template <class K, class V>
HashTableEntry<K, V> const &HashTable<K, V>::entry(size_t idx) const
{
    assert(idx < size());
    // TODO: recode according to your representation.
    HashTableEntry<K, V> aux;
    return aux;
    //
}

template <class K, class V>
HashTableEntry<K, V> &HashTable<K, V>::entry(size_t idx)
{
    assert(idx < size());
    // TODO: recode according to your representation.
    HashTableEntry<K, V> aux;
    return aux;
    //
}
