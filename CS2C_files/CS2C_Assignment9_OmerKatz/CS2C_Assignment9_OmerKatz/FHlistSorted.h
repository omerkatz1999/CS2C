// Sorted Linked List
// A linked list that maintains sorted order
// Ian Cramer and Joanna Lankester 
// 11/7/18
//



// ---------- Header Section ----------
#pragma once
#ifndef FHLISTSORTED_H
#define FHLISTSORTED_H

#include "FHlist.h"

using namespace std;
// ---------- End Header Section ----------



// Sorted List Class
// Derived from standard FHlist
template <class Comparable>
class FHlistSorted : public FHlist<Comparable>
{
public:
  // Insert Sorted
  void insert( const Comparable &x );
  
protected:
   void push_front( const Comparable &x ) { insert(x); }
   void push_back( const Comparable &x ) { insert(x); }
};

// Sorted Insert Method
template <class Comparable>
void FHlistSorted<Comparable>::insert( const Comparable &x )
{
  // Empty List Case
  if (this->empty())
  {
    FHlist<Comparable>::push_front(x);
    return;
  }
  // List not empty, find the correct position
  typename FHlistSorted<Comparable>::iterator iter = this->begin();
  for (iter; iter != this->end(); iter++)
  {
    if ( x < *iter )
      break;
  }
  FHlist<Comparable>::insert(iter, x);
}
// End Sorted List Class



#endif
// End of Program


