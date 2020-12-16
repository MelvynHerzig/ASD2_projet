//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 09 Dec 2020
//

#ifndef ASD2_LABS_2020_CORRECTOR_H
#define ASD2_LABS_2020_CORRECTOR_H

#include <string>     // std::string
#include <cctype>     // std::tolower, std::isalpha
#include <fstream>    // std::ifstream std::ofstream
#include <sstream>    // std::stringstream
#include <algorithm>  // std::count
#include <chrono>     // std::chrono

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

   void correctFile(const std::string& filename)
   {
      std::string output = "..\\data\\corrections.txt";

      //splitFilePath(filename, output);

     // std::ifstream inputs(filename);
      std::string word;

      std::ofstream outputs;
      outputs.open(output, std::ofstream::app);

      if(outputs.is_open())
      {
         std::cout << "OUVRE TOI ENCULE" << std::endl;
      }

//      while(inputs.good())
//      {
//         inputs >> word;
//         correctString(word);
//
//         if(!dictionary.contains(word))
//         {
//            outputs << '*' + word;
//            // Mots avec une lettre en moins
//
//            // Mots avec une lettre en plus
//
//            // Mots avec une lettre modifiées
//         }
//      }

      outputs << "Tamer";

      //inputs.close();
      outputs.close();
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
       auto t1 = std::chrono::high_resolution_clock::now();
       std::ifstream s(dictionaryFilename);
       std::string word;

       while(s.good())
       {
          s >> word;
          correctString(word);
          dictionary.insert(word);
       }
       auto t2 = std::chrono::high_resolution_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
       std::cout << "Chargement du dictionnaire en: " << duration << " ms" << std::endl;

       s.close();
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

       s.close();
       return count;
    }

    void splitFilePath(const std::string& inputFile, std::string& outfilename)
    {
       char delimiter = '\\';
       size_t namePos = inputFile.rfind(delimiter);
       std::string path = ".\\";
       outfilename = "Corrections_";
       if(namePos != std::string::npos)
       {
          path = inputFile.substr(0,namePos+1);
       }

       outfilename = path + outfilename + inputFile.substr(namePos+1);
    }
};

#endif //ASD2_LABS_2020_CORRECTOR_H
