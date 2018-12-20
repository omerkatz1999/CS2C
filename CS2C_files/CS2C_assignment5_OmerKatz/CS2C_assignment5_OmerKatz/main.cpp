/*


 1. What type of traversal does the traverse function in the FHsearch_tree use?
 
 It uses an inorder traversal because it prints left, root, and then right.
 This is easy to see because with every line the numbers increase.
 
 2. What is the purpose of the height data member in the AVL tree nodes?
 
 The nodes' heights are used in order to see if the longest left branch and longest
 right branch do not have a difference of more than 1 in height. If they do then it signifies
 that a rotation or double rotation is needed in order to rebalance the tree.
 
 3. There are 4 rotation functions. In which of the situations would you use each of the functions?
 
 The four functions are rotateWithLeftChild, rotateWithRightChild, doubleWithLeftChild
 , and doubleWithRightChild. Each is used for a different scenario where the tree needs to be rebalanced. A single rotation is needed for a Left Left or Right Right scenario. A double rotation is needed for a "zig zag" such as Left of Right or Right of Left.

 
 
 4.Which functions use the rotation functions? Why?
 
 Every function that could unbalance the tree must use these functions in order to rebalance the tree and maintain the AVL criteria of having a left and right branch with a difference of no more than one. The functions that use these rotations are insert and remove because they both change the structure of the tree and thus must use rotations to rebalance it.



*/
#include <iostream>

#include "FHsearch_tree.h"

#include "FHavlTreeLab5.h"




using namespace std;




// Printing Functor for Tree

template <class Object>

class PrintObject

{
    
public:
    
    void operator ()(Object x)
    
    {
        
        cout << x << endl;
        
    }
    
};




int main()

{
    FHavlTreeLab5<int> myTree;
    
    PrintObject<int> intPrinter;
    
    
    
    
    for (int i = 0; i < 20; i++)
        
        myTree.insert(i);
    
    myTree.traverse(intPrinter);
    
    cout << endl;
    
    return 0;
    
}




