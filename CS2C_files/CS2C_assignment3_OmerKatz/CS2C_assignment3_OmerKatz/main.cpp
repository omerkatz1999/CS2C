//
//  main.cpp
//  CS2C_assignment3_OmerKatz
//
//  Created by Omer Katz on 10/13/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAT_SIZE = 800;

typedef float* DynMat[MAT_SIZE];

DynMat mDyn, nDyn, ansDyn;



void matMultDyn( const DynMat & matA,  const DynMat & matB, DynMat & matC, int size)
{
    
    for( int r = 0; r < size; r++)
    {
        for ( int c = 0; c < size; c++)
        {
            double dotProduct = 0;
            
            for(int x = 0, y = 0; x < size; x++, y++)
            {
                dotProduct += matA[x][c] * matB[r][y];
           
            }
            
            matC[r][c] = dotProduct;
        }
     }
    
}

void matShowDyn( const DynMat & matA, int start, int size)
{
    
    for(int i = 0, r = start ; i < size; r++, i++)
    {
        for(int j = 0, c = start; j < size; c++, j++)
        {
           cout << fixed <<setprecision(3) << matA[r][c] << "  ";
        }
        
        cout << endl;
    }
}


// main

int main()
{
    int r, c;
    clock_t startTime, stopTime;
    double randFrac;
    int randRow, randCol, smallPercent;
    
    // non-sparse dynamic matrix
    DynMat matDyn, matDynAns;
    
    
    // allocate rows and initialize to 0
    for (r = 0; r < MAT_SIZE; r++)
    {
        
        matDyn[r] = new float [MAT_SIZE];
        matDynAns[r] = new float [MAT_SIZE];
        
        for (c = 0; c < MAT_SIZE; c++)
        {
            matDyn[r][c] = 0;
            matDynAns[r][c] = 0;
        }
    }
    
    matDyn[0][0] = 0.5;
    
    matDyn[4][4] = 0.2;
    
    cout << endl << endl;
    
    
    double randDouble1;
    double randDouble2;
    
    // generate small% non-default values bet .1 and 1
    smallPercent = MAT_SIZE/20. * MAT_SIZE;  // div by 20. means 5%, of course
    for (r = 0; r < smallPercent; r++)
    {
        
        randRow = rand()% MAT_SIZE;
        randCol = rand()% MAT_SIZE;
        
        randDouble1 = rand()*1.0/RAND_MAX;
      //randDouble2 = rand()*1.0/RAND_MAX;
        
        matDyn[randRow][randCol] = randDouble1;
       // matDynAns[randRow][randCol] = randDouble2;
        
    }
    
    
    // 10x10 submatrix in lower right
   matShowDyn(matDyn, MAT_SIZE - 10, 10);
    
    cout << endl << endl;
    
    startTime = clock();  // ------------------ start
    matMultDyn(matDyn, matDyn, matDynAns, MAT_SIZE);
    stopTime = clock();  // ---------------------- stop
    
    matShowDyn(matDynAns, MAT_SIZE - 10, 10);
    cout << "\nSize = " <<  MAT_SIZE << " Dyn Array Mult Elapsed Time: "
    << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    // clean up
    for (r = 0; r < MAT_SIZE; r++)
    {
        delete matDyn[r];
        delete matDynAns[r];
    }
        
        

}


/*
 
 
 0.500  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.053  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.000  0.000  0.200  0.000  0.000  0.000  0.679  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.756
 0.219  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.519  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 
 
 0.250  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.003  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.149  0.000  0.000  0.000  0.040  0.000  0.000  0.000  0.136  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.392  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.109  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.260  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 
 Size = 10 Dyn Array Mult Elapsed Time: 0.000 seconds.
 
 
 
 --------------------------------------------------------------------

 
 
 0.000  0.000  0.253  0.000  0.577  0.000  0.569  0.000  0.000  0.000
 0.000  0.000  0.036  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.000  0.476  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.909  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.000  0.379  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.662  0.000  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 0.000  0.000  0.796  0.000  0.000  0.000  0.000  0.964  0.000  0.000
 0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000  0.000
 
 
 0.286  0.272  1.134  0.389  0.328  0.000  0.006  1.799  0.216  0.670
 0.501  1.075  0.762  2.057  1.850  1.116  0.848  1.289  0.422  1.437
 0.759  2.420  1.337  1.681  0.213  0.757  2.398  0.011  0.871  0.477
 0.825  2.201  0.631  1.124  0.493  0.264  0.423  0.740  1.268  0.703
 0.693  0.651  0.955  1.170  1.428  0.158  0.060  0.329  0.166  0.080
 1.091  1.449  0.480  1.348  0.970  0.318  1.432  1.025  0.432  0.408
 1.971  0.010  0.666  0.873  0.535  0.098  2.149  0.045  0.725  1.506
 1.103  0.323  1.377  1.015  0.151  0.291  1.581  0.905  1.866  2.165
 0.893  0.651  0.625  1.033  0.699  0.820  1.324  1.199  0.371  0.595
 1.464  0.562  0.550  1.618  0.899  0.786  0.534  1.122  1.170  1.429
 
 Size = 1600 Dyn Array Mult Elapsed Time: 28.387 seconds.
 
 
*/


