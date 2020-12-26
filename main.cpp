//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 02 Dec 2020
//

#include <iostream>      // std::cout, std::endl
#include <set>           // std::set
#include <unordered_set> // std::undordered_set
#include "AdaptaterCorrector.h"
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
   //typedef AdaptaterCorrector<string, set<string>> Container;            // Adaptation de std::set
   //typedef AdaptaterCorrector<string, unordered_set<string>> Container;  // Adaptation de std::unordered_set
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
   //string input = "..\\data\\input_sh.txt";

//--------------------------------------------------------------------------------
//                             EXECUTION
//--------------------------------------------------------------------------------
   //Corrector<Container> corrector(dictionary);
   //corrector.correctFile(input);


   {
      cout << "----------------------------------------------------------\n" <<
              "                      CUSTOM HMAP CHAIN\n" <<
              "----------------------------------------------------------\n" << endl;

      typedef HashMapChain<string> Container;

      cout << "******* lates *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_lates.txt");
      }

      cout << "******* simple *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_simple.txt");
      }

      cout << "******* wikipedia *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_wikipedia.txt");
      }

      cout << "******* sh *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_sh.txt");
      }
   }

   {
      cout << "----------------------------------------------------------\n" <<
              "                      CUSTOM HMAP SONDAGE\n" <<
              "----------------------------------------------------------\n" << endl;

      typedef HashMapLinearSample<string> Container;

      cout << "******* lates *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_lates.txt");
      }

      cout << "******* simple *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_simple.txt");
      }

      cout << "******* wikipedia *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_wikipedia.txt");
      }

      cout << "******* sh *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_sh.txt");
      }
   }

   {
      cout << "----------------------------------------------------------\n" <<
              "                      STANDARD SET\n" <<
              "----------------------------------------------------------\n" << endl;

      typedef AdaptaterCorrector<string, set<string>> Container;

      cout << "******* lates *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_lates.txt");
      }

      cout << "******* simple *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_simple.txt");
      }

      cout << "******* wikipedia *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_wikipedia.txt");
      }

      cout << "******* sh *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_sh.txt");
      }
   }

   {
      cout << "----------------------------------------------------------\n" <<
              "                      STANDARD UNORDERED SET\n" <<
              "----------------------------------------------------------\n" << endl;

      typedef AdaptaterCorrector<string, unordered_set<string>> Container;

      cout << "******* lates *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_lates.txt");
      }

      cout << "******* simple *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_simple.txt");
      }

      cout << "******* wikipedia *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_wikipedia.txt");
      }

      cout << "******* sh *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_sh.txt");
      }
   }

   {
      cout << "----------------------------------------------------------\n" <<
              "                      CUSTOM TERNARY SEARCH TRIE\n " <<
              "----------------------------------------------------------\n" << endl;

      typedef TSTreeWords Container;

      cout << "******* lates *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_lates.txt");
      }

      cout << "******* simple *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_simple.txt");
      }

      cout << "******* wikipedia *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_wikipedia.txt");
      }

      cout << "******* sh *******" << endl;
      {
         Corrector<Container> corrector(dictionary);
         corrector.correctFile("..\\data\\input_sh.txt");
      }
   }

   return 0;
}