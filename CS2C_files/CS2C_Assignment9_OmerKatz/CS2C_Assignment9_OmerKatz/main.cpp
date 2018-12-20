//
//  main.cpp
//  CS2C_Assignment9_OmerKatz
//
//  Created by Omer Katz on 12/6/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//
/*
 1. Do you recognize this data structure from earlier in this course? What kind of data structure is being used to represent the graph?
 
 Answer: This is a sparce matrices.
 
 
 2. Draw a picture of the pre-made graph from the provided sample main/output.
 
 Answer: see attached file.
 
 
 3.What kind of algorithm is Prim’s algorithm?
 
 Answer: Prim’s algorithm is a greedy algorithm
 */

#include <iostream>

#include "FHlist.h"
#include "FHvector.h"
#include "FHlistSorted.h"
#include "Graph.h"
#include "GraphWPrim.h"

using namespace std;
int main()

{
    
    //change this to GraphWPrim later
    GraphWPrim<char> graph('A');

    graph.addVertex('B', 'A', 2);
    
    graph.addVertex('C', 'A', 3);
    
    graph.addEdge('C', 'B', 4);
    
    graph.addVertex('D', 'A', 3);
    
    graph.addEdge('C', 'D', 5);
    
    graph.addVertex('E', 'B', 3);
    
    graph.addEdge('C', 'E', 1);
    
    graph.addVertex('F', 'C', 6);
    
    graph.addEdge('D', 'F', 7);
    
    graph.addEdge('F', 'E', 8);
    
    graph.addVertex('G', 'F', 9);
    
    graph.print();
    
    
    
    graph.prim();
    
    
    
    graph.print();
    
    
    
    
}

/*
 
 
 A  ->  B.2  ->  C.3  ->  D.3
 B  ->  A.2  ->  E.3  ->  C.4
 C  ->  E.1  ->  A.3  ->  B.4  ->  D.5  ->  F.6
 D  ->  A.3  ->  C.5  ->  F.7
 E  ->  C.1  ->  B.3  ->  F.8
 F  ->  C.6  ->  D.7  ->  E.8  ->  G.9
 G  ->  F.9
 Total Edge Weight: 51
 
 
 A  ->  B.2  ->  C.3  ->  D.3
 B  ->  A.2
 C  ->  E.1  ->  A.3  ->  F.6
 E  ->  C.1
 D  ->  A.3
 F  ->  C.6  ->  G.9
 G  ->  F.9
 Total Edge Weight: 24
 */
