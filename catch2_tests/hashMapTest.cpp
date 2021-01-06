/*
 * Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 02 Dec 2020
 */

#include "catch.hpp"
#include "../hashMapChain.h"
#include "../hashMapLinearSample.h"

using namespace std;

#define MAX_CHAIN_INSERT 8.0
#define MAX_LINEAR_INSERT 0.5
#define MIN_CHAIN_INSERT 2.0
#define MIN_LINEAR_INSERT 0.125
#define MIN_TABLE_SIZE 1

TEMPLATE_TEST_CASE("Tests for hashmap<size_t>", "[hashmap]", HashMapLinearSample<size_t>, HashMapChain<size_t>)
{

   TestType hashmap = TestType();

   SECTION("Empty hashMap")
   {
      REQUIRE(hashmap.size() == 0);
   }

   SECTION("Insert 1 element")
   {
      hashmap.insert(1);
      REQUIRE(hashmap.contains(1));
      REQUIRE(hashmap.size() == 1);
   }

   SECTION("Insert 1 element already in hashMap")
   {
      hashmap.insert(1);
      REQUIRE(hashmap.contains(1));
      REQUIRE(hashmap.size() == 1);
   }

   SECTION("Erase 1 element")
   {
      hashmap.erase(1);
      REQUIRE(!hashmap.contains(1));
      REQUIRE(hashmap.size() == 0);
   }

   SECTION("Erase non existant element")
   {
      REQUIRE(!hashmap.contains(1));
      hashmap.erase(1);
      REQUIRE(hashmap.size() == 0);
   }

   SECTION("Insert elements")
   {
      for (int i : {2, 4, 6, 8, 10})
      {
         hashmap.insert(i);
      }

      for (int i : {2, 4, 6, 8, 10})
      {
         REQUIRE(hashmap.contains(i));
      }

      for (int i : {1, 3, 5, 7, 9})
      {
         REQUIRE(!hashmap.contains(i));
      }

      REQUIRE(hashmap.size() == 5);
   }

   SECTION("Erase all elements")
   {
      for (int i : {2, 4, 6, 8, 10})
      {
         hashmap.erase(i);
      }

      for (int i : {2, 4, 6, 8, 10})
      {
         REQUIRE(!hashmap.contains(i));
      }

      REQUIRE(hashmap.size() == 0);
   }
}

TEMPLATE_TEST_CASE("Tests for hashmap<string>", "[hashmap]", HashMapLinearSample<string>, HashMapChain<string>)
{

   TestType hashmap = TestType();

   SECTION("Empty hashMap")
   {
      REQUIRE(hashmap.size() == 0);
   }

   SECTION("Insert 1 element")
   {
      hashmap.insert("test");
      REQUIRE(hashmap.contains("test"));
      REQUIRE(hashmap.size() == 1);
   }

   SECTION("Insert 1 element already in hashMap")
   {
      hashmap.insert("test");
      REQUIRE(hashmap.contains("test"));
      REQUIRE(hashmap.size() == 1);
   }

   SECTION("Erase 1 element")
   {
      hashmap.erase("test");
      REQUIRE(!hashmap.contains("test"));
      REQUIRE(hashmap.size() == 0);
   }

   SECTION("Erase non existant element")
   {
      REQUIRE(!hashmap.contains("test"));
      hashmap.erase("test");
      REQUIRE(hashmap.size() == 0);
   }

   SECTION("Insert elements")
   {
      for (int i : {2, 4, 6, 8, 10})
      {
         hashmap.insert(" test " + to_string(i));
      }

      for (int i : {2, 4, 6, 8, 10})
      {
         REQUIRE(hashmap.contains(" test " + to_string(i)));
      }

      for (int i : {1, 3, 5, 7, 9})
      {
         REQUIRE(!hashmap.contains(" test " + to_string(i)));
      }

      REQUIRE(hashmap.size() == 5);
   }

   SECTION("Erase all elements")
   {
      for (int i : {2, 4, 6, 8, 10})
      {
         hashmap.erase(" test " + to_string(i));
      }

      for (int i : {2, 4, 6, 8, 10})
      {
         REQUIRE(!hashmap.contains(" test " + to_string(i)));
      }

      REQUIRE(hashmap.size() == 0);
   }
}

TEST_CASE("Tests for hashmap size", "[hashmap]")
{
   HashMapChain<size_t> hashMapChainInt;
   HashMapChain<string> hashMapChainString;
   HashMapLinearSample<size_t> hashMapLinearSampleInt;
   HashMapLinearSample<string> hashMapLinearSampleString;

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
