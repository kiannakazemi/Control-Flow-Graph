#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "graph.h"

using namespace std;
using namespace graph;
using namespace list;

const bool askForInput = true;

int main(){
	srand(time(NULL));
	string fileName;
	int budget;
	if(askForInput){
		cout << "Please enter the file name:" << endl;
		cin >> fileName;
		cout << "Please insert the budget:" << endl;
		cin >> budget;
	}
	else {
		fileName = "input.txt";
		budget = 1;
	}
	
	Graph CFG = buildGraphFromFile(fileName); 
	while(!allEdgesVisited(CFG) && budget > 0){ 
		List rWalk = randomWalk(CFG); 
		printList(rWalk);
		cout << endl;
		--budget; 
	}

	int visitedEdges = visitedEdges(CFG);
	int totalArchs = numEdges(CFG);
	cout << "Coverage: " << ((float) visitedEdges / (float) totalArchs) * 100 << '%' << endl;
}
