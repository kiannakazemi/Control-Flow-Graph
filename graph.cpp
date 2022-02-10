#include <stdlib.h>
#include "graph.h"

using namespace graph;

struct halfEdgeVertex{
	vertexNode* vertPtr;  //label of the destination vertex
	Weight weight;        //edge label
	bool visited;
	halfEdgeVertex* next; //pointer to the next half edge
};

typedef halfEdgeVertex * Edge;
const Edge emptyAdjList = NULL;

struct graph::vertexNode{
	Label label;
	Edge adjList;
	vertexNode * next;
	bool visited;
};

Graph graph::createEmptyGraph(){
	return emptyGraph;
}

bool graph::addVertex(Label l, Graph& g){
	Graph aux = g;
	while(!isEmpty(aux)){
		if(aux->label == l)
			return false; 
		aux = aux->next;
	}
	aux = new vertexNode;
	aux->label = l;
	aux->next = g;
	aux->adjList = emptyAdjList;
	g = aux;
	return true;
}

bool graph::addEdge(Label from, Label to, Weight w, Graph& g){
	Graph dest = g;
	while(!isEmpty(dest)){
		if(dest->label == to)
			break;
		dest = dest->next;
	}
	if(isEmpty(dest))
		return false;
	Graph source = g;
	while(!isEmpty(source)){
		if(source->label == from)
			break;
		source = source->next;
	}
	if(isEmpty(source))
		return false;
	Edge sourceAdj = source->adjList;
	Edge destAdj = dest->adjList;
	while((sourceAdj != emptyAdjList) && (destAdj != emptyAdjList)){
		if(destAdj->vertPtr == source)
			return false;
		destAdj = destAdj->next;
		sourceAdj = sourceAdj->next;
	}
	destAdj = new halfEdgeVertex;
	destAdj->weight = w;
	destAdj->visited = false;
	destAdj->vertPtr = dest;
	destAdj->next = source->adjList;
	source->adjList = destAdj;
	return true;
}

bool graph::isEmpty(const Graph& g){ 
	return (g == emptyGraph);
}

int graph::numVertices(const Graph& g){
	int cont = 0;
	Graph aux = g;
	while(!isEmpty(aux)){ 
		++cont;
		aux = aux->next;
	}
	return cont;
}

int graph::numEdges(const Graph& g){
	int cont = 0;
	Graph vert = g; 
	Edge edge = nullptr; 
	while(!isEmpty(vert)){ 
		edge = vert->adjList; 
		while(edge != emptyAdjList){ 
			edge = edge->next;
			++cont;
		}
		vert = vert->next;
	}
	return cont;
}

bool graph::nodeDegree(Label l, int& degree, const Graph& g){
	Graph aux = g;
	while(!isEmpty(aux)){
		if(aux->label == l){ 
			Edge auxAdj = aux->adjList;
			degree = 0;
			while(auxAdj != emptyAdjList){ 
				++degree;
				auxAdj = auxAdj->next;
			}
			return true;
		}
		aux = aux->next;
	}
	return false;
}

bool graph::areAdjacent(Label v1, Label v2, const Graph& g){
	Graph aux1 = g;
	while(!isEmpty(aux1)){ 
		if(aux1->label == v1){ 
			Edge aux2 = aux1->adjList;
			while(aux2 != emptyAdjList){
				if(aux2->vertPtr->label == v2)
					return true;
				aux2 = aux2->next;
			}
		}
		if(aux1->label == v2){ 
			Edge aux2 = aux1->adjList;
			while(aux2 != emptyAdjList){
				if(aux2->vertPtr->label == v1)
					return true;
				aux2 = aux2->next;
			}
			return false;
		}
		aux1 = aux1->next;
	}
	return false;
}

list::List graph::adjacentList(Label v1, const Graph& g){
	Graph aux = g;
	list::List lst = list::createEmpty();
	while(!isEmpty(aux)){
		if(aux->label == v1){ 
			Edge aux2 = aux->adjList;
			while(aux2 != emptyAdjList){
				list::addBack(aux2->vertPtr->label, lst);
				aux2 = aux2->next;
			}
		}
		aux = aux->next;
	}
	return lst;
}

void printGraphAux(const graph::Graph& g){
	g->visited = true;
	cout << g->label << " ";
	Edge aux = g->adjList;
	while(aux != emptyAdjList){
		if(aux->vertPtr->visited == false) 
			printGraphAux(aux->vertPtr);
		aux = aux->next;
	}
}

void printGraph(const graph::Graph& g) {
	Graph reset = g;
	while(!isEmpty(reset)){
		reset->visited = false;
		reset = reset->next;
	}
	printGraphAux(g);
}

graph::Graph buildGraphFromFile(string fileName){
	Graph G = createEmptyGraph();
	string line;
	ifstream infile(fileName);
	while (getline(infile, line)){
	    stringstream ss(line);
		string token;
		getline(ss, token, ' ');
		string nodo = token;
		addVertex(nodo, G);
	    while(getline(ss, token, ' ')) {
			addVertex(token, G); 
			addEdge(nodo, token, 0, G); 
		}
	}
	return G;
}

bool allEdgesVisited(const graph::Graph& g){
	for(vertexNode* nodo = g; !isEmpty(nodo); nodo = nodo->next){ 
		for(halfEdgeVertex* arco = nodo->adjList; arco != emptyAdjList; arco = arco->next){ 
			if(!arco->visited)
				return false; 
		}
	}
	return true;
}

graph::Label lastNode(graph::Graph& g){
	vertexNode* tmp = g;
	string max = tmp->label;
	while(!isEmpty(tmp)){
		if(stoi(tmp->label) > stoi(max)) 
			max = tmp->label;
		tmp = tmp->next;
	}
	return max;
}

graph::Graph firstNode(graph::Graph& g){
	vertexNode* tmp = g;
	Graph min = tmp; 
	while(!isEmpty(tmp)){
		if(stoi(tmp->label) < stoi(min->label)) 
			min = tmp;
		tmp = tmp->next;
	}
	return min;
}

/*********************************Useful functions for randomWalk*****************************************/

//Given an edge (the first), it returns true if the given edge and its following edges in the adjacency list are already visited
bool allNextEdgesVisited(halfEdgeVertex * arco); 

//Given an edge (the first), it returns true if the given edge and its following edges in the adjacency list aren't already visited
bool allNextEdgesUnvisited(halfEdgeVertex * arco);

//Given an edge (the first),it returns a random edge
halfEdgeVertex * chooseRandomEdge(halfEdgeVertex * arco);

//Given an edge (the first), it returns an unvisited edge
halfEdgeVertex * chooseUnvisitedEdge(halfEdgeVertex * arco); 




/*********************************Implementation of useful functions for randomWalk*****************************************/

bool allNextEdgesVisited(halfEdgeVertex * arco){
	while(arco != emptyAdjList){
		if(!arco->visited)
			return false;
		arco = arco->next;
	}
	return true;
}

bool allNextEdgesUnvisited(halfEdgeVertex * arco){
	while(arco != emptyAdjList){
		if(arco->visited)
			return false;
		arco = arco->next;
	}
	return true;
}

halfEdgeVertex * chooseRandomEdge(halfEdgeVertex * primoArco){
	int count = 0;
	halfEdgeVertex * tmp = primoArco;
	while(tmp != emptyAdjList){
		++count;
		tmp = tmp->next;
	}
	// choose a random number between 0 and the lengths of the edhe list
	int pos = rand() % count;
	tmp = primoArco;
	while(pos > 0){ //reach the arch at the randomly chosen position
		tmp = tmp->next;
		--pos;
	}
	return tmp;
}

halfEdgeVertex * chooseUnvisitedEdge(halfEdgeVertex * primoArco){
	halfEdgeVertex * tmp = primoArco;
	while(tmp != emptyAdjList){ //Scrolling through the adjacency list
		if(!tmp->visited) //If I find one that is not visited, then return it
			return tmp;
		tmp = tmp->next;
	}
	return emptyAdjList;
}

int visitedEdges(graph::Graph& g){
	int count = 0;
	for(vertexNode * tmp = g; tmp != emptyGraph; tmp = tmp->next){ 
		for(halfEdgeVertex * tmpEdge = tmp->adjList; tmpEdge != emptyAdjList; tmpEdge = tmpEdge->next){ 
			if(tmpEdge->visited)
				++count;
		}
	}
	return count;
}

//returns the list of node labels resulting from the random path on the graph
list::List randomWalk(graph::Graph& g){
	//start from the minimum labeled node
	Graph nodoVisitato = firstNode(g);
	list::List walk = list::createEmpty();
	// Insert the first node in the list
	addBack(nodoVisitato->label, walk);
	while(nodoVisitato->label != lastNode(g)){ //continue until I get to the node with the highest label
		halfEdgeVertex * arcoProssimo = emptyAdjList;
		if(allNextEdgesVisited(nodoVisitato->adjList) || allNextEdgesUnvisited(nodoVisitato->adjList))
			arcoProssimo = chooseRandomEdge(nodoVisitato->adjList); 
		else
			arcoProssimo = chooseUnvisitedEdge(nodoVisitato->adjList)
		//mark it as visited
		arcoProssimo->visited = true;
		// add the next node to the list
		list::addBack(arcoProssimo->vertPtr->label, walk);
		nodoVisitato = arcoProssimo->vertPtr;
	}
	return walk;
}
