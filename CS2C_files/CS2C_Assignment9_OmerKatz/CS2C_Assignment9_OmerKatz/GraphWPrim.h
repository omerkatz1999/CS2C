//  Omer Katz
//  GraphWPrim.h
//  CS2C_Assignment9_OmerKatz
//
//  Created by Omer Katz on 12/6/18.
//  Copyright © 2018 Omer Katz. All rights reserved.
//

#ifndef GraphWPrim_h
#define GraphWPrim_h

#include "Graph.h"

#include <limits.h>


template <class T>

class GraphWPrim : public Graph<T>

{
    
public:
    
    GraphWPrim(T name) : Graph<T>::Graph(name) { }
    
    int indexOfVertex( FHvector<T> vector, T name);
    
    GraphWPrim<T>& prim();
    
};


template <class T>
GraphWPrim<T>& GraphWPrim<T>:: prim(){
    
    if(this->vertices.size() <= 1)
    {
        return *this;
    }
    
    FHvector<int> visited;
    
    // 1. pick a starting vertex
    int x = 0;
  //  cout << "starting vertex:" << this->vertices[x] << endl;
    
    
    GraphWPrim mst(this->vertices[x]);
    
    
    //2. add to visited
    visited.push_back(x);
    
    T minEdgeName;
    T from ;
    int minDist;
    int round = 0;
    
    //3 compare size of visited and vertices
    while(visited.size() < this->vertices.size())
    {
        round++;
        minDist = INT_MAX;
        int curIndex;
        int removeFirstEdge;
        int addedVertex;
        //3.i. iterate through visited nodes
        for (int i = 0; i < visited.size(); i++)
        {

            curIndex = visited[i];
          
            while(indexOfVertex(mst.vertices, this->graphMat[curIndex].front().name) != -1)
            {
                if(this->graphMat[curIndex].size() > 0)
                {
                    this->graphMat[curIndex].pop_front();
                }
                else{
                    break;
                }
                
            }
            if(this->graphMat[curIndex].size() > 0)
            {
                if(minDist > this->graphMat[curIndex].front().dist)
                {
                    minEdgeName = this->graphMat[curIndex].front().name;
                    from = this->vertices[curIndex];
                    minDist = this->graphMat[curIndex].front().dist;
                    addedVertex = indexOfVertex(this->vertices, this-> graphMat[curIndex].front().name);
                    removeFirstEdge = curIndex;
                        
               
                }
            }
        }
        
        mst.addVertex(minEdgeName, from, minDist);
        
        // remove from original graph
        this->graphMat[removeFirstEdge].pop_front();
        
        visited.push_back(addedVertex);
    }
    
    *this = mst;
    
    return *this;
    
}



template <class T>
int GraphWPrim<T>:: indexOfVertex( FHvector<T> vector, T name)
{
    for(int i = 0; i < vector.size(); i++)
    {
        if(name == vector[i])
        {
            return i;
        }
    }
    
    return -1;
}



#endif /* GraphWPrim_hpp */







