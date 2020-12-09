//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 02 Dec 2020
//

#ifndef ASD2_LABS_2020_HASHMAPCHAIN_H
#define ASD2_LABS_2020_HASHMAPCHAIN_H

#include "HashMapCommon.h"
#include <list>      // std::list<Key>
#include <vector>    // std::vector<std::list<Key>>

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
   typedef typename std::list<Key>::const_iterator CListIterator;

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
    * @brief Permet d'ajouter la clé dans la table de hachage, sans effet si présente.
    * @param key Clé à ajouter.
    */
   void insert (const Key &key)
   {
      size_t pos = super::getPos(key, hmap.size());
      if (!contains(key))
      {
         hmap[pos].push_back(key);
         ++super::nbElem;
      }

      super::checkDistribution(hmap.size(), INSERTION);
   }

   /**
   * @brief Vérifie si la clé est contenue dans la table de hachage.
   * @param key Clé à vérifier.
   * @return Vrai si la clé est présente sinon faux.
   */
   bool contains (const Key &key)
   {
      size_t pos = super::getPos(key, hmap.size());

      CListIterator it = find(key);
      if (it != hmap[pos].end())
      { return true; }

      return false;
   }

   /**
    * @brief Supprime la clé de la table de hachage si elle est présente, sans effet sinon.
    * @param key Clé a retirer.
    */
   void erase (const Key &key)
   {
      size_t pos = super::getPos(key, hmap.size());

      CListIterator it = find(key);
      if (it != hmap[pos].end())
      {
         hmap[pos].erase(it);
         --super::nbElem;
      }

      super::checkDistribution(hmap.size(), DELETION);
   }

   /**
    * @return Retourne la taille de la table de hachage.
    */
   size_t tableSize ()
   {
      return hmap.size();
   }

private:

   /**
   * @Brief Calcule la position d'une clé dans la table de hachage puis dans la liste.
   * @param key Clé a rechercher
   * @return Retourne un itérateur sur la position de la clé sinon nullptr,
   */
   CListIterator find (const Key &key)
   {
      size_t pos = super::getPos(key, hmap.size());

      for (auto it = hmap[pos].begin(); it != hmap[pos].end(); ++it)
      {
         if (super::pred(*it, key))
         { return it; }
      }

      return hmap[pos].end();
   }

   /**
    * @brief Redimensionne la table de hachage avec la nouvelle taille.
    * @param newSize Nouvelle taille à appliquer à la table de hachage.
    */
   void resize (size_t newSize)
   {
      std::vector<std::list<Key>> tempHmap = std::vector<std::list<Key>>{newSize};
      hmap.swap(tempHmap);
      super::nbElem = 0;

      for (int i = 0; i < tempHmap.size(); ++i)
      {
         for (const Key &key : tempHmap[i])
         {
            insert(key);
         }
      }
   }

};

#endif //ASD2_LABS_2020_HASHMAPCHAIN_H
