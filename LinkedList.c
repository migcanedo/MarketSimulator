#include <stdio.h>
#include <stdlib.h>
#include "mercado.h"


/*
Funcion que se encarga de agregar un Producto 'p' a la Lista Enlazada 'l'.
*/
void agregarElem (LinkedList *l, Producto *p){
	Nodo *n = (Nodo*) malloc(sizeof(Nodo));
	n->prod = p;

	// printf("%s\n", p->nombre);

	if (!(l->head) || l->head->prod->peso > p->peso){	
		n->next = l->head;
		l->head = n;

	}else{
		
		Nodo *ite = l->head;
		
		while (ite->next && ite->next->prod->peso < p->peso)
				ite = ite->next;		
		
		n->next = ite->next;
		ite->next = n;
	}
	l->cant += 1;
}

/*
Funcion que se encarga de eliminar el primer Producto 'p' de la Lista Enlazada 'l', quien
seria la cabeza de la lista, y lo retorna. En caso de que la lista este vacia, retornara NULL.
*/
Producto *eliminarElem(LinkedList *l){
	Nodo *aux = l->head;
	Producto *prodAct;
	prodAct = aux->prod;
	if(aux)
		l->head = l->head->next;
	//printf("'%s' ha sido sacado de la la lista\n", aux->prod->nombre);
	free(aux);
	l->cant = l->cant -1;
	return prodAct;
}

/*
Funcion que se encarga de crear el espacio en memoria para una Lista Enlazada y retornar 
un apuntador a ese espacio.
*/
LinkedList * crearLista(){
	LinkedList *nueva = (LinkedList*) malloc(sizeof(LinkedList));
	nueva->head = NULL;
	nueva->cant = 0; 

	return nueva;
}

/*
Funcion que se encarga de imprimir los nombres de los Productos que se estan almacenando
en la Lista Enlazada 'l'.
*/
void imprimirLista(LinkedList *l){
	Nodo *p = l->head;
	while(p){
		printf("\t%s\n", p->prod->nombre);
		p = p->next;
	}
}

/*
Funcion que se encarga de imprimir los nombres de los Productos que se estan almacenando
en la Lista Enlazada 'l'.
*/
void eliminarLista(LinkedList *l){
	Nodo *p = l->head;
	Nodo *aux;
	while(p){
		aux = p->next;
		free(p);
		p = aux;
	}
}