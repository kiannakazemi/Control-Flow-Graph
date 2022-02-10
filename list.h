#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <string> 
#include <iostream>
#include <stdexcept>

using namespace std; 
 
namespace list{

typedef string Elem;  

const Elem emptyElem = "$#$#$";

struct list;

typedef list* List;

/* Cleans the list*/
void clear(List&); 

/* Modifies the element in position pos*/   
void set(int, Elem, List&); 

/* inserts the element in pos position, shifting the other elements to the right*/
void add(int, Elem, List&); 

/* Inserts the element at the end of the list*/
void addBack(Elem, List&);  

/* Inserts the element at the beginning of the list*/
void addFront(Elem, List&); 

/* Deletes the element in pos position*/
void removePos(int, List&); 

/* Returns the element in pos position*/
Elem get(int, const List&);	

/* Creates and returns an empty list*/
List createEmpty();        

/*Returns true if the list is empty*/
bool isEmpty(const List&);

/*Returns the size of the list*/
int size(const List&);
}

void printList(const list::List&);

#endif
