
// -------------- main.cpp -------------------------------------
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include "PQ.h"
#include "FHbinHeap.h"

int main(int argc, const char * argv[]) {
    clock_t startTime, stopTime;
    
    PQsortedList<int> myList;
    myList.insert(4);
    myList.insert(20);
    myList.insert(80);
    
    try {
        cout << myList.remove() << endl;
        cout << myList.remove() << endl;
        cout << myList.remove() << endl;
        cout << myList.remove() << endl;
        cout << myList.remove() << endl;
    }
    catch (EmptyPQException) {
        cout << "empty PQ" << endl;
    }
    
    PQunsortedList<int> myList2;
    myList2.insert(20);
    myList2.insert(4);
    myList2.insert(80);
    
    try {
        cout << myList2.remove() << endl;
        cout << myList2.remove() << endl;
        cout << myList2.remove() << endl;
        cout << myList2.remove() << endl;
        cout << myList2.remove() << endl;
        cout << myList2.remove() << endl;
    }
    catch (EmptyPQException) {
        cout << "empty PQ" << endl;
    }
    
    // Timing on random list of numbers
    int  sizes[] = {5000, 10000, 20000, 40000};
    int numSizesToTest = sizeof(sizes)/sizeof(sizes[0]);
    for (int i = 0; i < numSizesToTest; i++) {
        vector<int> randNumbersToInsert;
        int numNumbers = sizes[i];
        /*
         //for vector of random numbers
         for (int j = 0; j < numNumbers; j++) {
            // arbitrary - make random numbers up to 5 times the size of the vector, to spread them out
            // random numbers
            int r = rand() / (double) RAND_MAX * numNumbers * 5;
            randNumbersToInsert.push_back(r);
        }
         
         */
        
        /*
        //  sorted vector
        for( int i = 0; i < numNumbers; i++)
        {
            randNumbersToInsert.push_back(i);
        }
        */
        
        
         //  antisorted vector
         for( int i = numNumbers-1; i > 0; i--)
         {
         randNumbersToInsert.push_back(i);
         }
         
        /*
        PQsortedList<int> sortedListPQ;
        PQunsortedList<int> unsortedListPQ;
        FHbinHeap<int> heapPQ;
        
        // put your timing tests here:
      
        // ----------------- sorted list test ------------------
        // YOUR TEST HERE
        
        startTime = clock();
        
        for(int i = 0; i < randNumbersToInsert.size(); i++)
        {
            sortedListPQ.insert(randNumbersToInsert[i]);
        }
        
        stopTime = clock();
        cout << "\nSize = " <<  numNumbers << " inserted into sortedListPQ.";
        cout << "Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
        
        // YOUR TEST HERE
        
        startTime = clock();
        
        for(int i = 0; i < randNumbersToInsert.size(); i++)
        {
            sortedListPQ.remove();
        }
        
        stopTime = clock();
        
        cout << "\nSize = " <<  numNumbers << " removed from sortedListPQ.";
        cout << "Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
        
         // ----------------- unsorted list test ------------------
        
        // ETC - TESTS FOR OTHER DATA STRUCTURES
        
        startTime = clock();
        
        for(int i = 0; i < randNumbersToInsert.size(); i++)
        {
            unsortedListPQ.insert(randNumbersToInsert[i]);
        }
        
        stopTime = clock();
        
        cout << "\nSize = " <<  numNumbers << " insert into unsortedListPQ.";
        cout << "Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
        
        startTime = clock();
        
        for(int i = 0; i < randNumbersToInsert.size(); i++)
        {
            unsortedListPQ.remove();
        }
        
        stopTime = clock();
        
        cout << "\nSize = " <<  numNumbers << " removed from unsortedListPQ.";
        cout << "Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
        
         // ----------------- min heap ------------------
        
        startTime = clock();
        
        for(int i = 0; i < randNumbersToInsert.size(); i++)
        {
            heapPQ.insert(randNumbersToInsert[i]);
        }
        
        stopTime = clock();
        
        cout << "\nSize = " <<  numNumbers << " inserted into heapPQ.";
        cout << "Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
        
        startTime = clock();
        
        for(int i = 0; i < randNumbersToInsert.size(); i++)
        {
            heapPQ.remove();
        }
        
        stopTime = clock();
        
        cout << "\nSize = " <<  numNumbers << " removed from heapPQ.";
        cout << "Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
        
         */
        // Creates a min heap
        priority_queue <int, vector<int>, greater<int> > pq;
     
        
        
        startTime = clock();
        
        for(int i = 0; i < randNumbersToInsert.size(); i++)
        {
            pq.push(randNumbersToInsert[i]);
        }
        
        stopTime = clock();
        
        cout << "anti sorted Vector" << endl;
        cout << "\nSize = " <<  numNumbers << " inserted into priority queue.";
        cout << "Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
        
        startTime = clock();
        
        for(int i = 0; i < randNumbersToInsert.size(); i++)
        {
            pq.pop();
        }
        
        stopTime = clock();
        
        cout << "\nSize = " <<  numNumbers << " removed from priority queue.";
        cout << "Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
        
     
        
    }
    
    int  sizes2[] = {5000, 10000, 20000, 40000};
    int numSizesToTest2 = sizeof(sizes)/sizeof(sizes[0]);
    for (int i = 0; i < numSizesToTest2; i++) {
        vector<int> randNumbersToInsert;
        int numNumbers = sizes2[i];
        /*
         //for vector of random numbers
         for (int j = 0; j < numNumbers; j++) {
         // arbitrary - make random numbers up to 5 times the size of the vector, to spread them out
         // random numbers
         int r = rand() / (double) RAND_MAX * numNumbers * 5;
         randNumbersToInsert.push_back(r);
         }
         
         */
        
        
         //  sorted vector
         for( int i = 0; i < numNumbers; i++)
         {
         randNumbersToInsert.push_back(i);
         }
        
        
        
       
        priority_queue <int, vector<int>, greater<int> > pq;
        
        
        
        startTime = clock();
        
        for(int i = 0; i < randNumbersToInsert.size(); i++)
        {
            pq.push(randNumbersToInsert[i]);
        }
        
        stopTime = clock();
        
        cout << " sorted Vector" << endl;
        cout << "\nSize = " <<  numNumbers << " inserted into priority queue.";
        cout << "Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
        
        startTime = clock();
        
        for(int i = 0; i < randNumbersToInsert.size(); i++)
        {
            pq.pop();
        }
        
        stopTime = clock();
        
        cout << "\nSize = " <<  numNumbers << " removed from priority queue.";
        cout << "Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
        
        
        
    }
    
   
    for (int i = 0; i < numSizesToTest; i++) {
        vector<int> randNumbersToInsert;
        int numNumbers = sizes[i];
        
         //for vector of random numbers
         for (int j = 0; j < numNumbers; j++) {
         // arbitrary - make random numbers up to 5 times the size of the vector, to spread them out
         // random numbers
         int r = rand() / (double) RAND_MAX * numNumbers * 5;
         randNumbersToInsert.push_back(r);
         }
        
        priority_queue <int, vector<int>, greater<int> > pq;
        
        
        
        startTime = clock();
        
        for(int i = 0; i < randNumbersToInsert.size(); i++)
        {
            pq.push(randNumbersToInsert[i]);
        }
        
        stopTime = clock();
        
        cout << " random Vector" << endl;
        cout << "\nSize = " <<  numNumbers << " inserted into priority queue.";
        cout << "Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
        
        startTime = clock();
        
        for(int i = 0; i < randNumbersToInsert.size(); i++)
        {
            pq.pop();
        }
        
        stopTime = clock();
        
        cout << "\nSize = " <<  numNumbers << " removed from priority queue.";
        cout << "Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
        
        
        
    }
    
}

/*

 anti sorted Vector:
 
 Size = 5000 inserted into priority queue.Elapsed Time: 0.001224 seconds.
 
 
 Size = 5000 removed from priority queue.Elapsed Time: 0.001672 seconds.
 
 
 Size = 10000 inserted into priority queue.Elapsed Time: 0.00252 seconds.
 
 
 Size = 10000 removed from priority queue.Elapsed Time: 0.003762 seconds.
 
 
 Size = 20000 inserted into priority queue.Elapsed Time: 0.005327 seconds.
 
 
 Size = 20000 removed from priority queue.Elapsed Time: 0.007933 seconds.
 
 
 Size = 40000 inserted into priority queue.Elapsed Time: 0.011467 seconds.
 
 
 Size = 40000 removed from priority queue.Elapsed Time: 0.01639 seconds.
 
 sorted Vector:
 
 Size = 5000 inserted into priority queue.Elapsed Time: 0.000322 seconds.
 

 Size = 5000 removed from priority queue.Elapsed Time: 0.001796 seconds.

 
 Size = 10000 inserted into priority queue.Elapsed Time: 0.000688 seconds.
 
 
 Size = 10000 removed from priority queue.Elapsed Time: 0.003695 seconds.
 

 
 Size = 20000 inserted into priority queue.Elapsed Time: 0.00112 seconds.
 
 
 Size = 20000 removed from priority queue.Elapsed Time: 0.008738 seconds.
 

 
 Size = 40000 inserted into priority queue.Elapsed Time: 0.002348 seconds.
 
 
 Size = 40000 removed from priority queue.Elapsed Time: 0.017151 seconds.
 

 
 Size = 5000 inserted into priority queue.Elapsed Time: 0.000557 seconds.
 
 
 Size = 5000 removed from priority queue.Elapsed Time: 0.001907 seconds.
 
 random Vector:
 
 Size = 10000 inserted into priority queue.Elapsed Time: 0.001077 seconds.
 
 
 Size = 10000 removed from priority queue.Elapsed Time: 0.00452 seconds.
 
 
 Size = 20000 inserted into priority queue.Elapsed Time: 0.002197 seconds.
 
 
 Size = 20000 removed from priority queue.Elapsed Time: 0.009687 seconds.
 
 
 Size = 40000 inserted into priority queue.Elapsed Time: 0.004133 seconds.
 
 
 Size = 40000 removed from priority queue.Elapsed Time: 0.016946 seconds.
 */
