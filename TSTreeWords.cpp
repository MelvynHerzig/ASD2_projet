/*
 * Created by Berney Alec, Forestier Quentin, Herzig Melvyn on 24 Dec 2020
 */

#include "TSTreeWords.h"

//--------------------------------------------------------------------------------
//                               UTILITAIRES
//--------------------------------------------------------------------------------

void TSTreeWords::updateNodeHeight(Node* x)
{
   x->nodeHeight = std::max(std::max(height(x->right),height(x->left)), height(x->center)) + 1;
}

TSTreeWords::Node* TSTreeWords::rotateRight(Node* x) {
   Node* y = x->left;
   x->left = y->right;
   y->right = x;

   updateNodeHeight(x);
   updateNodeHeight(y);
   return y;
}

TSTreeWords::Node* TSTreeWords::rotateLeft(Node* x)
{
   Node* y = x->right;
   x->right = y->left;
   y->left = x;

   updateNodeHeight(x);
   updateNodeHeight(y);
   return y;
}

//--------------------------------------------------------------------------------
//                              CONSTRUCTEUR & DESTRUCTEUR
//--------------------------------------------------------------------------------

TSTreeWords::TSTreeWords() : root(nullptr), nbElem(0) { }

TSTreeWords::~TSTreeWords() { deleteSubTree( root ); }

void TSTreeWords::deleteSubTree(Node* x)
{
   if( x == nullptr) return;
   deleteSubTree( x->right );
   deleteSubTree( x->center );
   deleteSubTree( x->left );
   if(x->isWord) --nbElem;
   delete x;
}

//--------------------------------------------------------------------------------
//                              INSERTION
//--------------------------------------------------------------------------------

void TSTreeWords::insert(const std::string& word)
{
   if(word.empty()) return;
   root = insert(root, word, 0);
}

TSTreeWords::Node* TSTreeWords::insert(Node* x, const std::string& word, size_t d)
{
   char c = word.at(d);

   if (x==nullptr)
   {
      x = new Node(c);
   }

   if ( c < x->character )
      x->left = insert(x->left, word, d);
   else if ( c > x->character)
      x->right = insert(x->right, word, d);
   else if ( d < word.size() - 1)
      x->center = insert(x->center, word, d+1);
   else
   {
      if(not x->isWord) ++nbElem;
      x->isWord = true;
   }

   return restoreBalance(x);
}

//--------------------------------------------------------------------------------
//                              EQUILIBRAGE
//--------------------------------------------------------------------------------

int TSTreeWords::balance(Node* x)
{
   if(x==nullptr) return 0;
   return height(x->left) - height(x->right);
}

TSTreeWords::Node* TSTreeWords::restoreBalance(Node* x) {

   if(balance(x) < -1) // left < right-1
   {
      if (balance(x->right)>0)
         x->right = rotateRight( x->right );
      x = rotateLeft(x);
   }
   else if( balance(x) > 1) // left > right+1
   {
      if ( balance(x->left) < 0 )
         x->left = rotateLeft( x->left );
      x = rotateRight(x);
   }
   else updateNodeHeight(x);
   return x;
}

//--------------------------------------------------------------------------------
//                              APPARTENANCE
//--------------------------------------------------------------------------------

bool TSTreeWords::contains( const std::string& word )
{
   if(word.empty()) return false;
   Node* x = contains(root, word, 0);
   return x != nullptr && x->isWord;
}

TSTreeWords::Node* TSTreeWords::contains(Node* x, const std::string& word, size_t d)
{
   if(x == nullptr) return nullptr;

   char c = word.at(d);

   if(c < x->character)
      return contains(x->left, word, d);
   else if(c > x->character)
      return contains(x->right, word, d);
   else if (d < word.size() - 1)
      return contains(x->center, word, d+1);
   else
      return x;
}

//--------------------------------------------------------------------------------
//                              SUPPRESSION
//--------------------------------------------------------------------------------

void TSTreeWords::erase( const std::string& word )
{
   root = erase(root, word, 0);
}

TSTreeWords::Node* TSTreeWords::erase(Node* x, const std::string& word, size_t d)
{
   if(x == nullptr) return nullptr;

   char c = word.at(d);

   if(c < x->character)
      x->left = erase(x->left, word, d);
   else if(c > x->character)
      x->right = erase(x->right, word, d);
   else if (d < word.size() - 1)
      x->center = erase(x->center, word, d+1);
   else
   {
      x->isWord = false;
      --nbElem;
   }

   if(!x->isWord && x->left == nullptr && x->center == nullptr && x->right == nullptr)
   {
      delete x;
      return nullptr;
   }

   return restoreBalance(x);

}

//--------------------------------------------------------------------------------
//                              DIMENSION
//--------------------------------------------------------------------------------

int TSTreeWords::height() const
{
   return height(root);
}

int TSTreeWords::height(Node* x) const
{
   if ( x == nullptr )
      return -1;
   return x->nodeHeight;
}

size_t TSTreeWords::size() const
{
   return nbElem;
}
