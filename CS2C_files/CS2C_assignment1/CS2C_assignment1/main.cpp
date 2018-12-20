// Main file for search example


#include <iostream>
using namespace std;

#include "iTunes.h"
//#include "itunes_file.txt"

// for timing our algorithms
#include <time.h>
#include <cstdlib>

/*
 
 added bool exist array
 save best compliment or sublist
 
 
 
 */



template <class LTYPE>
class Sublist
{
public:
    Sublist();
    Sublist(vector<LTYPE> *orig);
    Sublist addItem( int indexOfItemToAdd );
    //Sublist entireDataSet();
    void showSublist() const;
    int getSum() const { return sum; }
    vector<int>  getIndices();
    
    //virtual ~Sublist();
    // Sublist& operator=(const Sublist& rhs);
    // Sublist(const Sublist& listToCopy);
    
    
    
private:
    int sum;
    vector<LTYPE> *originalObjects;
    vector<int> indices;
    
};



template <class LTYPE>
Sublist< LTYPE >:: Sublist()
{
    sum = 0;
    originalObjects = nullptr;
    
    
}

template <class LTYPE>
Sublist<LTYPE> :: Sublist(vector<LTYPE> *orig)
{
    this-> originalObjects = orig;
    
    sum = 0;
    
    
}


template < class LTYPE>
Sublist<LTYPE>  Sublist<LTYPE>:: addItem( int indexOfItemToAdd )
{
    Sublist<LTYPE>  newSublist;
    
    newSublist = *this;
    
    newSublist.indices.push_back(indexOfItemToAdd);
    
    newSublist.sum = this-> sum + originalObjects->at(indexOfItemToAdd);
    
    
    return newSublist;
    
}

template < class LTYPE>
vector<int>  Sublist<LTYPE>:: getIndices()
{
    
    return indices;
}



template < class LTYPE>
void Sublist<LTYPE> :: showSublist() const {
    
    
    cout << "Sublist---------------- " << endl << endl;
    
    cout << "sum:" << this->sum << endl << endl;
    
    
    if( indices.size() == 0 )
    {
        cout << "{ }" << endl;
    }
    
    else
    {
        
        for (int i = 0; i < indices.size(); i++)
        {
            
            cout <<" [" << i << "]" << " = "
            << originalObjects->at(indices[i]);
            
            if( i < (indices.size()-1))
            {
                cout << ",";
            }
            
            
        }
        cout << endl;
    }
    
    cout << endl << endl;
    
}

ostream & operator << (ostream & str, const iTunesEntry &song)
{
    str << song.getTitle() << " by " << song.getArtist() << "(" << song.getTime() << ")" << endl;
    return str;
}


int operator+(int sum, const iTunesEntry& song)
{
    return sum + song.getTime();
}

bool operator<( const iTunesEntry& song, int target)
{
    return (song.getTime() < target);
}

bool operator==( const iTunesEntry& song, int target)
{
    return (song.getTime() == target);
}





template < class LTYPE>
void subsetSumInt(int TARGET, vector<LTYPE> dataSet)
{
    subsetSum( TARGET, dataSet);
}

template < class LTYPE>
void subsetSumTunes(int TARGET, vector<LTYPE> dataSet)
{
    subsetSum( TARGET, dataSet);
}






template < class LTYPE>
void subsetSum(int TARGET, vector<LTYPE> dataSet) {
    
    bool doesExist[TARGET];
    
    for(int i = 0; i < TARGET; i++)
    {
        doesExist[i] = false;
    }
    
    vector<Sublist<LTYPE>> choices;
    
    vector<LTYPE> * dataSetPTR = & dataSet;
    
    Sublist<LTYPE> closestSublist;
    
    
    typename vector<LTYPE>::iterator iterDataSet, intIterBest;
    
    vector<LTYPE> newDataSet;
    
    vector<LTYPE> * newDataSetPTR = & newDataSet;
    
    int totalSum = 0;
    
    for(int i = 0; i < dataSet.size(); i++)
    {
        
        if( dataSet[i] < TARGET)
        {
            newDataSet.push_back(dataSet[i]);
            totalSum = totalSum + dataSet[i];
        }
        else if (dataSet[i] == TARGET)
        {
            Sublist<LTYPE> closestSublist(dataSetPTR);
            closestSublist.addItem(i).showSublist();
            return;
            
        }
    }
    
    if(totalSum <= TARGET)
    {
        
        cout << "sublist--------" << endl << endl;
        
        cout<< "sum: " << totalSum << endl;
        
        for ( int i = 0; i < newDataSet.size(); i++)
        {
            cout <<" [" << i << "]" << " = " << newDataSet[i];
        }
        
        //solution.entireDataSet();
        
        
        //solution.showSublist();
        return;
    }
    
    Sublist<LTYPE> emptySublist(newDataSetPTR);
    
    choices.push_back(emptySublist);
    
    // creating all sublists
    
    long choicesSize = 0;
    
    Sublist<LTYPE> addedSublist;
    
    
    
    int i = 0;
    
    for ( iterDataSet = newDataSet.begin(); iterDataSet != newDataSet.end(); iterDataSet++, i++)
    {
        choicesSize = choices.size();
        
        for( int j = 0; j < choicesSize; j++)
        {
            //duplicates sublist and adds the next item if its less then target
            if(choices[j].getSum() + newDataSet[i] < TARGET)
            {
                
                //checks the compliment of the sum and returns if found
                if(totalSum - (choices[j].getSum() + newDataSet[i]) == TARGET)
                {
                    
                    Sublist< LTYPE> currSublist = (choices[j]);
                    Sublist< LTYPE> complimentSublist(newDataSetPTR);
                    
                    for(int c = 0; c < newDataSet.size(); c++)
                    {
                        bool cInArray = false;
                        for (int m = 0; m < currSublist.getIndices().size() ; m++)
                        {
                            if(currSublist.getIndices().size() != 0)
                            {
                                if(c == currSublist.getIndices()[m] || i == c )
                                {
                                    cInArray = true;
                                    break;
                                }
                            }
                            else{
                                if( i == c )
                                {
                                    cInArray = true;
                                    break;
                                }
                            }
                            
                        }
                        
                        if(!cInArray)
                        {
                            complimentSublist = complimentSublist.addItem(c);
                        }
                        
                    }
                    
                    complimentSublist.showSublist();
                    
                    return;
                }
                
                if(!(doesExist[  (choices[j].getSum() + newDataSet[i])  ]))
                {
                    addedSublist = ((choices[j]).addItem(i));
                    choices.push_back(addedSublist);
                    doesExist[choices[j].getSum() + newDataSet[i]] = true;
                }
                
            }
            else if(choices[j].getSum() + newDataSet[i] == TARGET)
            {
                addedSublist = ((choices[j]).addItem(i));
                closestSublist = addedSublist;
                closestSublist.showSublist();
                return;
            }
            
            
            
            // adds new sublist to the choices vector
            
        }
    }
    
    for(int i = 0; i < choices.size(); i++)
    {
        if((choices[i].getSum() > closestSublist.getSum()) && choices[i].getSum() < TARGET)
        {
            closestSublist = choices[i];
        }
        else if( choices[i].getSum() == TARGET )
        {
            choices[i].showSublist();
            return;
        }
    }
    
    closestSublist.showSublist();
    
}


// --------------- main ---------------

 int main()
 {
 
 
 vector<int> dataSet;
 
 dataSet.push_back(1);
 dataSet.push_back(2);
 dataSet.push_back(3);
 dataSet.push_back(4);
 
 
 int dataBase =400;
 
 srand((unsigned)time(0));
 
 for( int i = 0 ; i < dataBase ; i++)
 {
 
 int random_integer = rand()%1000;
 dataSet.push_back(random_integer);
 
 }
 
 
 
 
 int target = 80000;
 
 cout << "target: " << target << endl << endl;
 
 clock_t startTime, stopTime;
 startTime = clock();
 
 //subsetSumInt(target, dataSet2 );
 
 subsetSum(target, dataSet );
 
 // how we determine the time elapsed -------------------
 stopTime = clock();
 
 cout << "\nAlgorithm Elapsed Time: "
 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
 << " seconds." << endl << endl;
 
 
 
 
 }


/* --- run for int main
 
 target: 2000
 
 Sublist----------------
 
 sum:2000
 
 [0] = 933, [1] = 549, [2] = 140, [3] = 212, [4] = 166
 
 
 
 Algorithm Elapsed Time: 0.019408 seconds.
 */

/*
 int main()

 {
 //22109 would be very slow
 const int TARGET = 12000;
 
 vector<iTunesEntry> dataSet;
 
 
 
 // read the data - you may need to modify with a full filepath
 
 iTunesEntryReader tunes_input("itunes_file.txt");
 
 if (tunes_input.readError())
 
 {
 
 cout << "couldn't open " << tunes_input.getFileName()
 
 << " for input.\n";
 
 exit(1);
 
 }
 
 // time the algorithm -------------------------
 
 clock_t startTime, stopTime;
 
 // create a vector of objects for our own use:
 
 int array_size = tunes_input.getNumTunes();
 
 for (int k = 0; k < array_size; k++)
 
 dataSet.push_back(tunes_input[k]);
 
 startTime = clock();
 
 subsetSumTunes(TARGET, dataSet);
 
 stopTime = clock();
 
 // how we determine the time elapsed -------------------
 
 cout << "\nAlgorithm Elapsed Time: "
 
 << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
 
 << " seconds." << endl << endl;
 
 
 
 return 0;
 
 }
*/

/* ------run for itunes main --------
 
 
 Sublist----------------
 
 sum:20000
 
 [0] = Russian Roulette by Rihanna(228)
 , [1] = Pretending by Eric Clapton(283)
 , [2] = Everybody's In The Mood by Howlin' Wolf(178)
 , [3] = Well That's All Right by Howlin' Wolf(175)
 , [4] = Hot Cha by Roy Buchanan(208)
 , [5] = I'm Just a Prisoner by Janiva Magness(230)
 , [6] = You Were Never Mine by Janiva Magness(276)
 , [7] = Hobo Blues by John Lee Hooker(187)
 , [8] = I Can't Quit You Baby by John Lee Hooker(182)
 , [9] = That's The Homie by Snoop Dogg(343)
 , [10] = Gangsta Luv by Snoop Dogg(257)
 , [11] = Ladies and Gentleman by The Rubyz(201)
 , [12] = Watch the Girl by The Rubyz(192)
 , [13] = Donuts for Benny by Veggie Tales(184)
 , [14] = Our Big Break by Veggie Tales(69)
 , [15] = Brahms: Symphony No. 1 in C Minor Op. 68 by Berliner Philharmoniker(839)
 , [16] = Brahms: Symphony No. 4 in E Minor Op. 98 by Berliner Philharmoniker(800)
 , [17] = Bach: Suite for Cello No. 1 in G Major Prelude by Yo-yo Ma(141)
 , [18] = Simple Gifts by Yo-yo Ma(154)
 , [19] = Alimony by Ry Cooter(175)
 , [20] = France Chance by Ry Cooter(168)
 , [21] = The Road by Aaron Watson(204)
 , [22] = Clone by Terra Incognita(298)
 , [23] = Lizard Skin by Terra Incogni(270)
 , [24] = Bullhead's Psalm by Blue Record(79)
 , [25] = Ogeechee Hymnal by Blue Record(155)
 , [26] = Oblivion by Mastadon(348)
 , [27] = The Bit by Mastadon(295)
 , [28] = Fire Burning by Sean Kingston(239)
 , [29] = My Girlfriend by Sean Kingston(204)
 , [30] = Take Your Shirt Off by T-Pain(228)
 , [31] = Give It All U Got by Lil Jon(218)
 , [32] = What We Talkin' About by Jay-Z(243)
 , [33] = Empire State of Mind by Jay-Z(276)
 , [34] = Think About It by Snoop Dog(217)
 , [35] = Lil' Crips by Snoop Dog(195)
 , [36] = Shuffleboard by Jeff Golub(210)
 , [37] = Goin' On by Jeff Golub(356)
 , [38] = Fish Fare by Jeff Golub(299)
 , [39] = Noites Cariocas by Caraivana(252)
 , [40] = Tico-Tico No Fuba by Caraivana(147)
 , [41] = Monk/Trane by John Patitucci(434)
 , [42] = Sonny Side by John Patitucci(445)
 , [43] = Pirate Jenny by Nina Simone(402)
 , [44] = The Other Woman by Nina Simone(186)
 , [45] = Feeling Good by Nina Simone(177)
 , [46] = A Love Supreme Part 1 by John Coltrane(462)
 , [47] = In a Sentimental Mood by John Coltrane(256)
 , [48] = Dime Si te Vas Con El by AOL Dejando Huellas(204)
 , [49] = Te Amo Tanto by AOL Dejando Huella(192)
 , [50] = Blues On the Corner by McCoy Tyner(367)
 , [51] = Afro Blue by McCoy Tyner(742)
 , [52] = Stronger by Kanye West(311)
 , [53] = Good Life by Kanye West(207)
 , [54] = Black Cow by Steely Dan(310)
 , [55] = Kid Charlemagne by Steely Dan(278)
 , [56] = Haitian Divorce by Steely Dan(351)
 , [57] = Nefertiti by Herbie Hancock(451)
 , [58] = Rockit by Herbie Hancock(325)
 , [59] = Chameleon by Herbie Hancock(941)
 , [60] = Medieval Overture by Return to Forever(313)
 , [61] = Luka by Suzanne Vega(231)
 , [62] = Small Blue Thing by Suzanne Vega(235)
 , [63] = Something to Talk About by Bonnie Raitt(227)
 , [64] = I Can't Make You Love Me by Bonnie Raitt(331)
 , [65] = This Will Be by Natalie Cole(171)
 , [66] = Unforgettable by Natalie Cole(211)
 , [67] = Timothy by Jet(260)
 , [68] = Rip It Up by Jet(200)
 , [69] = Where Did Your Heart Go? by Was (Not Was)(347)
 , [70] = I Blew Up The United States by Was (Not Was)(230)
 
 
 Algorithm Elapsed Time: 0.070803 seconds.
 */









