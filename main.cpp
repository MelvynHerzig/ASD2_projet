//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 02 Dec 2020
//

#include <iostream> // std::cout, std::endl
#include "HashMapChain.h"
#include "HashMapLinearSample.h"
#include "Corrector.h"


using namespace std;

int main ()
{
   // Changer le typedef pour changer le type de container utilisé.
   typedef HashMapChain<string> Container;

   // Changer la localisation du fichier dictionnaire.
   string dictionnary = "..\\data\\dictionary.txt";
   string input = "..\\data\\input_sh.txt";

   Corrector<Container> corrector(dictionnary);
   corrector.correctFile(input);

   return 0;
}