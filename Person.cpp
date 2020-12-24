//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 09 Dec 2020
//

#include "Person.h"

bool Person::operator== (const Person &other) const
{
   return this->name == other.name &&
          this->firstname == other.firstname &&
          this->gender == other.gender &&
          this->birthday == other.birthday;
}
