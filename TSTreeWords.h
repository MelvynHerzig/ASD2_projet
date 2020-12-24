/*
 * Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 24 Dec 2020
 */

#ifndef ASD2_LABS_2020_TSTREEWORDS_H
#define ASD2_LABS_2020_TSTREEWORDS_H

#include <algorithm> // std::max()
#include <string>    // std::string

/**
 * @brief La classe TSTreeWords met en place une structure d'arbre ternaire
 * de recherche pour les chaînes de caractères. Il sera rempli avec différents mots
 * du dictionnaire anglophone. Lorsque un noeud ayant la valeur "true" est atteint,
 * cela indique que le mot obtenu existe. La classe implémente
 * la même interface que HashMapChain, HashMapLinearSample, std::set et
 * std::unordered_set, plus précisement insert, contains, size et erase.
 * Ainsi la structure pour être utilisé en tant que container pour la classe Corrector.
 *
 * L'arbre est équilibré sur ses sous arbres droites et gauches uniquement.
 */
class TSTreeWords
{

private:
   struct Node
   {
   public:
      char character;
      bool isWord;
      Node* right;    // Sous-arbre avec une lettre plus grande en caractère de remplacement.
      Node* center;   // Sous-arbre des prochaines lettres du mots.
      Node* left;     // Sous-arbre avec une lettre plus petite en caractère de remplacement.
      int nodeHeight; // Hauteur du sous arbre duquel ce noeud est racine.

      Node(char character) : character(character), isWord(false), right(nullptr), center(nullptr), left(nullptr), nodeHeight(0){}
   };

   int nbElem; // Nombre de mots dans la structure.
   Node* root; // Racine de l'arbre.

//--------------------------------------------------------------------------------
//                               UTILITAIRES
//--------------------------------------------------------------------------------

   /**
    * @brief Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants.
    * @param x Noeud à mettre à jour.
    */
   void updateNodeHeight(Node* x);

   /**
    * @brief Rotation droite avec mise à jour des tailles et hauteurs
    * @param x Noeud sur lequel effectuer la rotation.
    * @return Retourne un pointeur vers le noeud remplacant x.
    */
   Node* rotateRight(Node* x);

   /**
    * @brief Rotation gauche avec mise à jour des tailles et hauteurs
    * @param x Noeud sur lequel effectuer la rotation.
    * @return Retourne un pointeur vers le noeud remplacant x.
    */
   Node* rotateLeft(Node* x);

//--------------------------------------------------------------------------------
//                              CONSTRUCTEUR & DESTRUCTEUR
//--------------------------------------------------------------------------------

public:

   /**
    * @brief Constructeur, la racine est vide.
    */
   TSTreeWords();

   /**
    * @brief Destructeur.
    */
   ~TSTreeWords();

private:

   /**
    * @brief détruit le noeud x et ses sous-arbres
    * @param x Noeud à détruire.
    */
   void deleteSubTree(Node* x);

//--------------------------------------------------------------------------------
//                              INSERTION
//--------------------------------------------------------------------------------

public:
   /**
    * @brief Insert un mot dans la structure.
    * @param word Mot à insérer.
    */
   void insert(const std::string& word);

private:
   /**
    * @brief insère la lettre d'index d du mot word depuis le noeud x.
    * @param x Noeud depuis lequel commencer l'insertion.
    * @param word Mot à insérer.
    * @param d Index de la lettre à insérer.
    * @return Retourne le noeud sur lequel la lettre a été inserée.
    */
   Node* insert(Node* x, const std::string& word, size_t d);

//--------------------------------------------------------------------------------
//                              EQUILIBRAGE
//--------------------------------------------------------------------------------
private:

   /**
    * @brief Calcule l'equilibre des sous-arbres droites et gauches du noeud x.
    * @param x Noeud à calculer l'équilibre.
    * @return Retourne le la hauteur de gauche - hauteur de droite.
    */
   int balance(Node* x);

   /**
    * @brief Restaure l'équilibre par rotation du noeud x.
    * @param x Noeud à équilibrer.
    * @return Retourne le nouveux noeud qui le remplace.
    */
   Node* restoreBalance(Node* x);

//--------------------------------------------------------------------------------
//                              APPARTENANCE
//--------------------------------------------------------------------------------
public:
   /**
    * @brief Vérifie si le mot word est contenu dans la structure de donnée.
    * @param word Mot à rechercher l'existance.
    * @return Vrai si le mot existe sinon faux.
    */
   bool contains( const std::string& word );

private:
   /**
    * @brief Vérifie si le sous-chaîne de word, entre d et se fin, exist depuis le
    *        noeud x.
    * @param x Noeud depuis lequel rechercher.
    * @param word Mot à rechercher.
    * @param d Depuis quel index du mot rechercher.
    * @return Retourne le noeud correspondant à la dernière lettre ou null si
    *         non accessible car lettres inexistantes.
    */
   Node* contains(Node* x, const std::string& word, size_t d);

//--------------------------------------------------------------------------------
//                              SUPPRESSION
//--------------------------------------------------------------------------------
public:

   /**
    * @brief Supprime un mot du TST.
    * @param word Mot à supprimer
    */
   void erase( const std::string& word );

private:

   /**
    * @brief Supprime les lettre du mot dans le tst si celle si sont des feuilles
    *        qui ne correspondent pas à un autre mot.
    * @param x Noeud depuis lequel commencer à rechercher.
    * @param word Mot à supprimer.
    * @param d Nombre de lettres déjà traitées.
    * @return Retourne le nouveau noeud remplaçant x en cas de rotation/supression.
    */
   Node* erase(Node* x, const std::string& word, size_t d);

//--------------------------------------------------------------------------------
//                              DIMENSION
//--------------------------------------------------------------------------------
public:

   /**
    * @brief Indique la profondeur de l'arbre.
    * @return Retourne la profondeur de l'arbre.
    */
   int height() const;

private:
   /**
    * @brief Calcul la profondeur depuis un noeud x donné.
    * @param x Noeud à connaître la profondeur
    * @return Retourne la profondeur depuis le noeud.
    */
   int height(Node* x) const;

public:
   /**
    * @brief Indique la nombre de mots stockés dans le tst.
    * @return Retourne le nombre de mots du tst.
    */
   size_t size() const;
};


#endif //ASD2_LABS_2020_TSTREEWORDS_H
