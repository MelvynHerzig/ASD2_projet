//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 09 Dec 2020
//

#ifndef ASD2_LABS_2020_ADAPTATERCORRECTOR_H
#define ASD2_LABS_2020_ADAPTATERCORRECTOR_H

#include <stdlib.h>

/**
 * Le but de cette classe est d'adapter les structures de la STL à l'interface demandée
 * par Corrector.h. Le container utilisé avec Corrector doit fournir les fonctions
 * - insert (const T& key)
 * - contains(const T& elem) const
 * - erase (const T& elem)
 * - size() const
 * Or les containers de la STL ne fournissent pas contains(). Dès lors cette classe
 * offre la possibilité de les utiliser quand même en utilisant find.
 *
 * Ainsi pour pouvoir utiliser cette classe "adaptater" le container doit avoir
 * les fonctions:
 * - insert (const T& key)
 * - find(const T& elem) const
 * - erase (const T& elem)
 * - size() const
 * @tparam T Type du container
 * @tparam Container Container employé.
 */
template<class T, class Container>
class AdaptaterCorrector
{
protected:

   Container container;

public:

   /*
    * @brief Constructeur par défaut
    */
   AdaptaterCorrector (){}

   /**
    * @brief Ajoute l'élément dans le container. Appel à insert.
    * @param key Clé à ajouter
    */
   void insert (const T& key)
   {
      container.insert(key);
   }

   /**
    * @brief Vérifie si l'élément est dans le container. Appel à find.
    * @param elem Élàment à vérifier.
    * @return Vrai si présent sinon faux.
    */
   bool contains(const T& elem) const
   {
      return container.find(elem) != container.end();
   }

   /**
    * @brief Supprime l'élément du container. Appel à erase.
    * @param elem Element à supprimer
    */
   void erase (const T& elem)
   {
      container.erase(elem);
   }

   /**
    * @return Retourne le nombre d'éléments dans le container. Appel à size.
    */
   size_t size () const
   {
      return container.size();
   }
};

#endif //ASD2_LABS_2020_ADAPTATERCORRECTOR_H
