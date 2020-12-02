//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 02 Dec 2020
//

#ifndef ASD2_LABS_2020_HASHMAPCHAIN_H
#define ASD2_LABS_2020_HASHMAPCHAIN_H

#include "HashMapWrapper.h"
#include <list>      // std::list<Key>
#include <vector>    // std::vector<std::list<Key>>
#include <cmath>     // std::ceil

template<class Key, class Hash = std::hash<Key>, class Pred = std::equal_to<Key>>
class HashMapChain : public HashMapWrapper<Key, Hash, Pred>
{
private:

   int nbElem;
   std::vector<std::list<Key>> hmap;
   bool canBeResized;

   typedef HashMapWrapper<Key, Hash, Pred> BASE;
   typedef typename std::list<Key>::const_iterator CListIterator;

   size_t getPos (const Key &key)
   {
      return BASE::hash(key) % hmap.size();
   }

public:

   HashMapChain (size_t length = 0)
   {
      hmap.resize(length);
      nbElem = 0;
      canBeResized = true;
   }

   void insert (const Key &key)
   {
      size_t pos = getPos(key);
      if (!contains(key))
      {
         hmap[pos].push_back(key);
         ++nbElem;
      }

      checkDistribution();
   };

   bool contains (const Key &key)
   {
      size_t pos = getPos(key);

      CListIterator it = find(key);
      if (it != hmap[pos].end())
      { return true; }

      return false;
   };

   void erase (const Key &key)
   {
      size_t pos = getPos(key);

      CListIterator it = find(key);
      if (it != hmap[pos].end())
      {
         hmap[pos].erase(it);
         --nbElem;
      }

      checkDistribution ();
   };

   size_t size ()
   {
      return nbElem;
   };

   size_t size2 ()
   {
      return hmap.size();
   };

private:

   CListIterator find (const Key &key)
   {
      size_t pos = getPos(key);

      for (auto it = hmap[pos].begin(); it != hmap[pos].end(); ++it)
      {
         if (BASE::pred(*it,key))
         { return it; }
      }

      return hmap[pos].end();
   }

   void checkDistribution ()
   {
      if(!canBeResized) return;

      double ratio = (double)nbElem / (double)hmap.size();

      if (ratio >= 8)
      {
         resize(hmap.size() * 2);
      }

      if (ratio <= 2)
      {
         resize(std::ceil((double)hmap.size() / (double)2));
      }
   }

   void resize (size_t newSize)
   {
      std::vector<std::list<Key>> tempHmap = std::vector<std::list<Key>>{newSize};
      hmap.swap(tempHmap);
      nbElem = 0;

      canBeResized = false;

      for(int i = 0; i < tempHmap.size(); ++i)
      {
         for(const Key& key : tempHmap[i])
         {
            insert(key);
         }
      }

      canBeResized = true;
   }
};

#endif //ASD2_LABS_2020_HASHMAPCHAIN_H
