#include "catch.hpp"
#include "../TSTreeWords.h"

using namespace std;


TEST_CASE("Ternary Search Tree tests", "[tst]")
{
   TSTreeWords tree;

   SECTION("Empty tree")
   {
      REQUIRE(tree.size() == 0);
   }

   SECTION("Insertions and contains")
   {
      tree.insert("aaa");
      tree.insert("baa");
      tree.insert("aba");
      tree.insert("aab");

      REQUIRE(tree.size() == 4);

      REQUIRE(tree.contains("aaa"));
      REQUIRE(tree.contains("baa"));
      REQUIRE(tree.contains("aba"));
      REQUIRE(tree.contains("aab"));

      REQUIRE(!tree.contains("bbb"));

   }

   SECTION("Insertions and heights")
   {
      tree.insert("a");

      REQUIRE(tree.height() == 0); // Right et Left n'existent pas

      tree.insert("b");

      REQUIRE(tree.height() == 1); // Right = 0 -> (0 + 1)

      tree.insert("c");
      // L'arbre est rebalancé, b devient la racine
      REQUIRE(tree.height() == 1); // Right = 0, Left = 0, MAX (Left et Right) = 0 -> (0 + 1)

      tree.insert("d");

      REQUIRE(tree.height() == 2); // Right = 1, Left = 0, MAX (Left et Right) = 1 -> (1 + 1)

      tree.insert("e");
      // l'arbre est rebalancé, c devient la racine
      REQUIRE(tree.height() == 2); // Right = 1, Left = 1, MAX (Left et Right) = 1 -> (1 + 1)

      tree.insert("f");
      // l'arbre est rebalancé, d devient la racine
      REQUIRE(tree.height() == 2); // Right = 1, Left = 1, MAX (Left et Right) = 1 -> (1 + 1)

      tree.insert("g");

      REQUIRE(tree.height() == 2); // Right = 1, Left = 1, MAX (Left et Right) = 1 -> (1 + 1)

      tree.insert("h");

      REQUIRE(tree.height() == 3);
   }

   SECTION("Insertions and erases")
   {
      tree.insert("aaa");
      tree.insert("baa");
      tree.insert("aba");
      tree.insert("aab");

      REQUIRE(tree.size() == 4);

      tree.erase("baa");

      REQUIRE(tree.size() == 3);

      tree.erase("aab");

      REQUIRE(tree.size() == 2);

      REQUIRE(!tree.contains("aab"));
      REQUIRE(!tree.contains("baa"));

      REQUIRE(tree.contains("aaa"));
      REQUIRE(tree.contains("aba"));
   }
}
