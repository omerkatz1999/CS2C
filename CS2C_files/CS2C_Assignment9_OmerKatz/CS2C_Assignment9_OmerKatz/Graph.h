// Graph
// A sparse matrix implementation of a graph structure for CS 2C Source Files/Code
// Joanna Lankester and Ian Cramer
// 11/7/18
//



// ---------- Header Section ----------
#ifndef GRAPH_H
#define GRAPH_H
#pragma once

#include <iostream>

#include "FHvector.h"
#include "FHlistSorted.h"

using namespace std;
// ---------- End Header Section ----------



// Graph Node Class
// Edges will be nodes (Vertices are simply represented by a char)
template <class T>
class GraphNode  // prototype --------------------------------------------------
{
public:
   T name;
   int dist;
   
   GraphNode(int distance = 0, T nm = T()) : dist(distance), name(nm) {}
   
   bool operator < (const GraphNode& rightSide) const { return dist < rightSide.dist; }
   bool operator > (const GraphNode& rightSide) const { return dist > rightSide.dist; }
   GraphNode& operator = (const GraphNode& rightSide) { this->dist = rightSide.dist; this->name = rightSide.name; return *this; }
};
// End Graph Node Class



// Graph Class
// Implements a graph through a sparse matrix
template <class T>
class Graph
{
public:
   Graph(T originalVertex);
   Graph(const Graph& rhs) { *this = rhs; }
   Graph& operator = (const Graph &rightSide);
   
   bool addVertex(T name, T anchor, int distance);
   bool addEdge(T name, T anchor, int distance);
   
   bool removeVertex(T name);
   bool removeEdge(T name, T anchor);
   
   int getNumVertices() const { return vertices.size(); }
   int getNumEdges() const;
   
   bool validVertex(T vName) const;
   bool validEdge(T name, T anchor) const;
   
   int weight() const;
   
   void print();
   
protected:
   // A vector that holds the names of each vertex.
   // Doubles as a representation for the spine of the sparse matrix
   FHvector<T> vertices;
   
   // The sparse matrix holds all the edge information between all vertices
   FHvector< FHlistSorted< GraphNode<T> > > graphMat;
};
// End Graph Class



// Graph Constructor
template <class T>
Graph<T>::Graph(T originalVertex)
{
   vertices.push_back(originalVertex);
   graphMat.push_back( FHlistSorted< GraphNode<T> >() );
} // End Constructor

// Assignment Operator Overload (Simply uses previously established assignment operator overloads)
template <class T>
Graph<T>& Graph<T>::operator = (const Graph &rightSide)
{
   this->vertices = rightSide.vertices;
   this->graphMat = rightSide.graphMat;
   return *this;
} // End Assignment Operator Overload



// Add Vertex
template <class T>
bool Graph<T>::addVertex(T name, T anchor, int distance)
{
   // Can't connect a vertex to itself
   if (name == anchor)
      return false;
   // Check valid vertex
   if (!validVertex(anchor))
      return false;
   // Check valid distance
   if (distance <= 0)
      return false;
   
   // The vertex already exists, meant to add an edge
   if (validVertex(name))
      return addEdge(name, anchor, distance);
   
   // Add the new vertex to the set of vertices
   vertices.push_back(name);
   // Add a row in the matrix to hold its edge data
   graphMat.push_back( FHlistSorted< GraphNode<T> >() );
   
   // Add the edge
   return addEdge(name, anchor, distance); 
} // End Add Vertex

// Add Edge
template <class T>
bool Graph<T>::addEdge(T name, T anchor, int distance)
{
   // Can't connect a vertex to itself
   if (name == anchor)
      return false;
   // Check Valid Distance
   if (distance <= 0)
      return false;
   // Check Valid Vertices (with which to draw an edge)
   if (!validVertex(name))
      return false;
   if (!validVertex(anchor))
      return false;
   // Check Valid Edge (Don't redraw edges)
   if (validEdge(name, anchor))
      return false;
   
   
   bool b1 = false, b2 = false;
   // Create the desired edge between the vertex and its anchor
   for (int i = 0; i < vertices.size(); i++)
   {
      // Connect the vertex to the anchor
      if (vertices[i] == name)
      {
         GraphNode<T> newEdge(distance,anchor);
         graphMat[i].insert(newEdge);
         b1 = true;
      }
      // Connect the anchor back to the edge
      if (vertices[i] == anchor)
      {
         GraphNode<T> newEdge(distance,name);
         graphMat[i].insert(newEdge);
         b2 = true;
      }
      // All Done
      if (b1 && b2)
         return true;
   }
   
   cout << "Add Edge Failure" << endl;
   return validEdge(name, anchor);
} // End Add Edge



// Remove Vertex
template <class T>
bool Graph<T>::removeVertex(T name)
{
   if ( !validVertex(name) )
      return false;
   
   for (int i = 0; i < vertices.size(); i++)
      removeEdge(vertices[i], name);
   
   return true;
} // End Remove Vertex

// Remove Edge
template <class T>
bool Graph<T>::removeEdge(T name, T anchor)
{
   if ( !validEdge(name, anchor) )
      return false;
   
   typename FHvector<T>::iterator vIter = NULL, j = vertices.begin();
   typename FHvector< FHlistSorted< GraphNode<T> > >::iterator matIter = NULL, k = graphMat.begin();
   bool b1 = false, b2 = false, rmV = false;
   for (int i = 0; i < vertices.size(); i++, j++, k++)
   {
      // All Vertices must be connected to be part of the graph. If removing a vertex's last edge, remove the vertex from the graph entirely
      if (vertices[i] == name || vertices[i] == anchor)
         if (graphMat[i].size() <= 1)
         {
            vIter = j;
            matIter = k;
            rmV = true;
         }
      
      if (vertices[i] == name)
      {
         typename FHlistSorted< GraphNode<T> >::iterator iter = graphMat[i].begin();
         for (iter; iter != graphMat[i].end(); iter++)
            if ( (*iter).name == anchor)
            {
               graphMat[i].erase(iter);
               b1 = true;
               break;
            }
      }
      if (vertices[i] == anchor)
      {
         typename FHlistSorted< GraphNode<T> >::iterator iter = graphMat[i].begin();
         for (iter; iter != graphMat[i].end(); iter++)
            if ( (*iter).name == name)
             {
               graphMat[i].erase(iter);
               b2 = true;
               break;
            }
      }
      if (b1 && b2)
         break;
   }
   if (rmV)
   {
      vertices.erase(vIter);
      graphMat.erase(matIter);
   }
   
   return b1 && b2;
   
} // End Remove Edge



// Check Valid Vertex (Semi Helper Method, also public in case client wants to check)
template <class T>
bool Graph<T>::validVertex(T vName) const
{
   for (int i = 0; i < vertices.size(); i++)
      if (vertices[i] == vName)
         return true;
   return false;
} // End Valid Vertex

// Check Valid Edge Helper Method
template <class T>
bool Graph<T>::validEdge(T name, T anchor) const
{
   // No edges to itself
   if (name == anchor)
      return false;
   
   bool b1 = false, b2 = false;
   for (int i = 0; i < vertices.size(); i++)
   {
      if (vertices[i] == name)
      {
         typename FHlistSorted< GraphNode<T> >::const_iterator iter = graphMat[i].begin();
         for (iter; iter != graphMat[i].end(); iter++)
            if ( (*iter).name == anchor )
               b1 = true;
      }
      if (vertices[i] == anchor)
      {
         typename FHlistSorted< GraphNode<T> >::const_iterator iter = graphMat[i].begin();
         for (iter; iter != graphMat[i].end(); iter++)
            if ( (*iter).name == name )
               b2 = true;
      }
      if (b1 && b2)
         return true;
   }
   
   if (b1 && !b2)
      cout << "Valid Edge Error Mismatch: " << anchor << " -/-> " << name;
   if (!b1 && b2)
      cout << "Valid Edge Error Mismatch: " << name << " -/-> " << anchor;
   return false;
}



template <class T>
int Graph<T>::getNumEdges() const
{
   int x = 0;
   for (int i = 0; i < graphMat.size(); i++)
      x += graphMat[i].size();
   return x;
}



template <class T>
int Graph<T>::weight() const
{
   int w = 0;
   for (int i = 0; i < this->graphMat.size(); i++)
   {
      typename FHlistSorted< GraphNode<T> >::const_iterator iter = this->graphMat[i].begin();
      for (iter; iter != this->graphMat[i].end(); iter++)
         w += (*iter).dist;
   }
   return w/2;
}



// Print Function
template <class T>
void Graph<T>::print()
{
   cout << endl;
   for (int i = 0; i < vertices.size(); i++)
   {
      cout << vertices[i];
      typename FHlistSorted< GraphNode<T> >::const_iterator iter = graphMat[i].begin();
      for (iter; iter != graphMat[i].end(); iter++)
         cout << "  ->  " << (*iter).name << "." << (*iter).dist << "";
      cout << endl;
   }
   cout << "Total Edge Weight: " << weight() << endl;
   cout << endl;
}



#endif
// End of Program


