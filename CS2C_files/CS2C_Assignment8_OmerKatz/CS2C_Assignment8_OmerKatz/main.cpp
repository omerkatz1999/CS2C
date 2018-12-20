//
//  main.cpp
//  CS2C_Assignment8_OmerKatz
//
//  Created by Omer Katz on 11/30/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "FHsort.h"



// quickSort public driver
template <typename Comparable>
void quickSortX( FHvector<Comparable> & a, int recursionLimit )
{
    quickSortX(a, 0, a.size() - 1, recursionLimit);
}


// quickSort internal
template <typename Comparable>
void quickSortX(FHvector<Comparable> & a, int left, int right, int recursionLimit)
{
    int recurLimit = recursionLimit;
    Comparable pivot;
    int i, j;
    
    if( left + recurLimit <= right )
    {
        pivot = median3(a, left, right);
        for( i = left, j = right - 1; ; )
        {
            while( a[++i] < pivot )
                ;
            while( pivot < a[--j] )
                ;
            if( i < j )
                mySwapFH(a[i], a[j]);
            else
                break;
        }
        
        mySwapFH(a[i], a[right - 1]);  // restore pivot
        
        // recursive calls on smaller sub-groups
        quickSort(a, left, i - 1);
        quickSort(a, i + 1, right);
    }
    else
        // non-recursive escape valve - insertionSort
        insertionSort(a, left, right);
}


using namespace std;
int main(int argc, const char * argv[]) {
   
    clock_t startTime, stopTime;
    ofstream myFile;
    
    myFile.open ("/Users/omerkatz/Desktop/CS2C/CS2C_Assignment8_OmerKatz/CS2C_Assignment8_OmerKatz/CS2C_Assignment8.csv");
 
    
    myFile << "gap" << ","<<  "40000" << ","
           <<  "80000" << ","  << "120000"
           << "," << "160000" << endl;
    
    
   
    for(int i = 2; i <= 100; i += 2)
    {
        FHvector<int> fhVectorOfInts;
        
        for(int i = 0; i < 40000; i++)
        {
            fhVectorOfInts.push_back(rand()%1000000);
        }
        
        FHvector<int> fhVectorOfInts1;
        
        for(int i = 0; i < 80000; i++)
        {
            fhVectorOfInts1.push_back(rand()%1000000);
        }
        
        FHvector<int> fhVectorOfInts2;
        
        for(int i = 0; i < 120000; i++)
        {
            fhVectorOfInts2.push_back(rand()%1000000);
        }
        
        FHvector<int> fhVectorOfInts3;
        
        for(int i = 0; i < 160000; i++)
        {
            fhVectorOfInts3.push_back(rand()%1000000);
        }
        
        myFile << i << ",";
        startTime = clock();
        quickSortX(fhVectorOfInts, i);
        stopTime = clock();
        myFile << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
        
        startTime = clock();
        quickSortX(fhVectorOfInts1, i);
        stopTime = clock();
        myFile << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
        
        startTime = clock();
        quickSortX(fhVectorOfInts2, i);
        stopTime = clock();
        myFile << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
        
        startTime = clock();
        quickSortX(fhVectorOfInts3, i);
        stopTime = clock();
        myFile << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC <<endl;
        
        
        
    }
    
    
    
    myFile.close();
    
   /*
    
    The fastest times were with a recursion limit of 14, 16 , and 70 all with
    a time of about 0.00741. I would assume that 70 is an outliar and that the
    ideal recursion limit would be between 14 and 16. The recursion limits of 12
    and 2 were some of the slowest probably because insertion sort was overused.
    insertion sort can be very fast for small arrays that are somewhat sorted, or even
    have O(n) when the array is sorted and therefore should be used once quicksort
    narrows down the array size to small partions to optimize the sort. When not used
    the quicksort can waste time using recursion when not needed or even have stack overflow
    problems, which is why switching to quick sort is a good option.
    Other good solutions could also be using sorts other than quick sort such as heap sort
    to sort the smaller partitions. Also in the case that small partitions already happen to be sorted
    insertions sort would be the fastest way to "sort" those partitions with a complexity
    of just O(n).
    
    
    */
//--------------------part 2--------------------------------
  
    ofstream myFile2;
    
    myFile2.open ("/Users/omerkatz/Desktop/CS2C/CS2C_Assignment8_OmerKatz/CS2C_Assignment8_OmerKatz/CS2C_Assignment8_Part2.csv");
    
    
    myFile2 << "Size" << "," << "QuickSort" << "," << "InsertionSort" << ","
    << "HeapSort" << "," << "MergeSort" << endl;
    
    
   
    FHvector<int> fhVectorOfInts;
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts.push_back(rand()%1000000);
    }
   
    myFile2 <<  "40000" <<",";
    startTime = clock();
    quickSort(fhVectorOfInts);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
    
    fhVectorOfInts.clear();
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts.push_back(rand()%1000000);
    }
    
    startTime = clock();
    insertionSort(fhVectorOfInts);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
    
    fhVectorOfInts.clear();
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts.push_back(rand()%1000000);
    }
    
    startTime = clock();
    heapSort(fhVectorOfInts);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
    
    fhVectorOfInts.clear();
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts.push_back(rand()%1000000);
    }
   
    startTime = clock();
    mergeSort(fhVectorOfInts);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << endl;
    
    
    
    FHvector<int> fhVectorOfInts1;
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts1.push_back(rand()%1000000);
    }
   
    myFile2 <<  "80000" <<",";
    startTime = clock();
    quickSort(fhVectorOfInts1);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
    
    fhVectorOfInts1.clear();
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts1.push_back(rand()%1000000);
    }
    
    startTime = clock();
    insertionSort(fhVectorOfInts1);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
    
    fhVectorOfInts1.clear();
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts1.push_back(rand()%1000000);
    }
    
    startTime = clock();
    heapSort(fhVectorOfInts1);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
    
    fhVectorOfInts1.clear();
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts1.push_back(rand()%1000000);
    }
    
    startTime = clock();
    mergeSort(fhVectorOfInts1);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << endl;
    
   
    FHvector<int> fhVectorOfInts2;
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts2.push_back(rand()%1000000);
    }
    
    myFile2 <<  "120000" <<",";
    startTime = clock();
    quickSort(fhVectorOfInts2);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
   
    fhVectorOfInts2.clear();
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts2.push_back(rand()%1000000);
    }
    
    startTime = clock();
    insertionSort(fhVectorOfInts2);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
    
    
    fhVectorOfInts2.clear();
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts2.push_back(rand()%1000000);
    }
    
    startTime = clock();
    heapSort(fhVectorOfInts2);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
    
    fhVectorOfInts2.clear();
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts2.push_back(rand()%1000000);
    }
    
    startTime = clock();
    mergeSort(fhVectorOfInts2);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << endl;
   
    FHvector<int> fhVectorOfInts3;
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts3.push_back(rand()%1000000);
    }
    
    myFile2 <<  "160000" <<",";
    startTime = clock();
    quickSort(fhVectorOfInts3);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
    
    fhVectorOfInts3.clear();
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts3.push_back(rand()%1000000);
    }
   
    startTime = clock();
    insertionSort(fhVectorOfInts3);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
    
    fhVectorOfInts3.clear();
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts3.push_back(rand()%1000000);
    }
    
    startTime = clock();
    heapSort(fhVectorOfInts3);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << ",";
    
    fhVectorOfInts3.clear();
    
    for(int i = 0; i < 40000; i++)
    {
        fhVectorOfInts3.push_back(rand()%1000000);
    }
    
    startTime = clock();
    mergeSort(fhVectorOfInts3);
    stopTime = clock();
    myFile2 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << endl;
    
    
    /*
     quicksort, merge sort, and heap sort all have a O(nlog(n))
     
     insertion sort has a O(n^2)
     
     from all the tests quick sort was much better than any of the other sorts.
     This means that the pivot selections must have been good since the algorithm
     was very efficient. Depending on the input and pivot selection, Quick sort can be faster
     or slower, and this seems like one of the cases that quick sort was faster and maintained
     close to nlog(n) complexity.Heap sort was the second best and merge sort
     was right behind, probably because they have the same time complexity.
     
     
     */
    
}














