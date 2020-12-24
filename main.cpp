//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 02 Dec 2020
//

#include <iostream>      // std::cout, std::endl
#include <set>           // std::set
#include <unordered_set> // std::undordered_set
#include "HashMapChain.h"
#include "HashMapLinearSample.h"
#include "TSTreeWords.h"
#include "Corrector.h"

using namespace std;

int main ()
{

//--------------------------------------------------------------------------------
//                              CHOIX CONTAINER
//--------------------------------------------------------------------------------

   // Changer le typedef pour changer le type de container utilisé. /!\ Décommenter 1 seulement.

   //typedef HashMapChain<string> Container;
   //typedef HashMapLinearSample<string> Container;
   typedef set<string> Container;
   //typedef unordered_set<string> Container;
   //typedef TSTreeWords Container;

//--------------------------------------------------------------------------------
//                             CHOIX FICHIERS
//--------------------------------------------------------------------------------
   // Changer la localisation du fichier dictionnaire.
   string dictionary = "..\\data\\dictionary.txt";

   // Changer la localisation du fichier à analyser. /!\  Décommenter 1 seulement.
   //string input = "..\\data\\input_lates.txt";
   //string input = "..\\data\\input_simple.txt";
   //string input = "..\\data\\input_wikipedia.txt";
   string input = "..\\data\\input_sh.txt";

//--------------------------------------------------------------------------------
//                             EXECUTION
//--------------------------------------------------------------------------------
   Corrector<Container> corrector(dictionary);
   corrector.correctFile(input);

   return 0;
}