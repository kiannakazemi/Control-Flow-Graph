
#include "list.h"

using namespace list;

struct list::list {  
	Elem info;
	list* prev;
	list* next;
};

void list::clear(List& l){
	for(int i=size(l); i>0; --i)
		removePos(i,l);
}

void list::set(int pos, Elem e, List& l){
	if(pos<=0 || pos>size(l))
		return; //error
	list* temp=l->next;
	int cont=1;
	while(cont!=pos){
		++cont;
		temp=temp->next;
	}
	temp->info=e;
}

void list::add(int pos, Elem e, List& l){
	if(pos<=0 || pos>size(l)+1)
		return; //error
	list* temp=l->next;
	int cont=1;
	while(cont!=pos){
		++cont;
		temp=temp->next;
	}
	list* aux= new list;
	aux->info=e;
	aux->next=temp;
	aux->prev=temp->prev;
	temp->prev->next=aux;
	temp->prev=aux;
}

void list::addBack(Elem e, List& l){
	list* aux=new list;
	aux->info=e;
	aux->prev=l->prev;
	aux->next=l;
	l->prev->next=aux;
	l->prev=aux;
}

void list::addFront(Elem e, List& l){
	list* aux= new list;
	 aux->info=e;
	 aux->next=l->next;
	 l->next=aux;
	 aux->next->prev=aux;
	 aux->prev=l;
}

void list::removePos(int pos, List& l){
	if(pos<=0 || pos>size(l))
		return; //error
	list* aux=l->next;
	int cont=1;
	while(cont != pos){
		++cont;
		aux=aux->next;
	}
	aux->prev->next=aux->next;
	aux->next->prev=aux->prev;
	delete aux;
}

List list::createEmpty(){
	list* aux= new list;
	aux->next=aux;
	aux->prev=aux;
	aux->info=emptyElem;
	return aux;
}

Elem list::get(int pos, const List& l)
{
	if(pos<=0 || pos>size(l))
		return emptyElem; //error
	list* temp=l->next;
	int cont=1;
	while(cont != pos){
		++cont;
		temp=temp->next;
	}
	return(temp->info); 
}

bool list::isEmpty(const List& l){
	return (l->next == l);
}

int list::size(const List& l){
	if(isEmpty(l))
		return 0;
	list* aux=l->next;
	int cont=0;
	while(aux != l){
		++cont;
		aux=aux->next;
	}
	return cont;
}

void printList(const List& l)
{
   List q = l->next;  //skip the sentry node
   while (q != l){
      cout << q->info << "; ";
      q = q->next; 
    }
}
