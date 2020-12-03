//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 02 Dec 2020
//

#ifndef ASD2_LABS_2020_HASHMAPLINEARSAMPLE_H
#define ASD2_LABS_2020_HASHMAPLINEARSAMPLE_H

#include "HashMapCommon.h"
#include <vector>    // std::vector<std::list<Key>>

/*
 * @Brief Classe définissant une table de hachage selon le principe de sondage linéaire.
 *        La fonction std::hash doit être définie pour le type de Key sinon passer
 *        une fonction personnalisé. De même, == doit être défini pour Key.
 */
template<class Key, class Hash = std::hash<Key>, class Pred = std::equal_to<Key>>
class HashMapLinearSample : public HashMapCommon<Key, Hash, Pred>
{
private:
   typedef HashMapCommon<Key, Hash, Pred> super;

   std::vector<const Key *> hmap;

public:

   /**
    * @brief Constructeur. Dimensionne la table de hachage selon length.
    * @param length Par défaut vaut 1.
    */
   HashMapLinearSample (size_t length = 1) : HashMapCommon<Key, Hash, Pred>(0.125, 0.5)
   {
      hmap.resize(length);
   }

   /**
    * @brief Destructeur. Réallou la mémoire associé a la table de hachage.
    */
   ~HashMapLinearSample()
   {
      for (int i = 0; i < hmap.size(); ++i)
      {
         if (hmap[i] != nullptr)
         {
            insert(*hmap[i]);
            delete hmap[i];
            hmap[i] = nullptr;
         }
      }
   }

   /**
    * @brief Permet d'ajouter la clé dans la table de hachage, sans effet si présente.
    * @param key Clé à ajouter.
    */
   void insert (const Key &key)
   {
      size_t pos = super::getPos(key, hmap.size());

      // We look for next empty cell
      if (!contains(key))
      {
         while (hmap[pos] != nullptr)
         {
            pos = (pos + 1) % hmap.size();
         }

         hmap[pos] = new Key(key);
         ++super::nbElem;
      }

      super::checkDistribution(hmap.size());
   }

   /**
    * @brief Vérifie si la clé est contenue dans la table de hachage.
    * @param key Clé à vérifier.
    * @return Vrai si la clé est présente sinon faux.
    */
   bool contains (const Key &key)
   {
      if (find(key) > 0)
      { return true; }

      return false;
   }

   /**
    * @brief Supprime la clé de la table de hachage si elle est présente, sans effet sinon.
    * @param key Clé a retirer.
    */
   void erase (const Key &key)
   {
      int pos = find(key);
      if (pos >= 0)
      {
         delete hmap[pos];
         hmap[pos] = nullptr;
         --super::nbElem;
      }

      super::checkDistribution(hmap.size());
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
    * @Brief Calcule la position d'une clé dans la table de hachage.
    * @param key Clé a rechercher
    * @return Retourne la position de la clé si existante sinon -1.
    */
   int find (const Key &key)
   {
      size_t pos = super::getPos(key, hmap.size());

      while (hmap[pos] != nullptr && pos < hmap.size())
      {
         if (super::pred(*hmap[pos], key))
         {
            return pos;
         }
         ++pos;
      }

      return -1;
   }

   /**
    * @brief Redimensionne la table de hachage avec la nouvelle taille.
    * @param newSize Nouvelle taille à appliquer à la table de hachage.
    */
   void resize (size_t newSize)
   {
      std::vector<const Key *> tempHmap = std::vector<const Key *>{newSize};
      hmap.swap(tempHmap);
      super::nbElem = 0;

      super::canBeResized = false;

      for (int i = 0; i < tempHmap.size(); ++i)
      {
         if (tempHmap[i] != nullptr)
         {
            insert(*tempHmap[i]);
            delete tempHmap[i];
            tempHmap[i] = nullptr;
         }
      }

      super::canBeResized = true;
   }
};

#endif //ASD2_LABS_2020_HASHMAPLINEARSAMPLE_H
