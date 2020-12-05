//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 02 Dec 2020
//

#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include "HashMapChain.h"
#include "HashMapLinearSample.h"

using namespace std;

int main ()
{
//   HashMapChain<int> hm {8};
//
//   cout << "taille " << hm.size() << endl;
//
//   cout<< "Ajout de cle 5 " << endl;
//   hm.insert(5);
//
//   cout << "taille " << hm.size() << endl;
//
//   cout << boolalpha;
//   cout << "Est ce que la map contient 5 " << hm.contains(5) << endl;
//   cout << "Est ce que la map contient 4 " << hm.contains(4) << endl;
//
//   cout << "Suppression de 5 " << endl;
//   hm.erase(5);
//
//   cout << "taille " << hm.size() << endl;
//
//   for (int i = 0; i < 16; ++i)
//   {
//      cout << "nb Elem " << hm.size() << endl;
//      cout << "taille de la table " << hm.tableSize() << endl;
//      hm.insert(i);
//   }

   HashMapLinearSample<int> hm;
   for (int i = 0; i < 4; ++i)
   {
      cout << "nb Elem " << hm.size() << endl;
      cout << "taille de la table " << hm.tableSize() << endl;
      hm.insert(i);
      cout <<  endl;
   }

   for (int i = 0; i < 3; ++i)
   {
      cout << "nb Elem " << hm.size() << endl;
      cout << "taille de la table " << hm.tableSize() << endl;
      hm.erase(i);
      cout <<  endl;
   }

   cout << "nb Elem " << hm.size() << endl;
   cout << "taille de la table " << hm.tableSize() << endl;
   return 0;
}