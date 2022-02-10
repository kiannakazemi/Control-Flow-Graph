#ifndef GRAPH_H
#define GRAPH_H

#include <cstddef>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

#include "list.h"

using namespace std;

namespace graph {

typedef string Label;
typedef int Weight;

struct vertexNode; 

typedef vertexNode* Graph; //a graph is identified by the pointer to the first vertex inserted


const Graph emptyGraph = NULL;

/*returns an empty graph*/
Graph createEmptyGraph();

/*adds a new labeled vertex; fails if it is already present*/
bool addVertex(Label, Graph&);

/*adds a new weighted edge between the two labeled nodes*/
bool addEdge(Label, Label, Weight, Graph&);

/*returns true if the graph is empty*/
bool isEmpty(const Graph&);

/*returns the number of the graph vertices*/
int numVertices(const Graph&);

/*returns the number of the graph edges*/
int numEdges(const Graph&);

/*returns the degree of the node.*/
bool nodeDegree(Label, int&, const Graph&);

/*checks if two vertices are adjacent*/
bool areAdjacent(Label, Label, const Graph&);

/*returns the adjacency list of a vertex*/
list::List adjacentList(Label, const Graph&);

}

void printGraph(const graph::Graph&);



/***************************************Functions required for the CFG***************************************/

/*constructs the CFG graph corresponding to the data in the fileName*/
graph::Graph buildGraphFromFile(string fileName);

/*checks if all the edges have been visited*/
bool allEdgesVisited(const graph::Graph&);

/*returns a list of labels corresponding to the visited nodes during the random walk*/
list::List randomWalk(graph::Graph&);

/*returns the last label (the one containing the maximum number)*/
graph::Label lastNode(graph::Graph&);

/*returns the first node (the one containing the minimum number)*/
graph::Graph firstNode(graph::Graph&);

/*returns the number of visted edges*/
int visitedEdges(graph::Graph& g);


#endif
