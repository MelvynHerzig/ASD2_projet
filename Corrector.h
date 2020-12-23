//
// Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 09 Dec 2020
//

#ifndef ASD2_LABS_2020_CORRECTOR_H
#define ASD2_LABS_2020_CORRECTOR_H

#include <string>     // std::string
#include <cctype>     // std::tolower
#include <fstream>    // std::ifstream std::ofstream
#include <sstream>    // std::stringstream
#include <algorithm>  // std::count, std::find
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

   // Jeu de caractères autorisés
   static const size_t CHARSET_LENGTH = 27;
   const char charset[CHARSET_LENGTH] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\''};

   std::string dictionaryFilename;
   Container dictionary;

public:

   /**
    * Constructeur
    * @param dictionaryFile Nom du fichier dictionnaire à lire et charger.
    */
   Corrector(const std::string& dictionaryFile): dictionaryFilename(dictionaryFile), dictionary(countDictionaryWord())
   {
      loadDictionary();
   }

   void correctFile(const std::string& filename)
   {
      std::string output = createOutFilename(filename);

      std::ifstream inputs(filename);
      std::string word;

      std::ofstream outputs;
      outputs.open(output, std::ofstream::trunc);


      while(inputs.good())
      {
         inputs >> word;
         correctString(word);
         if(word != "" && !dictionary.contains(word))
         {
            outputs << '*' + word << std::endl;

            tryOneLetterLess(word, outputs);
            tryOneLetterMore(word, outputs);
            tryOneLetterChanged(word, outputs);
            tryTwoLettersSwapped(word, outputs);
         }
      }
      outputs.close();
      inputs.close();
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
         word[i] = tolower(word[i]);
         if(  std::find(charset, charset + CHARSET_LENGTH, word[i]) == (charset + CHARSET_LENGTH))
         {
            word.erase(i, 1);
            --i;
         }
      }
   }

    /**
    * @brief Rempli le container avec les mots du dictionnaire.
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

    /**
     * Pour un chemin Windows du fichier input, créer le fichier output.
     * Le fichier de sortie sera au même endroit que le fichier d'entrée.
     * Le fichier de sortie sera de la forme "Corrections_<nom du fichier d'entrée>"
     * @param inputFile Chemin et nom du fichier d'entrée.
     * @return Retourne le chemin et le nom du fichier de sortie.
     */
    std::string createOutFilename(const std::string& inputFile)
    {
       char delimiter = '\\';
       size_t namePos = inputFile.rfind(delimiter);
       std::string path = ".\\";
       std::string outfilename = "Corrections_";
       if(namePos != std::string::npos)
       {
          path = inputFile.substr(0,namePos+1);
       }

       return outfilename = path + outfilename + inputFile.substr(namePos+1);
    }

    /**
     * Génère les mots avec une lettre en moins et vérifie si ils appartiennent au dictionnaire.
     * Si telle est le cas, la suggestion est écrite dans le flux outputs.
     * @param word Mot à tenter les variations.
     * @param outputs Flux de sortie.
     */
    size_t tryOneLetterLess(const std::string word, std::ofstream& outputs)
    {
       std::string wordCopy;

       for(size_t i = 0; i < word.size(); ++i)
       {
          wordCopy = word;
          wordCopy.erase(i, 1);

          if(dictionary.contains(wordCopy))
             outputs << 1 << ":" << wordCopy << std::endl;
       }
    }

    /**
     * Génère les mots avec une lettre en plus et vérifie si ils appartiennent au dictionnaire.
     * Si telle est le cas, la suggestion est écrite dans le flux outputs.
     * @param word Mot à tenter les variations.
     * @param outputs Flux de sortie.
     */
    size_t tryOneLetterMore(const std::string word, std::ofstream& outputs)
    {
       std::string wordCopy;

       for(size_t i = 0; i <= word.size(); ++i)
       {
          for(size_t c = 0; c < CHARSET_LENGTH; ++c)
          {
             wordCopy = word;
             wordCopy.insert(i, 1, charset[c]);

             if(dictionary.contains(wordCopy))
                outputs << 2 << ":" << wordCopy << std::endl;
          }
       }
   }

   /**
     * Génère les mots avec une lettre modifiée et vérifie si ils appartiennent au dictionnaire.
     * Si telle est le cas, la suggestion est écrite dans le flux outputs.
     * @param word Mot à tenter les variations.
     * @param outputs Flux de sortie.
     */
   size_t tryOneLetterChanged(const std::string word, std::ofstream& outputs)
   {
      std::string wordCopy;

      for(size_t i = 0; i < word.size(); ++i)
      {
         for(size_t c = 0; c < CHARSET_LENGTH; ++c)
         {
            wordCopy = word;
            if(charset[c] != word[i])
               wordCopy.replace(i, 1,1, charset[c]);

            if(dictionary.contains(wordCopy))
               outputs << '3' << ":" << wordCopy << std::endl;
         }
      }
   }

   /**
     * Génère les mots avec deux lettres adjacentes échangées et vérifie si ils appartiennent au dictionnaire.
     * Si telle est le cas, la suggestion est écrite dans le flux outputs.
     * @param word Mot à tenter les variations.
     * @param outputs Flux de sortie.
     */
   void tryTwoLettersSwapped(const std::string word, std::ofstream& outputs)
   {
      std::string wordCopy;

      // Mot avec deux lettres échangées
      for(size_t i = 0; i < word.size() - 1; ++i)
      {
         wordCopy = word;
         std::swap(wordCopy[i], wordCopy[i+1]);

         if(dictionary.contains(wordCopy))
            outputs << '4' << ":" << wordCopy << std::endl;
      }
   }
};

#endif //ASD2_LABS_2020_CORRECTOR_H
