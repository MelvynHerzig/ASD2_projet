//
// Created by melvy on 06/12/2020.
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

   bool operator== (const Person &other) const;
};

namespace std
{
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
