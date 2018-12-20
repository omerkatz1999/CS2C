// By Omer Katz

#include <iostream>
using namespace std;

#include "iTunes.h"
//#include "itunes_file.txt"

// for timing our algorithms
#include <time.h>
#include <cstdlib>
#include <vector>




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
    
    vector<Sublist<LTYPE>> choices;
    
    bool doesExist[TARGET];
    
    for(int i = 0; i < TARGET; i++)
    {
        doesExist[i] = false;
    }
    
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
                               if(c == currSublist.getIndices()[(m)] || i == c )
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
                   cout<< "used this" << endl;
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
    
    
    //max tried so far 40,000
    int dataBase =40000;
    
    srand((unsigned)time(0));
    
    for( int i = 0 ; i < dataBase ; i++)
    {
        
        int random_integer = rand()%100;
        dataSet.push_back(random_integer);
        
    }
    
    

    //max target so far 1,000,000
    int target = 40000;
    
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


/* --- run for integer main
 
 target: 40000
 
 Sublist----------------
 
 sum:40000
 
 [0] = 41, [1] = 19, [2] = 85, [3] = 2, [4] = 6, [5] = 35, [6] = 19, [7] = 14, [8] = 69, [9] = 21, [10] = 83, [11] = 99, [12] = 63, [13] = 63, [14] = 47, [15] = 51, [16] = 60, [17] = 94, [18] = 64, [19] = 79, [20] = 57, [21] = 8, [22] = 26, [23] = 61, [24] = 51, [25] = 33, [26] = 26, [27] = 34, [28] = 2, [29] = 82, [30] = 31, [31] = 85, [32] = 50, [33] = 18, [34] = 16, [35] = 97, [36] = 71, [37] = 98, [38] = 48, [39] = 22, [40] = 14, [41] = 85, [42] = 90, [43] = 83, [44] = 89, [45] = 69, [46] = 84, [47] = 7, [48] = 76, [49] = 27, [50] = 25, [51] = 21, [52] = 12, [53] = 30, [54] = 55, [55] = 72, [56] = 49, [57] = 41, [58] = 57, [59] = 17, [60] = 90, [61] = 44, [62] = 13, [63] = 28, [64] = 5, [65] = 12, [66] = 80, [67] = 7, [68] = 51, [69] = 54, [70] = 34, [71] = 42, [72] = 73, [73] = 14, [74] = 17, [75] = 49, [76] = 32, [77] = 19, [78] = 48, [79] = 19, [80] = 98, [81] = 99, [82] = 62, [83] = 84, [84] = 69, [85] = 73, [86] = 50, [87] = 2, [88] = 57, [89] = 47, [90] = 22, [91] = 20, [92] = 47, [93] = 83, [94] = 41, [95] = 20, [96] = 62, [97] = 2, [98] = 20, [99] = 7, [100] = 96, [101] = 99, [102] = 29, [103] = 64, [104] = 81, [105] = 47, [106] = 14, [107] = 66, [108] = 6, [109] = 96, [110] = 80, [111] = 84, [112] = 68, [113] = 29, [114] = 10, [115] = 96, [116] = 65, [117] = 70, [118] = 62, [119] = 61, [120] = 58, [121] = 47, [122] = 24, [123] = 49, [124] = 45, [125] = 76, [126] = 86, [127] = 70, [128] = 36, [129] = 38, [130] = 9, [131] = 89, [132] = 84, [133] = 37, [134] = 90, [135] = 4, [136] = 57, [137] = 20, [138] = 36, [139] = 19, [140] = 80, [141] = 20, [142] = 71, [143] = 31, [144] = 14, [145] = 60, [146] = 29, [147] = 7, [148] = 3, [149] = 18, [150] = 54, [151] = 83, [152] = 12, [153] = 78, [154] = 9, [155] = 16, [156] = 48, [157] = 4, [158] = 93, [159] = 88, [160] = 73, [161] = 4, [162] = 91, [163] = 73, [164] = 49, [165] = 9, [166] = 96, [167] = 39, [168] = 76, [169] = 92, [170] = 14, [171] = 10, [172] = 25, [173] = 44, [174] = 89, [175] = 1, [176] = 60, [177] = 71, [178] = 80, [179] = 48, [180] = 30, [181] = 41, [182] = 7, [183] = 64, [184] = 61, [185] = 35, [186] = 43, [187] = 26, [188] = 40, [189] = 89, [190] = 10, [191] = 88, [192] = 25, [193] = 48, [194] = 63, [195] = 79, [196] = 52, [197] = 43, [198] = 34, [199] = 98, [200] = 2, [201] = 44, [202] = 42, [203] = 36, [204] = 97, [205] = 20, [206] = 61, [207] = 67, [208] = 55, [209] = 62, [210] = 57, [211] = 30, [212] = 21, [213] = 9, [214] = 94, [215] = 67, [216] = 84, [217] = 5, [218] = 63, [219] = 91, [220] = 67, [221] = 37, [222] = 87, [223] = 63, [224] = 60, [225] = 35, [226] = 90, [227] = 78, [228] = 61, [229] = 88, [230] = 68, [231] = 22, [232] = 29, [233] = 35, [234] = 15, [235] = 61, [236] = 32, [237] = 86, [238] = 15, [239] = 46, [240] = 84, [241] = 31, [242] = 39, [243] = 27, [244] = 60, [245] = 83, [246] = 19, [247] = 39, [248] = 52, [249] = 90, [250] = 2, [251] = 10, [252] = 89, [253] = 84, [254] = 12, [255] = 28, [256] = 14, [257] = 90, [258] = 88, [259] = 47, [260] = 10, [261] = 21, [262] = 16, [263] = 43, [264] = 73, [265] = 97, [266] = 56, [267] = 30, [268] = 70, [269] = 81, [270] = 61, [271] = 52, [272] = 41, [273] = 59, [274] = 78, [275] = 34, [276] = 95, [277] = 80, [278] = 42, [279] = 54, [280] = 20, [281] = 12, [282] = 59, [283] = 75, [284] = 96, [285] = 62, [286] = 85, [287] = 21, [288] = 61, [289] = 33, [290] = 11, [291] = 15, [292] = 29, [293] = 81, [294] = 75, [295] = 36, [296] = 24, [297] = 83, [298] = 40, [299] = 98, [300] = 52, [301] = 80, [302] = 55, [303] = 96, [304] = 56, [305] = 42, [306] = 23, [307] = 11, [308] = 90, [309] = 29, [310] = 51, [311] = 96, [312] = 71, [313] = 3, [314] = 42, [315] = 62, [316] = 51, [317] = 19, [318] = 61, [319] = 9, [320] = 82, [321] = 52, [322] = 38, [323] = 60, [324] = 24, [325] = 63, [326] = 65, [327] = 28, [328] = 49, [329] = 21, [330] = 7, [331] = 84, [332] = 89, [333] = 74, [334] = 43, [335] = 14, [336] = 73, [337] = 63, [338] = 89, [339] = 21, [340] = 15, [341] = 18, [342] = 45, [343] = 4, [344] = 45, [345] = 8, [346] = 49, [347] = 66, [348] = 24, [349] = 97, [350] = 84, [351] = 4, [352] = 53, [353] = 21, [354] = 97, [355] = 45, [356] = 52, [357] = 82, [358] = 91, [359] = 47, [360] = 14, [361] = 17, [362] = 95, [363] = 37, [364] = 30, [365] = 7, [366] = 2, [367] = 80, [368] = 28, [369] = 22, [370] = 32, [371] = 26, [372] = 10, [373] = 63, [374] = 10, [375] = 20, [376] = 24, [377] = 60, [378] = 13, [379] = 66, [380] = 76, [381] = 83, [382] = 14, [383] = 33, [384] = 62, [385] = 80, [386] = 40, [387] = 72, [388] = 81, [389] = 62, [390] = 35, [391] = 5, [392] = 95, [393] = 37, [394] = 16, [395] = 82, [396] = 64, [397] = 12, [398] = 1, [399] = 36, [400] = 66, [401] = 85, [402] = 87, [403] = 60, [404] = 31, [405] = 7, [406] = 1, [407] = 41, [408] = 80, [409] = 74, [410] = 50, [411] = 79, [412] = 93, [413] = 7, [414] = 83, [415] = 17, [416] = 27, [417] = 53, [418] = 40, [419] = 54, [420] = 96, [421] = 87, [422] = 74, [423] = 33, [424] = 9, [425] = 35, [426] = 27, [427] = 65, [428] = 69, [429] = 43, [430] = 33, [431] = 7, [432] = 10, [433] = 57, [434] = 75, [435] = 91, [436] = 55, [437] = 56, [438] = 84, [439] = 69, [440] = 54, [441] = 32, [442] = 17, [443] = 57, [444] = 40, [445] = 99, [446] = 46, [447] = 38, [448] = 21, [449] = 27, [450] = 51, [451] = 57, [452] = 73, [453] = 38, [454] = 82, [455] = 86, [456] = 47, [457] = 10, [458] = 52, [459] = 37, [460] = 10, [461] = 40, [462] = 81, [463] = 5, [464] = 35, [465] = 91, [466] = 8, [467] = 85, [468] = 38, [469] = 76, [470] = 97, [471] = 9, [472] = 27, [473] = 2, [474] = 73, [475] = 6, [476] = 82, [477] = 26, [478] = 44, [479] = 15, [480] = 3, [481] = 21, [482] = 26, [483] = 4, [484] = 93, [485] = 18, [486] = 82, [487] = 32, [488] = 62, [489] = 46, [490] = 58, [491] = 3, [492] = 93, [493] = 31, [494] = 54, [495] = 61, [496] = 76, [497] = 31, [498] = 47, [499] = 53, [500] = 94, [501] = 95, [502] = 43, [503] = 35, [504] = 68, [505] = 68, [506] = 76, [507] = 83, [508] = 80, [509] = 13, [510] = 64, [511] = 56, [512] = 13, [513] = 45, [514] = 36, [515] = 84, [516] = 39, [517] = 99, [518] = 79, [519] = 90, [520] = 43, [521] = 23, [522] = 61, [523] = 61, [524] = 57, [525] = 2, [526] = 49, [527] = 19, [528] = 97, [529] = 11, [530] = 80, [531] = 3, [532] = 45, [533] = 2, [534] = 82, [535] = 34, [536] = 23, [537] = 78, [538] = 79, [539] = 30, [540] = 84, [541] = 57, [542] = 10, [543] = 42, [544] = 61, [545] = 87, [546] = 64, [547] = 47, [548] = 79, [549] = 35, [550] = 32, [551] = 75, [552] = 37, [553] = 74, [554] = 44, [555] = 52, [556] = 36, [557] = 94, [558] = 63, [559] = 44, [560] = 80, [561] = 69, [562] = 51, [563] = 73, [564] = 23, [565] = 35, [566] = 68, [567] = 16, [568] = 64, [569] = 54, [570] = 87, [571] = 21, [572] = 74, [573] = 92, [574] = 22, [575] = 42, [576] = 22, [577] = 97, [578] = 8, [579] = 1, [580] = 30, [581] = 35, [582] = 38, [583] = 20, [584] = 52, [585] = 66, [586] = 42, [587] = 97, [588] = 76, [589] = 41, [590] = 35, [591] = 39, [592] = 73, [593] = 44, [594] = 14, [595] = 78, [596] = 1, [597] = 69, [598] = 73, [599] = 76, [600] = 85, [601] = 17, [602] = 83, [603] = 33, [604] = 40, [605] = 83, [606] = 39, [607] = 72, [608] = 52, [609] = 85, [610] = 54, [611] = 48, [612] = 84, [613] = 33, [614] = 50, [615] = 18, [616] = 91, [617] = 45, [618] = 59, [619] = 22, [620] = 32, [621] = 12, [622] = 13, [623] = 41, [624] = 43, [625] = 98, [626] = 69, [627] = 6, [628] = 39, [629] = 75, [630] = 76, [631] = 70, [632] = 97, [633] = 4, [634] = 12, [635] = 49, [636] = 71, [637] = 61, [638] = 75, [639] = 72, [640] = 50, [641] = 45, [642] = 86, [643] = 86, [644] = 61, [645] = 38, [646] = 72, [647] = 15, [648] = 18, [649] = 49, [650] = 51, [651] = 53, [652] = 78, [653] = 53, [654] = 71, [655] = 83, [656] = 43, [657] = 42, [658] = 56, [659] = 94, [660] = 32, [661] = 87, [662] = 97, [663] = 89, [664] = 43, [665] = 52, [666] = 41, [667] = 42, [668] = 61, [669] = 86, [670] = 38, [671] = 22, [672] = 66, [673] = 83, [674] = 9, [675] = 81, [676] = 36, [677] = 80, [678] = 22, [679] = 57, [680] = 60, [681] = 87, [682] = 9, [683] = 91, [684] = 10, [685] = 19, [686] = 64, [687] = 68, [688] = 91, [689] = 85, [690] = 59, [691] = 50, [692] = 7, [693] = 58, [694] = 50, [695] = 20, [696] = 90, [697] = 63, [698] = 12, [699] = 85, [700] = 42, [701] = 96, [702] = 6, [703] = 85, [704] = 25, [705] = 72, [706] = 11, [707] = 65, [708] = 73, [709] = 75, [710] = 37, [711] = 2, [712] = 69, [713] = 47, [714] = 87, [715] = 12, [716] = 48, [717] = 93, [718] = 33, [719] = 26, [720] = 52, [721] = 19, [722] = 92, [723] = 89, [724] = 58, [725] = 53, [726] = 40, [727] = 15, [728] = 52, [729] = 75, [730] = 81, [731] = 95, [732] = 86, [733] = 30, [734] = 36, [735] = 7, [736] = 69, [737] = 5, [738] = 46, [739] = 93, [740] = 96, [741] = 69, [742] = 96, [743] = 10, [744] = 20, [745] = 79, [746] = 70, [747] = 61, [748] = 70, [749] = 54, [750] = 7, [751] = 33, [752] = 67, [753] = 14, [754] = 37, [755] = 27, [756] = 70, [757] = 33, [758] = 68, [759] = 7, [760] = 68, [761] = 40, [762] = 12, [763] = 33, [764] = 47, [765] = 29, [766] = 58, [767] = 18, [768] = 24, [769] = 12, [770] = 49, [771] = 69, [772] = 15, [773] = 46, [774] = 62, [775] = 40, [776] = 31, [777] = 82, [778] = 57, [779] = 53, [780] = 84, [781] = 33, [782] = 75, [783] = 21, [784] = 69, [785] = 97, [786] = 62, [787] = 67, [788] = 62, [789] = 25, [790] = 79, [791] = 63, [792] = 46, [793] = 95, [794] = 77, [795] = 45, [796] = 9, [797] = 52, [798] = 13
 
 
 
 Algorithm Elapsed Time: 0.542785 seconds.
 
 Program ended with exit code: 0
 */

/*
int main()

{
    //22109 would be very slow
    const int TARGET = 350;
    
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
  


    
    




