//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 09 Dec 2020
//

#ifndef ASD2_LABS_2020_PERSON_H
#define ASD2_LABS_2020_PERSON_H

#include <string>


class Person
{
public:
   std::string name;
   std::string firstname;
   std::string gender;
   std::string birthday;

   /**
    * @brief Compare si la personne est égale à other.
    * @param other Personne à comparer à l'objet courrant.
    * @return Vrai si les objets sont égaux au niveau des attributs.
    */
   bool operator== (const Person &other) const;
};

namespace std
{
   /**
    * @brief surcharge de la fonction de hachage std pour une personne.
    */
   template <>
   struct hash<Person>
   {
      size_t operator()(const Person& p) const
      {
         const unsigned NB_PREMIER = 31;
         using std::size_t;
         using std::hash;
         using std::string;
         size_t hashval = 17;
         hashval = NB_PREMIER * hashval + hash<string>()(p.name);
         hashval = NB_PREMIER * hashval + hash<string>()(p.firstname);
         hashval = NB_PREMIER * hashval + hash<string>()(p.gender);
         hashval = NB_PREMIER * hashval + hash<string>()(p.birthday);
         return hashval;
      }
   };
}


#endif //ASD2_LABS_2020_PERSON_H
