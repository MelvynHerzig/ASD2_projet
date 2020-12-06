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
         using std::size_t;
         using std::hash;
         using std::string;
         size_t hashval = 17;
         hashval = 31 * hashval + hash<string>()(p.name);
         hashval = 31 * hashval + hash<string>()(p.firstname);
         hashval = 31 * hashval + hash<string>()(p.gender);
         hashval = 31 * hashval + hash<string>()(p.birthday);
         return hashval;
      }
   };
}


#endif //ASD2_LABS_2020_PERSON_H
