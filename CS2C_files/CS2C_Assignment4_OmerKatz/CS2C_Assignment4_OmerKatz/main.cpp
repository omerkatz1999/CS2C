//
//  main.cpp
//  CS2C_Assignment4_OmerKatz
//
//  Created by Omer Katz on 10/19/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <iostream>
#include "FHlazySearchTree.h"
#include <string>
#include <stack>
#include "FHlazySearchTree.h"
#include "FHSearch_Tree.h"
#include <time.h>
#include <cstdlib>

using namespace std;

template <typename Object>
class PrintObject
{
public:
    void operator()(Object obj)
    {
        cout << obj << " ";
    }
};

int main()
{
    /*
    int k;
    FHlazySearchTree<int> searchTree;
    PrintObject<int> intPrinter;
    
    FHlazySearchTree<int> sTree;
    sTree.traverse(intPrinter);
    
    searchTree.traverse(intPrinter);
    
   
    
    
    sTree.insert(30);
    sTree.insert(70);
    sTree.insert(10);
    sTree.insert(60);
    sTree.remove(30);
    cout << "Max is 70: " << sTree.findMax() << endl;
    cout << "Min is 10: " << sTree.findMin() << endl;
    
    
    cout << "\ninitial size: " << searchTree.size() << endl;
    searchTree.insert(50);
    searchTree.insert(20);
    searchTree.insert(30);
    searchTree.insert(70);
    searchTree.insert(10);
    searchTree.insert(60);
    
    cout << "After populating -- traversal and sizes: \n";
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;
   
    
    cout << "Collecting garbage on new tree - should be no garbage." << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;
    
    // test assignment operator
    FHlazySearchTree<int> searchTree2 = searchTree;
    
    cout << "\n\nAttempting 1 removal: \n";
    if (searchTree.remove(20))
        cout << "removed " << 20 << endl;
    cout << "should be 60: " << searchTree.findMax() << endl;
    cout << "tree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;
    
    cout << "Collecting Garbage - should clean 1 item. " << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;
    
    cout << "Collecting Garbage again - no change expected. " << endl;
    searchTree.collectGarbage();
    cout << "tree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;
    
    // test soft insertion and deletion:
    
    cout << "Adding 'hard' 22 - should see new sizes. " << endl;
    searchTree.insert(22);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;
    
    cout << "\nAfter soft removal. " << endl;
    searchTree.remove(22);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;
    
    cout << "Repeating soft removal. Should see no change. " << endl;
    searchTree.remove(22);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;
    
    cout << "Soft insertion. Hard size should not change. " << endl;
    searchTree.insert(22);
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;
    
    cout << "\n\nAttempting 100 removals: \n";
    for (k = 100; k > 0; k--)
    {
        if (searchTree.remove(k))
            cout << "removed " << k << endl;
    }
    searchTree.collectGarbage();
    
    cout << "\nsearchTree now:\n";
    searchTree.traverse(intPrinter);
    cout << "\ntree 1 size: " << searchTree.size()
    << "  Hard size: " << searchTree.sizeHard() << endl;
    
   
    searchTree2.insert(500);
    searchTree2.insert(200);
    searchTree2.insert(300);
    searchTree2.insert(700);
    searchTree2.insert(100);
    searchTree2.insert(600);
    cout << "\nsearchTree2:\n";
    searchTree2.traverse(intPrinter);
    cout << "\ntree 2 size: " << searchTree2.size()
    << "  Hard size: " << searchTree2.sizeHard() << endl;
   */
   
    clock_t startTime, stopTime;
    
    FHlazySearchTree<int> lazyBST;
    
    FHlazySearchTree<int> BST;
   
    
    srand((unsigned)time(0));
    

    
    
    for( int i = 0 ; i < 10000000 ; i++)
    {
        int random_integer = rand()%1000;
        BST.insert(random_integer);
        
        
    }
    
    
    
   
    

  //  int random_integer = rand()%1000;

    startTime = clock();
    
  
    BST.clear();
 
  
    
    stopTime = clock();
    
    cout <<"Time: " << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
    
    << " seconds." << endl << endl;
    
    
}

/* ---------------------- Run --------------------------
 initial size: 0
 After populating -- traversal and sizes:
 10 20 30 50 60 70
 tree 1 size: 6  Hard size: 6
 Collecting garbage on new tree - should be no garbage.
 tree 1 size: 6  Hard size: 6
 
 
 Attempting 1 removal:
 removed 20
 tree 1 size: 5  Hard size: 6
 Collecting Garbage - should clean 1 item.
 tree 1 size: 5  Hard size: 5
 Collecting Garbage again - no change expected.
 tree 1 size: 5  Hard size: 5
 Adding 'hard' 22 - should see new sizes.
 10 22 30 50 60 70
 tree 1 size: 6  Hard size: 6
 
 After soft removal.
 10 30 50 60 70
 tree 1 size: 5  Hard size: 6
 Repeating soft removal. Should see no change.
 10 30 50 60 70
 tree 1 size: 5  Hard size: 6
 Soft insertion. Hard size should not change.
 10 22 30 50 60 70
 tree 1 size: 6  Hard size: 6
 
 
 Attempting 100 removals:
 removed 70
 removed 60
 removed 50
 removed 30
 removed 22
 removed 10
 
 searchTree now:
 
 tree 1 size: 0  Hard size: 0
 
 searchTree2:
 10 20 30 50 60 70 100 200 300 500 600 700
 tree 2 size: 12  Hard size: 12
 Press any key to continue
 */
