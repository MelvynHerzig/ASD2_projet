//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 09 Dec 2020
//

#ifndef ASD2_LABS_2020_CORRECTOR_H
#define ASD2_LABS_2020_CORRECTOR_H

#include <string>    // std::string
#include <cctype>    // std::tolower, std::isalpha
#include <fstream>   // std::ifstream
#include <sstream>   // std::stringstream
#include <algorithm> //std::count

/**
 * @brief Classe simulant un correcteur orthographique.
 * @tparam Container Type du container qui contiendra le dictionnaire
 *         Doit supporter les méthodes size, insert, contains erase ainsi
 *         que le type string.
 */
template<class Container>
class Corrector
{
private:

   std::string dictionaryFilename;
   Container dictionary;

public:

   Corrector(const std::string& dictionaryFile): dictionaryFilename(dictionaryFile), dictionary(countDictionaryWord())
   {
      loadDictionary();
   }

private:
   /**
    * @brief Corrige un mot pour utiliser le correcteur.
    * @param word Mot à corriger.
    */
   void correctString(std::string& word)
   {
      for(size_t i = 0; i < word.size(); ++i)
      {
         char c = word[i];
         if( not( isalpha(c) || c == '\'') )
         {
            word.erase(i, 1);
         }

         word[i] = tolower(word[i]);
      }
   }

    /**
    * @brief Rempli le container avec les mot du dictionnaire.
    */
    void loadDictionary()
    {
       std::ifstream s(dictionaryFilename);
       std::string word;

       while(s.good())
       {
          s >> word;
          correctString(word);
          dictionary.insert(word);
       }
    }

    /**
    * @brief Compte le nombre de mot dans un fichier.
    * @param filename Nom du fichier à analyser.
    * @return Retourne le nombre de mot du fichier.
    */
    size_t countDictionaryWord()
    {
       std::ifstream s(dictionaryFilename);
       size_t count = 0;
       std::string line;

       while(s.good())
       {
          s >> line;
          std::stringstream linesStream(line);
          while(getline(linesStream, line, ' '))
          {
             ++count;
          }
       }
       return count;

    }
};

#endif //ASD2_LABS_2020_CORRECTOR_H
