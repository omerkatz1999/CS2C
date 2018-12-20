//
//  main.cpp
//  CS2C_Assignment6_OmerKatz
//
//  Created by Omer Katz on 11/12/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Gene.h"
#include "FHhashQP.h"


template <class Object, typename KeyType>

class FHhashQPwFind: public FHhashQP<Object>

{

public:
    //returns the found object, or throws a NotFoundException
    const Object find(const KeyType & key);

private:
    //
    int myHashKey(const KeyType & key) const;
    
    int findPosKey( const KeyType & key ) const ;
    
public:
    class NotFoundException{};
};





/*
string getKey(const Gene &g) {

    return g.getName();

}
 */


int getKey(const Gene &g) {
    
    return g.getStartingBasePair();
    
}



/*
 int Hash( const string & key )
 
 {
 
 unsigned int k, retVal = 0;
 
 
 
 for(k = 0; k < key.length( ); k++ )
 
 retVal = 37 * retVal + key[k];
 
 
 
 return retVal;
 
 }
*/



int Hash( int key )

{
    
    return key;
    
}


// we have to define how to get the number to hash for a Gene object

int Hash( const Gene & g )

{
    return Hash(getKey(g));
}


template <class Object, typename KeyType>
int FHhashQPwFind< Object, KeyType>::myHashKey( const KeyType & key) const
{
    int hashVal;
    
    hashVal = Hash(key) % this->mTableSize;
    if(hashVal < 0)
        hashVal += this->mTableSize;
    
    return hashVal;
}


// for int
template <class Object , typename KeyType>
int FHhashQPwFind< Object, KeyType>::findPosKey( const KeyType & key ) const
{
    int kthOddNum = 1;
    int index = myHashKey(key);
    
    while ( this->mArray[index].state != FHhashQP<Object>::EMPTY
           && this->mArray[index].data.getStartingBasePair() != key )
    {
        index += kthOddNum;  // k squared = (k-1) squared + kth odd #
        kthOddNum += 2;   // compute next odd #
        if ( index >= this->mTableSize )
            index -= this->mTableSize;
    }
    
    return index;
}

/*
 //for string
 template <class Object , typename KeyType>
 int FHhashQPwFind< Object, KeyType>::findPosKey( const KeyType & key ) const
 {
    int kthOddNum = 1;
    int index = myHashKey(key);
 
    while ( this->mArray[index].state != FHhashQP<Object>::EMPTY
    && this->mArray[index].data.getName() != key )
    {
        index += kthOddNum;  // k squared = (k-1) squared + kth odd #
        kthOddNum += 2;   // compute next odd #
        if ( index >= this->mTableSize )
        index -= this->mTableSize;
    }
 
    return index;
 }
*/


//for int
template <class Object , typename KeyType>
const Object FHhashQPwFind< Object, KeyType>::find(const KeyType & key){
    int x = findPosKey(key);
    
    if( this->mArray[x].data.getStartingBasePair() == key)
    {
        return this->mArray[x].data;
    }
    
    throw NotFoundException();

        
    
}


/*
 //for string
 
 template <class Object , typename KeyType>
 const Object FHhashQPwFind< Object, KeyType>::find(const KeyType & key)
 {
    int x = findPosKey(key);
 

    if( this->mArray[x].data.getName() == key )
    {
 
        return this->mArray[x].data;
 
    }
 
    throw NotFoundException();
 
 }
 */

/*
// string main
int main()

{
    //string main

     FHhashQPwFind<Gene, string> hashTable; // for any string equality
    
    Gene geneResult;
    
    GeneDataReader geneInput("/Users/omerkatz/Downloads/human_genes.txt");
    
    
    if (geneInput.readError()) {
        
        cout << "couldn't open " << geneInput.getFileName() << " for input.\n";
        
        exit(1);
        
    }
    
    for( int i = 0; i < geneInput.getNumGenes(); i++)
    {
        hashTable.insert(geneInput[i]);
    }
    
    
    cout << geneInput.getFileName() << endl;
    
    cout << geneInput.getNumGenes() << endl;
    
    
    
    
    const int NUM_RANDOM_INDICES = 25;
    
    int randomIndices[NUM_RANDOM_INDICES];
    
    float randFrac;
    
    for( int i = 0; i < 25; i++)
    {
        randFrac = rand() % geneInput.getNumGenes();
        randomIndices[i] = randFrac;
        cout << geneInput[randFrac].toString() << endl;
    }
    
    
    
    
    // create a QP hash table of Genes ...
    
    // generate some random indices into the GeneDataReader vector ...
    
    // insert all genes into the hash table  ...
    
    // display NUM_RANDOM_INDICES genes from array ...
    
    
    
    
    
    // attempt to find on the selected key
    
    
    
    cout << "The same random genes from the hash table " << endl;
    
    for (int k = 0; k < NUM_RANDOM_INDICES; k++)
        
    {
        
        try
        
        {
            
            geneResult = hashTable.find(geneInput[randomIndices[k]].getName());
            
            cout << "GENE FOUND: " << geneResult.toString() << endl;
            
        }
        
        catch (...)
        
        {
            
            cout << "this gene is not in the hash table, still needs to be discovered";
            
        }
        
        cout << endl;
        
    }
    
    
    
    
    // test known failures exceptions:
    
    try
    
    {
        
        geneResult = hashTable.find( "s" );
        geneResult = hashTable.find( "human" );
        geneResult = hashTable.find( "123456" );
        
        //geneResult = hashTable.find( "PenguinGene123" );
        
        
    }
    
    catch (...)
    
    {
        
        cout << "that is not a human gene!" << endl;
        
    }
    
    
    try
    
    {
        
        geneResult = hashTable.find( "human-gene" );
        
        //geneResult = hashTable.find( "PenguinGene123" );
        
        
    }
    
    catch (...)
    
    {
        
        cout << "that is not a human gene!" << endl;
        
    }
    
    
    
    try
    
    {
        
        geneResult = hashTable.find( "MIR3647" );
        
        //geneResult = hashTable.find( "PenguinGene123" );
        
        
    }
    
    catch (...)
    
    {
        
        cout << "that is not a human gene!" << endl;
        
    }
    
    
}
*/

/*
 
 string run:
 
 /Users/omerkatz/Downloads/human_genes.txt
 41003
 CHCHD2P6 starting at base pair 15604597
 DNAJC25 starting at base pair 111631352
 CELSR1 starting at base pair 46360834
 ABHD17AP3 starting at base pair 214605470
 MIR6129 starting at base pair 49288346
 PSMB9 starting at base pair 32877612
 MAGEB16 starting at base pair 35798342
 MUC6 starting at base pair 1019669
 MIR6837 starting at base pair 44051766
 MAP4K5 starting at base pair 50418501
 PDGFA starting at base pair 497258
 PRYP3 starting at base pair 23681440
 PBX2 starting at base pair 32184741
 LY6G6D starting at base pair 31694313
 CBY3 starting at base pair 179679567
 MYH4 starting at base pair 10443290
 DDX50P2 starting at base pair 154352136
 RN7SL489P starting at base pair 75268430
 MIR3646 starting at base pair 44408120
 MIR202HG starting at base pair 133246478
 GPR152 starting at base pair 67451301
 RPL18AP7 starting at base pair 38526802
 MIR3672 starting at base pair 121370972
 IQCF6 starting at base pair 51778561
 RRN3P3 starting at base pair 21843633
 The same random genes from the hash table
 GENE FOUND: CHCHD2P6 starting at base pair 15604597
 
 GENE FOUND: DNAJC25 starting at base pair 111631352
 
 GENE FOUND: CELSR1 starting at base pair 46360834
 
 GENE FOUND: ABHD17AP3 starting at base pair 214605470
 
 GENE FOUND: MIR6129 starting at base pair 49288346
 
 GENE FOUND: PSMB9 starting at base pair 32934853
 
 GENE FOUND: MAGEB16 starting at base pair 35798342
 
 GENE FOUND: MUC6 starting at base pair 1012821
 
 GENE FOUND: MIR6837 starting at base pair 44051766
 
 GENE FOUND: MAP4K5 starting at base pair 50418501
 
 GENE FOUND: PDGFA starting at base pair 497258
 
 GENE FOUND: PRYP3 starting at base pair 23681440
 
 GENE FOUND: PBX2 starting at base pair 32133204
 
 GENE FOUND: LY6G6D starting at base pair 31783184
 
 GENE FOUND: CBY3 starting at base pair 179678583
 
 GENE FOUND: MYH4 starting at base pair 10443290
 
 GENE FOUND: DDX50P2 starting at base pair 154352136
 
 GENE FOUND: RN7SL489P starting at base pair 75268430
 
 GENE FOUND: MIR3646 starting at base pair 44408120
 
 GENE FOUND: MIR202HG starting at base pair 133246478
 
 GENE FOUND: GPR152 starting at base pair 67451301
 
 GENE FOUND: RPL18AP7 starting at base pair 38526802
 
 GENE FOUND: MIR3672 starting at base pair 121370972
 
 GENE FOUND: IQCF6 starting at base pair 51778561
 
 GENE FOUND: RRN3P3 starting at base pair 22418672
 
 that is not a human gene!
 that is not a human gene!
 that is not a human gene!
 
 */


int main()

{
 
 //int main
    
    

    FHhashQPwFind<Gene, int> hashTable; // for ID equality
    
    // FHhashQPwFind<Gene, string> hashTable; // for any string equality
    
    
    
    
 
    
    Gene geneResult;
    
    GeneDataReader geneInput("/Users/omerkatz/Downloads/human_genes.txt");
    
   
    if (geneInput.readError()) {
        
        cout << "couldn't open " << geneInput.getFileName() << " for input.\n";
        
        exit(1);
        
    }
    
    for( int i = 0; i < geneInput.getNumGenes(); i++)
    {
        hashTable.insert(geneInput[i]);
    }
        
        
    cout << geneInput.getFileName() << endl;
    
    cout << geneInput.getNumGenes() << endl;
    
    
    
    
    const int NUM_RANDOM_INDICES = 25;
    
    int randomIndices[NUM_RANDOM_INDICES];
    
    float randFrac;
    
    for( int i = 0; i < 25; i++)
    {
        randFrac = rand() % geneInput.getNumGenes();
        randomIndices[i] = randFrac;
        cout << geneInput[randFrac].toString() << endl;
    }
    
    
    
    
    // create a QP hash table of Genes ...
    
    // generate some random indices into the GeneDataReader vector ...
    
    // insert all genes into the hash table  ...
    
    // display NUM_RANDOM_INDICES genes from array ...
    

    
    
    
    // attempt to find on the selected key
    
    
    
    cout << "The same random genes from the hash table " << endl;
    
    for (int k = 0; k < NUM_RANDOM_INDICES; k++)
        
    {
        
        try
        
        {
            
            geneResult = hashTable.find(geneInput[randomIndices[k]].getStartingBasePair());
            
            cout << "GENE FOUND: " << geneResult.toString() << endl;
            
        }
        
        catch (...)
        
        {
            
            cout << "this gene is not in the hash table, still needs to be discovered";
            
        }
        
        cout << endl;
        
    }
    
    
    
    
    // test known failures exceptions:
    
    try
    
    {
        
        geneResult = hashTable.find( -3 );
        
        //geneResult = hashTable.find( "PenguinGene123" );
        
        
    }
    
    catch (...)
    
    {
        
        cout << "that is not a human gene!" << endl;
        
    }
    
    try
    
    {
        
        geneResult = hashTable.find( 100 );
    
        
        
    }
    
    catch (...)
    
    {
        
        cout << "that is not a human gene!" << endl;
        
    }
    
    try
    
    {
        
        geneResult = hashTable.find( 1234 );
        
        //geneResult = hashTable.find( "PenguinGene123" );
        
        
    }
    
    catch (...)
    
    {
        
        cout << "that is not a human gene!"<< endl;
        
    }
 
    
    
    
    
}

 

/*  Int Main Run
 
 /Users/omerkatz/Downloads/human_genes.txt
 41003
 CHCHD2P6 starting at base pair 15604597
 DNAJC25 starting at base pair 111631352
 CELSR1 starting at base pair 46360834
 ABHD17AP3 starting at base pair 214605470
 MIR6129 starting at base pair 49288346
 PSMB9 starting at base pair 32877612
 MAGEB16 starting at base pair 35798342
 MUC6 starting at base pair 1019669
 MIR6837 starting at base pair 44051766
 MAP4K5 starting at base pair 50418501
 PDGFA starting at base pair 497258
 PRYP3 starting at base pair 23681440
 PBX2 starting at base pair 32184741
 LY6G6D starting at base pair 31694313
 CBY3 starting at base pair 179679567
 MYH4 starting at base pair 10443290
 DDX50P2 starting at base pair 154352136
 RN7SL489P starting at base pair 75268430
 MIR3646 starting at base pair 44408120
 MIR202HG starting at base pair 133246478
 GPR152 starting at base pair 67451301
 RPL18AP7 starting at base pair 38526802
 MIR3672 starting at base pair 121370972
 IQCF6 starting at base pair 51778561
 RRN3P3 starting at base pair 21843633
 The same random genes from the hash table
 GENE FOUND: CHCHD2P6 starting at base pair 15604597
 
 GENE FOUND: DNAJC25 starting at base pair 111631352
 
 GENE FOUND: CELSR1 starting at base pair 46360834
 
 GENE FOUND: ABHD17AP3 starting at base pair 214605470
 
 GENE FOUND: MIR6129 starting at base pair 49288346
 
 GENE FOUND: PSMB9 starting at base pair 32877612
 
 GENE FOUND: MAGEB16 starting at base pair 35798342
 
 GENE FOUND: MUC6 starting at base pair 1019669
 
 GENE FOUND: MIR6837 starting at base pair 44051766
 
 GENE FOUND: MAP4K5 starting at base pair 50418501
 
 GENE FOUND: PDGFA starting at base pair 497258
 
 GENE FOUND: PRYP3 starting at base pair 23681440
 
 GENE FOUND: PBX2 starting at base pair 32184741
 
 GENE FOUND: LY6G6D starting at base pair 31694313
 
 GENE FOUND: CBY3 starting at base pair 179679567
 
 GENE FOUND: MYH4 starting at base pair 10443290
 
 GENE FOUND: DDX50P2 starting at base pair 154352136
 
 GENE FOUND: RN7SL489P starting at base pair 75268430
 
 GENE FOUND: MIR3646 starting at base pair 44408120
 
 GENE FOUND: MIR202HG starting at base pair 133246478
 
 GENE FOUND: GPR152 starting at base pair 67451301
 
 GENE FOUND: RPL18AP7 starting at base pair 38526802
 
 GENE FOUND: MIR3672 starting at base pair 121370972
 
 GENE FOUND: IQCF6 starting at base pair 51778561
 
 GENE FOUND: RRN3P3 starting at base pair 21843633
 
 that is not a human gene!
 that is not a human gene!
 that is not a human gene!
 
 */









