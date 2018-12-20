//
//  main.cpp
//  CS2C_Assignment2_OmerKatz
//
//  Created by Omer Katz on 10/5/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <ctime>
#include "FHvector.h"
#include "FHlist.h"

using namespace std;

template <class Object>
class MatNode
{

protected:
    
    int col;

public:
    
    Object data;
    // we need a default constructor for lists
    MatNode(int cl = 0, Object dt = Object()) : col(cl), data(dt) {}
    int getCol() const { return col; }
    // not optimized yet for set() = defaultVal;  refer to forums
    const Object & operator=( const Object &x ) { return (data = x);}
};


template <class Object>
class SparseMat
{

public:
    
    SparseMat( int r = 1, int c = 1, const Object & defaultVal = 0);
    const Object & get(int r, int c) const;
    bool set(int r, int c, const Object &x);
    SparseMat <Object> & set(int r, int c);
    SparseMat<Object>& operator=(int setToValue);
    void clear();
    void showSubSquare(int start, int size);
    
protected:
    
    typedef FHlist< MatNode<Object> > MatRow;
    typedef FHvector<MatRow> MasterCol;
    
    MasterCol rows;
    Object defaultVal;
    int rowSize, colSize;
    int rowHolder, colHolder;
    
 

};

class outOfBounds{};




template <class Object>
SparseMat<Object> :: SparseMat( int r, int c, const Object & defaultVal)
{
    if( r >= 1)
    {
         this-> rowSize = r;
    }
    else
    {
        rowSize = 1;
    }
    
    if( r >= 1)
    {
        colSize = c;
    }
    else
    {
        colSize = 1;
    }
    
    this-> defaultVal = defaultVal;
    
    rows.reserve(r);
    rows.resize(r);
    
}

template <class Object>
const Object & SparseMat<Object>:: get(int r, int c) const
{
    if( r > rowSize|| r < 0 || c > colSize || c < 0)
    {
        throw outOfBounds();
    }
    
    else
    {
        typename MatRow :: const_iterator iter;
        
        for(iter = rows[r].begin(); iter != rows[r].end(); iter++ )
        {
            if((*iter).getCol() == c)
            {
                //may need fixing
                return ((*iter).data);
            }
    
        }
       
        return this->defaultVal;
        
    }
    
}


template <class Object>
bool SparseMat<Object>:: set(int r, int c, const Object &x)
{
   
    // comment back in later
    if(r < 0 || r > rowSize-1 || c < 0 || c > colSize-1 )
    {
        return false;
    }
    
    if( x == defaultVal)
    {
        typename MatRow :: iterator iter;
        
        for(iter = rows[r].begin(); iter != rows[r].end(); iter++ )
        {
            if((*iter).getCol() == c)
            {
                rows[r].erase(iter);
            }
            
        }
        return true;
    }
    else
    {
        typename MatRow :: iterator iter;
        
        bool needNewNode = true;
        for(iter = rows[r].begin(); iter != rows[r].end(); iter++ )
        {
            if((*iter).getCol() == c)
            {
                (*iter).data = x;
                needNewNode = false;
            }
            
        }
        
        if(needNewNode)
        {
            rows[r].push_back(MatNode<Object>(c, x));
        }
        

    }
    
    return true;
    
    
}

template < class Object>
void SparseMat<Object>:: clear()

{
    for( int i = 0; i < rowSize; i++)
    {
        rows[i].clear();
    }
}


template < class Object>
void SparseMat<Object> :: showSubSquare(int start, int size)
{
    for( int i = start; i <= start + size-1; i++)
    {
        typename MatRow :: const_iterator iter;
        
        for( int j = start; j <= start+size-1; j++)
        {
            bool isFound = false;
            Object dataTmp;
            for( iter = rows[i].begin(); iter != rows[i].end(); iter++ )
            {
                if(j == (*iter).getCol())
                {
                    isFound = true;
                    dataTmp = (*iter).data;
                }
            }
            
            if(isFound)
            {
                cout << fixed <<setprecision(2) << dataTmp << " ";
            }
            else
            {
                cout << fixed <<setprecision(2) << defaultVal << " ";
            }
        }
        cout << endl;
    }
    
    cout << endl << endl;
}


template < class Object>
SparseMat<Object> & SparseMat<Object> :: set(int r, int c)
{
    this-> rowHolder = r;
    this-> colHolder = c;
    return *this;
}

template < class Object>
SparseMat<Object> & SparseMat<Object> ::operator=(int setToValue)
{
    (*this).set(rowHolder, colHolder, setToValue);
    rowHolder = 0;
    colHolder = 0;
    return *this;
}



// extra credit for assignment 3

template <class Object>
class SparseMatWMult : public SparseMat<double>
{
public:
    SparseMatWMult( int numRows, int numCols );
    bool matMult( SparseMatWMult<Object> & a,  SparseMatWMult<Object> & b );
};




// new constructor (extra credit)
template <class Object>
SparseMatWMult<Object>:: SparseMatWMult( int r, int c ) : SparseMat(r, c , 0.0)
{
    return;
}

// also for the extra credit
template <class Object>
bool SparseMatWMult<Object>:: matMult( SparseMatWMult<Object> & a,  SparseMatWMult<Object> & b )
{
    
    if(this->rowSize <1 || this->colSize <1 )
    {
        return false;
    }
    
    (*this).clear();
    
    
    
    for( int r = 0; r < this->rowSize ; r++)
    {
       // typename MatRow :: iterator iterA;
       // typename MatRow :: iterator iterB;
        
        for ( int C = 0; C < this->rowSize; C++ )
        {
            double currentRowData = a.get(r, C);
            
            if( currentRowData != 0)
            {
                for(int c = 0; c < this->rowSize; c++)
                {
                    double dotProduct = 0;
                    double currentColData = b.get(C, c);
                
                    dotProduct = currentRowData * currentColData;
                
                 
                    if( dotProduct > 0)
                    {
                 
                        typename MatRow :: iterator iterC;
                 
                        bool foundNode = false;
                        for(iterC = this->rows[r].begin(); iterC != this->rows[r].end(); iterC++  )
                        {
                            if(c == (*iterC).getCol())
                            {
                                foundNode = true;
                                (*iterC).data += dotProduct;
                            }
                        }
                 
                        if(!foundNode)
                        {
                     
                            this->rows[r].push_back(MatNode<Object>(c, dotProduct));
                        }
                 
                 
                    }
                }
                 
            }

        }
    }
    
    return true;
}




using namespace std;
/*
int main(int argc, const char * argv[]) {
  
    
    try{
        SparseMat<int> Mat(5,5,0);
        
        Mat.set(0, 0, 3);
        Mat.set(1, 1, 2);
        Mat.set(2, 2, 8);
        Mat.set(3, 3, 9);
        Mat.set(4, 4, 1);
        Mat.set(5, 5, 4);
        
        
        Mat.showSubSquare(0,5);
        
        Mat.showSubSquare(2,3);
        
        
        
        SparseMat<int> Mat2(50,50,0);
        
        Mat2.set(0, 0, 3);
        Mat2.set(1, 1, 2);
        Mat2.set(2, 2, 8);
        Mat2.set(3, 3, 9);
        Mat2.set(4, 4, 1);
        Mat2.set(49, 49, 4);
        
        
        Mat2.showSubSquare(0,50);
        
        
        
        Mat.clear();
        cout << "should be cleared:" << endl;
        cout << Mat.get(3, 2) << endl;
        
        cout << Mat.get(8, 2);
         
    
    }
    
    catch( outOfBounds ){
        cout << "exception thrown" << endl;
        
    }
    
   
}
*/



/*
 int main(int argc, const char * argv[]) {
 
 clock_t startTime, stopTime;
 
 try{
     
 int MAT_SIZE = 800;
 SparseMatWMult<double> Mat(MAT_SIZE, MAT_SIZE);
     
 SparseMatWMult<double> Mat1(MAT_SIZE,MAT_SIZE);

 
 double smallPercent = MAT_SIZE/100. * MAT_SIZE;  // div by 100. should mean 1%, I think
 double randRow;
 double randCol;

 double randDouble1;
     
 for (int r = 0; r < smallPercent; r++)
 {
         randRow = rand()% MAT_SIZE;
         randCol = rand()% MAT_SIZE;
         
         randDouble1 = rand()*1.0/RAND_MAX;
     
         Mat.set(randRow, randCol, randDouble1);
         Mat1.set(randRow, randCol, randDouble1);
     
         
}
     
     
 
     Mat.set(0, 0, 3);
     Mat.set(1, 1, 2);
     Mat.set(2, 2, 8);
     Mat.set(3, 3, 9);
     Mat.set(4, 4, 1);
     
     Mat1.set(1, 0, 1);
     Mat1.set(1, 1, 6);
     Mat1.set(2, 4, 5);
     Mat1.set(3, 1, 7);
     Mat1.set(1, 4, 2);
 
 Mat.showSubSquare(MAT_SIZE-5,5);
     
     
 
 Mat1.showSubSquare(MAT_SIZE-5,5);
     
 SparseMatWMult<double> mult(MAT_SIZE,MAT_SIZE);
     
// mult.showSubSquare(0,MAT_SIZE);
 
 
startTime = clock();  // ------------------ start
mult.matMult(Mat, Mat1);
stopTime = clock();

cout << "\nSize = " <<  MAT_SIZE << " Dyn Array Mult Elapsed Time: "
     << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC << endl;


 
     
 mult.showSubSquare(MAT_SIZE-5,5);
 

 
 
 }
 
 catch( outOfBounds ){
 cout << "exception thrown" << endl;
 
 }
 
 
 }
 */


/*
 
 run with MAT_SIZE = 5
 
 3.00 0.00 0.00 0.00 0.00
 0.00 2.00 0.00 0.00 0.00
 0.00 0.00 8.00 0.00 0.76
 0.00 0.00 0.00 9.00 0.00
 0.00 0.00 0.00 0.00 1.00
 
 
 0.00 0.00 0.00 0.00 0.00
 1.00 6.00 0.00 0.00 2.00
 0.00 0.00 0.00 0.00 5.00
 0.00 7.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 
 
 
 Size = 5 Dyn Array Mult Elapsed Time: 0.00
 0.00 0.00 0.00 0.00 0.00
 2.00 12.00 0.00 0.00 4.00
 0.00 0.00 0.00 0.00 40.00
 0.00 63.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 
 
 -------------------------------------------------
 
 run for MAT_SIZE = 800 (bottom right corner)
 
 
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 
 
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 
 
 
 Size = 800 Dyn Array Mult Elapsed Time: 1.16
 0.00 0.06 0.00 0.00 0.21
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.06 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
-------------------------------------------------
 
 run for MAT_SIZE = 1600 (bottom right corner)

 0.00 0.00 0.66 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.96 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 
 
 0.00 0.00 0.66 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.96 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 
 
 
 Size = 1600 Dyn Array Mult Elapsed Time: 16.32
 0.00 0.06 0.36 0.00 0.17
 0.00 0.00 0.00 0.00 0.00
 0.06 0.00 0.51 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 

-------------------------------------------------
 
 Size = 3200 Dyn Array Mult Elapsed Time: 246.97
 
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 
 
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 0.00 0.00 0.00 0.00 0.00
 
 
 
 Size = 3200 Dyn Array Mult Elapsed Time: 246.97
 0.00 0.00 0.00 0.00 0.00
 0.00 1.05 0.00 0.00 0.00
 0.00 0.00 0.00 0.82 0.00
 0.00 0.22 0.00 0.00 0.00
 0.00 0.00 0.14 0.09 0.00
 



 
 */

