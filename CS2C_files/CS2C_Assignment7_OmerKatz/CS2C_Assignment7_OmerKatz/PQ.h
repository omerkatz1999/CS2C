//
//  PQ.hpp
//  CS2C_Assignment7_OmerKatz
//
//  Created by Omer Katz on 11/22/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#ifndef PQ_hpp
#define PQ_hpp

#include <stdio.h>

// PQ.h

#include <iostream>
#include "FHlist.h"

// ------------- base class -----------------

template <class Comparable>
class PQ {
protected:
    int mSize;
    
public:
    virtual void insert( const Comparable & x ) = 0;
    virtual Comparable & remove() = 0;
    bool empty() const { return mSize == 0; }
};

// ------------- exception class -----------------

class EmptyPQException{};

// ------------- derived class prototypes -----------------PQsortedList and PQunsortedList

// sorted list

template <class Comparable>
class PQsortedList : public PQ<Comparable> {

protected:
     FHlist<Comparable> mList;
    
public:
    virtual void insert( const Comparable & x );
    virtual Comparable & remove();

};



// unsorted list

template <class Comparable>
class PQunsortedList : public PQ<Comparable> {
    
protected:
    FHlist<Comparable> mList;
    
public:
    virtual void insert( const Comparable & x );
    virtual Comparable & remove();
   
};


// ------------- derived class implementations -----------------

// sorted implemintation:

template <class Comparable>
void PQsortedList<Comparable>:: insert( const Comparable & x )
{
    if(mList.empty() || (mList.front() > x))
    {
        mList.push_front(x);
        return;
    }
    
    
    typename FHlist<Comparable> :: iterator iter;
    
    
    for(iter = mList.begin(); iter != mList.end(); iter++)
    {
        if(*iter > x)
        {
            mList.insert(iter, x);
            return;
        }
    
    }
   
    mList.push_back(x);
    return;

    
  
}


template <class Comparable>
Comparable & PQsortedList<Comparable>:: remove()
{
   
    static Comparable dataFront;
    
    if(mList.empty())
    {
        throw EmptyPQException();
    }
   
    dataFront = mList.front();
    
    mList.pop_front();
    
    return dataFront ;
    
}


//unsorted

template <class Comparable>
void PQunsortedList<Comparable>:: insert( const Comparable & x )
{
    mList.push_front(x);
}

template <class Comparable>
Comparable & PQunsortedList<Comparable>:: remove()
{
    if(mList.empty())
    {
        throw EmptyPQException();
    }
    
    typename FHlist<Comparable> :: iterator iter, iter2;
    
    static Comparable smallest;
    
    smallest = mList.front();
    iter2 = mList.begin();
    
    for(iter = mList.begin(); iter != mList.end(); iter++)
    {
        if(*iter < smallest)
        {
            smallest = *iter;
            iter2 = iter;
        }
    }
    
    mList.erase(iter2);
 
    
    return smallest;
    
}





#endif /* PQ_hpp */
