#include "catch.hpp"
#include "../HashMapWrapper.h"

using namespace std;

// TODO: faire avec plusieurs types?
// TODO: exceptions levées? -> déjà raison?
// TODO: trouver un moyen de créer des collisions (si possible)

TEST_CASE("Tests", "[hashmap]")
{
    HashMapWrapper<int> hashMapWrapper;

    SECTION("Empty hashMap")
    {
        REQUIRE(hashMapWrapper.size() == 0);
    }

   SECTION("Insert 1 element")
   {
       hashMapWrapper.insert(1);
       REQUIRE(hashMapWrapper.contains(1));
       REQUIRE(hashMapWrapper.size() == 1);
   }

   SECTION("Insert 1 element already in hashmap")
   {
      hashMapWrapper.insert(1);
      REQUIRE(hashMapWrapper.contains(1));
      REQUIRE(hashMapWrapper.size() == 1);
   }

   SECTION("Erase 1 element")
   {
       hashMapWrapper.erase(1);
       REQUIRE(hashMapWrapper.contains(1));
       REQUIRE(hashMapWrapper.size() == 0);
   }

   SECTION("Erase non existant element")
   {
       REQUIRE(!hashMapWrapper.contains(1));
       hashMapWrapper.erase(1);
       REQUIRE(hashMapWrapper.size() == 0);
   }

   SECTION("Insert positive elements")
   {
       for (int i : {2, 4, 6, 8, 10})
       {
          hashMapWrapper.insert(i);
       }

       for (int i : {2, 4, 6, 8, 10})
       {
          REQUIRE(hashMapWrapper.contains(i));
       }

       for (int i : {1, 3, 5, 7, 9})
       {
          REQUIRE(!hashMapWrapper.contains(i));
       }

       REQUIRE(hashMapWrapper.size() == 5);
   }


   SECTION("Erase all positive elements")
   {
       for (int i : {2, 4, 6, 8, 10})
       {
          hashMapWrapper.erase(i);
       }

       for (int i : {2, 4, 6, 8, 10})
       {
          REQUIRE(!hashMapWrapper.contains(i));
       }

       REQUIRE(hashMapWrapper.size() == 0);
   }

   SECTION("Insert negative elements")
   {
      for (int i : {-2, -4, -6, -8, -10})
      {
         hashMapWrapper.insert(i);
      }

      for (int i : {-2, -4, -6, -8, -10})
      {
         REQUIRE(hashMapWrapper.contains(i));
      }

      for (int i : {-1, -3, -5, -7, -9})
      {
         REQUIRE(!hashMapWrapper.contains(i));
      }

      REQUIRE(hashMapWrapper.size() == 5);
   }

   SECTION("Erase all negative elements")
   {
      for (int i : {-2, -4, -6, -8, -10})
      {
         hashMapWrapper.erase(i);
      }

      for (int i : {-2, -4, -6, -8, -10})
      {
         REQUIRE(!hashMapWrapper.contains(i));
      }

      REQUIRE(hashMapWrapper.size() == 0);
   }

}
