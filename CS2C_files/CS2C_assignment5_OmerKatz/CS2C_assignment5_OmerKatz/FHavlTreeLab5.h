// File FHavlTreeLab5.h
// Template definitions for FHavlTreeLab5s.  
#ifndef FHavlTreeLab5_H
#define FHavlTreeLab5_H
#include "FHsearch_tree.h"

using namespace std;

// ---------------------- AvlNode --------------------------
template <class Comparable>
class AvlNode : public FHs_treeNode<Comparable>
{
public: 
   AvlNode(const Comparable &d, AvlNode *lftChild, AvlNode *rtChild, int ht = 0)
      : FHs_treeNode<Comparable>(d, lftChild, rtChild), height(ht)
   { }

   int height;

   int getHeight() const { return height; }
   bool setHeight(int height);
};

template <class Comparable>
bool AvlNode<Comparable>::setHeight(int height) 
{
   if (height < -1) 
      return false;
   this->height = height;
   return true;
}

// ---------------------- FHavlTreeLab5 Prototype --------------------------
template <class Comparable>
class FHavlTreeLab5 : public FHsearch_tree<Comparable>
{
public:
   // we need our own copy constructor and op= because of height info
   FHavlTreeLab5(const FHavlTreeLab5 &rhs) 
      { this->mRoot = NULL; this->mSize = 0; *this = rhs; }

   // need a default because above hides it.  Simply chain to base class
   FHavlTreeLab5() : FHsearch_tree<Comparable>() { }

   const FHavlTreeLab5 & operator=(const FHavlTreeLab5 &rhs);

   // override base class insert/remove
   bool insert(const Comparable &x);
   bool remove(const Comparable &x);

   // a fun and informative touch
   int showHeight() const { return heightOf(this->mRoot); }
    
    template <class Processor>
    void traverse(Processor func) const { traverse(this->mRoot, func, 0 ); }

protected:
   // static because the node whose height we want might be null
   static int heightOf(FHs_treeNode<Comparable> *t)
      { return t == NULL? -1 : t->getHeight(); }
   AvlNode<Comparable> *clone( FHs_treeNode<Comparable> *root) const;

   bool insert( const Comparable & x, FHs_treeNode<Comparable> * & root );
   bool remove( const Comparable & x, FHs_treeNode<Comparable> * & root );
   void rotateWithLeftChild( FHs_treeNode<Comparable> * & k2 );
   void doubleWithLeftChild( FHs_treeNode<Comparable> * & k3 );
   void rotateWithRightChild( FHs_treeNode<Comparable> * & k2 );
   void doubleWithRightChild( FHs_treeNode<Comparable> * & k3 );
   static int max(int a, int b) { return (a < b)? b : a ; }
    
   template<class Processor>
   void traverse( FHs_treeNode<Comparable> *treeNode, Processor func, int level) const;
};

// FHavlTreeLab5 method definitions -------------------
// private utilities for member methods
template <class Comparable>
bool FHavlTreeLab5<Comparable>::insert( const Comparable & x, 
   FHs_treeNode<Comparable> * & root )
{
   if( root == NULL )
   {
      // found a place to hang new node
      root = new AvlNode<Comparable>(x, NULL, NULL, 0);
      return true;
   }
   else if( x < root->data )
   {
      if ( !insert(x, root->lftChild) )
         return false;
      if(heightOf(root->lftChild) - heightOf(root->rtChild) == 2)
         if( x < root->lftChild->data )
            rotateWithLeftChild(root);
         else
            doubleWithLeftChild(root);
   }
   else if(root->data < x)
   {
      if ( !insert(x, root->rtChild) )
         return false;
      if(heightOf(root->rtChild) - heightOf(root->lftChild) == 2)
         if(root->rtChild->data < x)
            rotateWithRightChild(root);
         else
            doubleWithRightChild(root);
   }
   else
      return false;

   // successfully inserted at this or lower level; adjust height
   root->setHeight( max(heightOf(root->lftChild), heightOf(root->rtChild)) + 1);
   return true;
}

template <class Comparable>
bool FHavlTreeLab5<Comparable>::remove( const Comparable & x, 
   FHs_treeNode<Comparable> * & root )
{
   if (root == NULL)
      return false;

   if (x < root->data)
   {
      if ( !remove(x, root->lftChild) )
         return false;

      // rebalance - shortened left branch so right may now be higher by 2
      if(heightOf(root->rtChild) - heightOf(root->lftChild) == 2)
         if(heightOf(root->rtChild->rtChild) < heightOf(root->rtChild->lftChild))
            doubleWithRightChild(root);
         else
            rotateWithRightChild(root);
   }
   else if (root->data < x)
   {
      if ( !remove(x, root->rtChild) )
         return false;

      // rebalance - shortened right branch so left may now be higher by 2
      if(heightOf(root->lftChild) - heightOf(root->rtChild) == 2)
         if(heightOf(root->lftChild->lftChild) < heightOf(root->lftChild->rtChild))
            doubleWithLeftChild(root);
         else
            rotateWithLeftChild(root);
   }

   // found the node
   else if (root->lftChild != NULL && root->rtChild != NULL)
   {
      // first simply copy min right data into the node marked for deletion
      FHs_treeNode<Comparable> *minNode = this->findMin(root->rtChild);
      root->data = minNode->data;

      // now  do a real deletion:  the old min is still in the right sub-tree
      remove(minNode->data, root->rtChild);

      // rebalance - shortened right branch so left may now be higher by 2
      if(heightOf(root->lftChild) - heightOf(root->rtChild) == 2)
         if(heightOf(root->lftChild->lftChild) < heightOf(root->lftChild->rtChild))
            doubleWithLeftChild(root);
         else
            rotateWithLeftChild(root);
   }
   else
   {
      // no rebalancing needed at this external (1+ NULL children) node
      FHs_treeNode<Comparable> *nodeToRemove = root;
      root = (root->lftChild != NULL)? root->lftChild : root->rtChild;
      delete nodeToRemove;
      return true;

   }
   // successfully removed and rebalanced at this and lower levels; 
   // now adjust height
   root->setHeight(max(heightOf(root->lftChild), heightOf(root->rtChild)) + 1);
   return true;
}

template <class Comparable>
void FHavlTreeLab5<Comparable>::rotateWithLeftChild( 
   FHs_treeNode<Comparable> * & k2 )
{
   FHs_treeNode<Comparable> *k1 = k2->lftChild;
   k2->lftChild = k1->rtChild;
   k1->rtChild = k2;
   k2->setHeight( max( heightOf(k2->lftChild),  heightOf(k2->rtChild) ) + 1 );
   k1->setHeight( max( heightOf(k1->lftChild),  k2->getHeight() ) + 1 );
   k2 = k1;
}

template <class Comparable>
void FHavlTreeLab5<Comparable>::doubleWithLeftChild( 
   FHs_treeNode<Comparable> * & k3 )
{
   rotateWithRightChild(k3->lftChild);
   rotateWithLeftChild(k3);
}

template <class Comparable>
void FHavlTreeLab5<Comparable>::rotateWithRightChild( 
   FHs_treeNode<Comparable> * & k2 )
{
   FHs_treeNode<Comparable> *k1 = k2->rtChild;
   k2->rtChild = k1->lftChild;
   k1->lftChild = k2;
   k2->setHeight( max( heightOf(k2->lftChild), heightOf(k2->rtChild) ) + 1 );
   k1->setHeight( max( heightOf(k1->rtChild), k2->getHeight() ) + 1 );
   k2 = k1;
}

template <class Comparable>
void FHavlTreeLab5<Comparable>::doubleWithRightChild( 
   FHs_treeNode<Comparable> * & k3 )
{
   rotateWithLeftChild(k3->rtChild);
   rotateWithRightChild(k3);
}

// FHsearch_tree private method definitions -----------------------------
template <class Comparable>
AvlNode<Comparable> *FHavlTreeLab5<Comparable>::clone(
   FHs_treeNode<Comparable> *root) const
{
   AvlNode<Comparable> *newNode;
   if (root == NULL)
      return NULL;

   newNode =  new AvlNode<Comparable>(
      root->data, 
      clone(root->lftChild), clone(root->rtChild), root->getHeight());
   return newNode;
}

// public interface
template <class Comparable>
bool FHavlTreeLab5<Comparable>::insert( const Comparable &x )
{
   if (insert(x, this->mRoot))
   {
      this->mSize++;
      return true;
   }
   return false;
}

template <class Comparable>
bool FHavlTreeLab5<Comparable>::remove( const Comparable &x )
{

   if (remove(x, this->mRoot))
   {
      this->mSize--;
      return true;
   }
   return false;
}

template <class Comparable>
const FHavlTreeLab5<Comparable> &FHavlTreeLab5<Comparable>::operator=
   (const FHavlTreeLab5 &rhs)
{
   if (&rhs != this) 
   {
      this->clear();
      this->mRoot = clone(rhs.mRoot);
      this->mSize = rhs.size();
   }
   return *this;
}



template <class Comparable>
template <class Processor>
void FHavlTreeLab5<Comparable>:: traverse( FHs_treeNode<Comparable> *treeNode,
                                          Processor func, int level) const
{
    if (treeNode == NULL)
        return;
   
    traverse(treeNode->lftChild, func, level + 1);
    
    if(level == 0)
    {
        cout << "r";
        func(treeNode->data);
        cout << endl;
        
    }
    else{
        for(int i = 0; i < level; i++)
        {
            cout << "        ";
        }
        func(treeNode->data);
        cout << endl;
    }
    
    traverse(treeNode->rtChild, func, level + 1);
}




#endif
