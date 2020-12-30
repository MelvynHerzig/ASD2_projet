#include "catch.hpp"
#include "../hashMapChain.h"
#include "../hashMapLinearSample.h"

using namespace std;

#define MAX_CHAIN_INSERT 8.0
#define MAX_LINEAR_INSERT 0.5
#define MIN_CHAIN_INSERT 2.0
#define MIN_LINEAR_INSERT 0.125
#define MIN_TABLE_SIZE 1

TEST_CASE("Tests", "[hashmap]")
{
   HashMapChain<size_t> hashMapChainInt;
   HashMapChain<string> hashMapChainString;
   HashMapLinearSample<size_t> hashMapLinearSampleInt;
   HashMapLinearSample<string> hashMapLinearSampleString;

    SECTION("Empty hashMap")
    {
       REQUIRE(hashMapChainInt.size() == 0);
       REQUIRE(hashMapChainString.size() == 0);
       REQUIRE(hashMapLinearSampleInt.size() == 0);
       REQUIRE(hashMapLinearSampleString.size() == 0);
    }

   SECTION("Insert 1 element")
   {
       hashMapChainInt.insert(1);
       REQUIRE(hashMapChainInt.contains(1));
       REQUIRE(hashMapChainInt.size() == 1);

       hashMapChainString.insert("test");
       REQUIRE(hashMapChainString.contains("test"));
       REQUIRE(hashMapChainString.size() == 1);

       hashMapLinearSampleInt.insert(1);
       REQUIRE(hashMapLinearSampleInt.contains(1));
       REQUIRE(hashMapLinearSampleInt.size() == 1);

       hashMapLinearSampleString.insert("test");
       REQUIRE(hashMapLinearSampleString.contains("test"));
       REQUIRE(hashMapLinearSampleString.size() == 1);
   }

   SECTION("Insert 1 element already in hashMap")
   {
       hashMapChainInt.insert(1);
       REQUIRE(hashMapChainInt.contains(1));
       REQUIRE(hashMapChainInt.size() == 1);

       hashMapChainString.insert("test");
       REQUIRE(hashMapChainString.contains("test"));
       REQUIRE(hashMapChainString.size() == 1);

       hashMapLinearSampleInt.insert(1);
       REQUIRE(hashMapLinearSampleInt.contains(1));
       REQUIRE(hashMapLinearSampleInt.size() == 1);

       hashMapLinearSampleString.insert("test");
       REQUIRE(hashMapLinearSampleString.contains("test"));
       REQUIRE(hashMapLinearSampleString.size() == 1);

   }

   SECTION("Erase 1 element")
   {
       hashMapChainInt.erase(1);
       REQUIRE(!hashMapChainInt.contains(1));
       REQUIRE(hashMapChainInt.size() == 0);

       hashMapChainString.erase("test");
       REQUIRE(!hashMapChainString.contains("test"));
       REQUIRE(hashMapChainString.size() == 0);

       hashMapLinearSampleInt.erase(1);
       REQUIRE(!hashMapLinearSampleInt.contains(1));
       REQUIRE(hashMapLinearSampleInt.size() == 0);

       hashMapLinearSampleString.erase("test");
       REQUIRE(!hashMapLinearSampleString.contains("test"));
       REQUIRE(hashMapLinearSampleString.size() == 0);
   }

   SECTION("Erase non existant element")
   {
       REQUIRE(!hashMapChainInt.contains(1));
       hashMapChainInt.erase(1);
       REQUIRE(hashMapChainInt.size() == 0);

       REQUIRE(!hashMapChainString.contains("test"));
       hashMapChainString.erase("test");
       REQUIRE(hashMapChainString.size() == 0);

       REQUIRE(!hashMapLinearSampleInt.contains(1));
       hashMapLinearSampleInt.erase(1);
       REQUIRE(hashMapLinearSampleInt.size() == 0);

       REQUIRE(!hashMapLinearSampleString.contains("test"));
       hashMapLinearSampleString.erase("test");
       REQUIRE(hashMapLinearSampleString.size() == 0);
   }

   SECTION("Insert elements")
   {
       for (int i : {2, 4, 6, 8, 10})
       {
          hashMapChainInt.insert(i);
          hashMapChainString.insert(" test " + to_string(i));
          hashMapLinearSampleInt.insert(i);
          hashMapLinearSampleString.insert(" test " + to_string(i));
       }

       for (int i : {2, 4, 6, 8, 10})
       {
          REQUIRE(hashMapChainInt.contains(i));
          REQUIRE(hashMapChainString.contains(" test " + to_string(i)));
          REQUIRE(hashMapLinearSampleInt.contains(i));
          REQUIRE(hashMapLinearSampleString.contains(" test " + to_string(i)));
       }

       for (int i : {1, 3, 5, 7, 9})
       {
          REQUIRE(!hashMapChainInt.contains(i));
          REQUIRE(!hashMapChainString.contains(" test " + to_string(i)));
          REQUIRE(!hashMapLinearSampleInt.contains(i));
          REQUIRE(!hashMapLinearSampleString.contains(" test " + to_string(i)));
       }

       REQUIRE(hashMapChainInt.size() == 5);
       REQUIRE(hashMapChainString.size() == 5);
       REQUIRE(hashMapLinearSampleInt.size() == 5);
       REQUIRE(hashMapLinearSampleString.size() == 5);
   }

   SECTION("Erase all elements")
   {
      for (int i : {2, 4, 6, 8, 10})
      {
         hashMapChainInt.erase(i);
         hashMapChainString.erase(" test " + to_string(i));
         hashMapLinearSampleInt.erase(i);
         hashMapLinearSampleString.erase(" test " + to_string(i));
      }

      for (int i : {2, 4, 6, 8, 10})
      {
         REQUIRE(!hashMapChainInt.contains(i));
         REQUIRE(!hashMapChainString.contains(" test " + to_string(i)));
         REQUIRE(!hashMapLinearSampleInt.contains(i));
         REQUIRE(!hashMapLinearSampleString.contains(" test " + to_string(i)));
      }

      REQUIRE(hashMapChainInt.size() == 0);
      REQUIRE(hashMapChainString.size() == 0);
      REQUIRE(hashMapLinearSampleInt.size() == 0);
      REQUIRE(hashMapLinearSampleString.size() == 0);
   }

   SECTION("Resizing hashmap cases")
   {
      for (int i = 0; i < 20; ++i)
      {
         hashMapChainInt.insert(i);
         hashMapChainString.insert(" test " + to_string(i));
         hashMapLinearSampleInt.insert(i);
         hashMapLinearSampleString.insert(" test " + to_string(i));

         double rapportChainInt = (double) hashMapChainInt.size() / (double) hashMapChainInt.tableSize();
         double rapportChainString = (double) hashMapChainString.size() / (double) hashMapChainString.tableSize();
         double rapportLinearInt = (double) hashMapLinearSampleInt.size() / (double) hashMapLinearSampleInt.tableSize();
         double rapportLinearString = (double) hashMapLinearSampleString.size() / (double) hashMapLinearSampleString.tableSize();

         REQUIRE(rapportChainInt < MAX_CHAIN_INSERT);
         REQUIRE(rapportChainString < MAX_CHAIN_INSERT);
         REQUIRE(rapportLinearInt < MAX_LINEAR_INSERT);
         REQUIRE(rapportLinearString < MAX_LINEAR_INSERT);
      }

      for (int i = 0; i < 20; ++i)
      {
         // Rien ne sert de continuer à vérifier le rapport des tailles N / M si M est arrivé à sa taille minimale = 1
         if (hashMapChainInt.tableSize() == MIN_TABLE_SIZE) break;

         hashMapChainInt.erase(i);
         hashMapChainString.erase(" test " + to_string(i));
         hashMapLinearSampleInt.erase(i);
         hashMapLinearSampleString.erase(" test " + to_string(i));

         double rapportChainInt = (double) hashMapChainInt.size() / (double) hashMapChainInt.tableSize();
         double rapportChainString = (double) hashMapChainString.size() / (double) hashMapChainString.tableSize();
         double rapportLinearInt = (double) hashMapLinearSampleInt.size() / (double) hashMapLinearSampleInt.tableSize();
         double rapportLinearString = (double) hashMapLinearSampleString.size() / (double) hashMapLinearSampleString.tableSize();

         REQUIRE(rapportChainInt > MIN_CHAIN_INSERT);
         REQUIRE(rapportChainString > MIN_CHAIN_INSERT);
         REQUIRE(rapportLinearInt > MIN_LINEAR_INSERT);
         REQUIRE(rapportLinearString > MIN_LINEAR_INSERT);
      }
   }
}
