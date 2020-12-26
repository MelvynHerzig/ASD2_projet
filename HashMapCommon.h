/*
 * Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 02 Dec 2020
 */

#ifndef HASHMAP_WRAPPER_H
#define HASHMAP_WRAPPER_H

#include <functional> // hash<Key>, equal_to<Key>
#include <cmath>      // std::ceil

enum hash_operation{ INSERTION, DELETION};

/*
 * @brief Classe englobante des methodes communes a définir et attributs communs
 *        aux classe HashMapLinearSample et HashMapChain.
 *        La fonction std::hash doit être définie pour le type de Key sinon passer
 *        une fonction personnalisé. De même, == doit être défini pour Key.
 */
template<class Key, class Hash = std::hash<Key>, class Pred = std::equal_to<Key>>
class HashMapCommon
{
protected:

   Hash hash;  // Fonction de hachage
   Pred pred;  // Fonction d'égalité

   size_t nbElem;     // # d'éléments stockés dans la table de hachage

   const double REDUCT_AT;  // Ratio au dessous du quel réduir la taille de la table
   const double AUGMENT_AT; // Ratio au dessus du quel augmenter la taille de la table.

   bool mustCheckContains; // Permet de ne pas appeler contains lors de l'insertion si true
                           // Utilisé lors du redimensionnement

   /*
    * @brief Constructeur par défaut
    */
   HashMapCommon (double reduct, double augment) : REDUCT_AT(reduct), AUGMENT_AT(augment)
   {
      nbElem = 0;
   }

   /**
    * @brief permet d'ajouter la clé dans la table de hachage, sans effet si présent.
    * @param key Clé à ajouter
    */
   virtual void insert (const Key &key) = 0;

   /**
    * @brief Vérifie si la clé est contenue dans la table de hachage.
    * @param key Clé à vérifier.
    * @return Vrai si la clé est présente sinon faux.
    */
   virtual bool contains (const Key &key) const = 0;

   /**
    * @brief Supprime la clé de la table de hachage si elle est présente, sans effet sinon.
    * @param key Clé a retirer.
    */
   virtual void erase (const Key &key) = 0;

   /**
    * @return Retourne le nombre d'éléments de la table de hachage.
    */
   size_t size () const
   {
      return nbElem;
   }

   /**
    * @return Retourne la taille de la table de hachage.
    */
   virtual size_t tableSize() const = 0;

   /**
    * @Brief Pour une longueur de hashMap donnée, spécifie ou insérer la clé.
    * @param key Clé à insérer.
    * @param hmapSize Longueur de la hmapAssocié.
    * @return Position correspondant au hachage dans la hmap associée.
    */

   size_t getKey (const Key &key, size_t hmapSize) const
   {
      return hash(key) % hmapSize;
   }

   /**
    * @brief Pour une table de hachage, vérifie si elle doit être redimensionnée.
    *        Appel resize si tel est le cas.
    */
   void checkDistribution (hash_operation operation)
   {
      size_t hmapsize = tableSize();
      double ratio = (double) nbElem / (double) hmapsize;

      if (operation == INSERTION && ratio >= AUGMENT_AT)
      {
         resize(hmapsize * 2);
      }

      if (operation == DELETION && ratio <= REDUCT_AT)
      {
         resize(std::ceil((double) hmapsize / (double) 2));
      }
   }

   /**
    * @brief Redimensionne la table de hachage avec la nouvelle taille.
    * @param newSize Nouvelle taille à appliquer à la table de hachage.
    */
   virtual void resize (size_t newSize) = 0;

};

#endif //HASHMAP_WRAPPER_H
