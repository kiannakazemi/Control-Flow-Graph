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

/*delets all the list elements*/
void clear(List&); 

/*modifies the element in pos position*/   
void set(int, Elem, List&); 

/*inserts the element in pos position, shifting the other elements to the right*/
void add(int, Elem, List&); 

/*inserts the element at the end of the list*/
void addBack(Elem, List&);  

/*inserts the element at the beginning of the list*/
void addFront(Elem, List&); 

/*deletes the element in pos position*/
void removePos(int, List&); 

/*returns the element in pos position*/
Elem get(int, const List&);	

/*creates and returns an empty list*/
List createEmpty();        

/*returns true if the list is empty*/
bool isEmpty(const List&);

/*returns the size of the list*/
int size(const List&);
}

void printList(const list::List&);

#endif
