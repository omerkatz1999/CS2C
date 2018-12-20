//
//  Gene.h
//  Assignment06_genes
//
//  Created by Joanna Lankester on 11/7/18.
//  Copyright © 2018 Joanna Lankester. All rights reserved.
//

#ifndef Gene_h
#define Gene_h

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Gene {
private:
    string name;
    int startingBasePair;

public:
    Gene(string name="", int bp=0);
    string toString() const;
    bool operator==(const Gene &other) const;
    bool operator!=(const Gene &other) const;
    string getName() const {return name;}
    int getStartingBasePair() const {return startingBasePair; }
    
    friend class GeneDataReader;
};

class GeneDataReader {
private:
    vector<Gene> genes;
    int numGenes;
    bool fileOpenError;
    string geneFile;
    Gene readOneLine(string line);
public:
    GeneDataReader(string fileName);
    Gene & operator[](int k);
    string getFileName() { return geneFile; }
    bool readError() { return fileOpenError; }
    int getNumGenes() { return numGenes; }
    class GeneIndexNotFoundException{};
};

Gene::Gene(string name, int bp) {
    this->name = name;
    this->startingBasePair = bp; 
}

string Gene::toString() const {
    return name + " starting at base pair " + to_string(startingBasePair);
}

bool Gene::operator==(const Gene &other) const {
    return (name == other.name) && (startingBasePair == other.startingBasePair);
}

bool Gene::operator!=(const Gene &other) const {
    return (name != other.name) || (startingBasePair != other.startingBasePair);
}

GeneDataReader::GeneDataReader(string fileName) {
    string name;
    string line, entryString;
    Gene gene("",0);
    
    numGenes = 0;
    fileOpenError = false;
    
    if (fileName.length() == 0)
    {
        fileOpenError = true;
        return;
    }
    geneFile = fileName;
    // open file for reading
    ifstream infile(fileName.c_str());
    if (!infile)
    {
        fileOpenError = true;
        return;
    }

    // read each line and add the Gene to a vector
    while ( !infile.eof() )
    {
        getline (infile, line);
        if (line == "") // end of file
            break;
        gene = readOneLine(line);
        genes.push_back(gene);
        numGenes++;
    }
    infile.close();
}


Gene & GeneDataReader::operator[](int k) {
    if (k < 0 || k >= numGenes)
        throw GeneIndexNotFoundException();
    return genes[k];
}

Gene GeneDataReader::readOneLine(string line) {
    string geneName;
    string geneIdAsString;
    int geneId;
    
    // split on delimiter
    char delim = '\t';
    stringstream ss(line);
    getline(ss,geneIdAsString,delim);
    getline(ss,geneName,delim);
    
    // convert Gene ID to integer
    geneId = stoi(geneIdAsString);
    
    // create and return a Gene
    Gene thisGene(geneName,geneId);
    return thisGene;
}

#endif /* Gene_h */
