/*
 * Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 02 Dec 2020
 */

#ifndef HASHMAP_WRAPPER_H
#define HASHMAP_WRAPPER_H

#include <functional> // hash<Key>, equal_to<Key>

template<class Key, class Hash = std::hash<Key>, class Pred = std::equal_to<Key>>
class HashMapWrapper
{
protected:
   Hash hash;
   Pred pred;

public:

   virtual void insert (const Key &key) = 0;

   virtual bool contains (const Key &key) = 0;

   virtual void erase (const Key &key) = 0;

   virtual size_t size () = 0;
};

#endif //HASHMAP_WRAPPER_H
