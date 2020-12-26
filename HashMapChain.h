//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 02 Dec 2020
//

#ifndef ASD2_LABS_2020_HASHMAPCHAIN_H
#define ASD2_LABS_2020_HASHMAPCHAIN_H

#include "HashMapCommon.h"
#include <list>      // std::list<Key>
#include <vector>    // std::vector<std::list<Key>>
#include <algorithm> // std::find()

/*
 * @Brief Classe définissant une table de hachage selon le principe de chaînage
 *        La fonction std::hash doit être définie pour le type de Key sinon passer
 *        une fonction personnalisé. De même, == doit être défini pour Key.
 */
template<class Key, class Hash = std::hash<Key>, class Pred = std::equal_to<Key>>
class HashMapChain : public HashMapCommon<Key, Hash, Pred>
{
private:
   typedef HashMapCommon<Key, Hash, Pred> super;

   std::vector<std::list<Key>> hmap;

public:

    /**
     * @brief Constructeur. Mise en place des structure de stockages
     * @param length Hash map length
     */
   HashMapChain (size_t length = 1) : HashMapCommon<Key, Hash, Pred>(2,8)
   {
      hmap.resize(length);
   }

   /**
    * @brief Insertion d'un élément dans la hashmap.
    * @param key Élément à insérer.
    */
   void insert (const Key &key)
   {
      size_t pos = super::getKey(key, hmap.size());

      if (super::mustCheckContains && contains(key)) return;

      hmap[pos].emplace_front(key);
      ++super::nbElem;


      super::checkDistribution(INSERTION);
   }

   /**
   * @brief Vérifie si la clé est contenue dans la table de hachage.
   * @param key Clé à vérifier.
   * @return Vrai si la clé est présente sinon faux.
   */
   bool contains (const Key &key) const
   {
      size_t pos = super::getKey(key, hmap.size());

      return std::find(hmap[pos].begin(), hmap[pos].end(), key) != hmap[pos].end();
   }

   /**
    * @brief Supprime la clé de la table de hachage si elle est présente, sans effet sinon.
    * @param key Clé a retirer.
    */
   void erase (const Key &key)
   {
      size_t pos = super::getKey(key, hmap.size());

      auto it = std::find(hmap[pos].begin(), hmap[pos].end(), key);
      if(it != hmap[pos].end())
      {
         hmap[pos].erase(it);
         --super::nbElem;
      }

      super::checkDistribution(DELETION);
   }

   /**
    * @return Retourne la taille de la table de hachage.
    */
   size_t tableSize () const
   {
      return hmap.size();
   }

private:

   /**
    * @brief Redimensionne la table de hachage avec la nouvelle taille.
    * @param newSize Nouvelle taille à appliquer à la table de hachage.
    */
   void resize (size_t newSize)
   {
      std::vector<std::list<Key>> tempHmap = std::vector<std::list<Key>>{newSize};
      hmap.swap(tempHmap);
      super::nbElem = 0;

      super::mustCheckContains = false;
      for (int i = 0; i < tempHmap.size(); ++i)
      {
         for (const Key& key : tempHmap[i])
         {
            insert(key);
         }
      }
      super::mustCheckContains = true;
   }
};

#endif //ASD2_LABS_2020_HASHMAPCHAIN_H
