#include <stdio.h>
#include <stdlib.h>
#include "mercado.h"


/*
Funcion que se encarga de agregar un Producto 'p' a la Lista Enlazada 'l'.
*/
void agregarElem (LinkedList *l, Producto *p){
	if (!(l->head) || l->head->peso > p->peso){
		
		p->next = l->head;
		l->head = p;

	}else{
		
		Producto *ite = l->head;
		
		while (ite->next && ite->next->peso < p->peso)
				ite = ite->next;		
		
		p->next = ite->next;
		ite->next = p;
	}
	l->cant += 1;
}

/*
Funcion que se encarga de eliminar el primer Producto 'p' de la Lista Enlazada 'l', quien
seria la cabeza de la lista, y lo retorna. En caso de que la lista este vacia, retornara NULL.
*/
Producto *eliminarElem(LinkedList *l){
	Producto *aux = l->head;
	if(aux)
		l->head = l->head->next;

	return aux;
}

/*
Funcion que se encarga de crear el espacio en memoria para una Lista Enlazada y retornar 
un apuntador a ese espacio.
*/
LinkedList * crearLista(){
	LinkedList *nueva = (LinkedList*) malloc(sizeof(LinkedList));

	return nueva;
}

/*
Funcion que se encarga de imprimir los nombres de los Productos que se estan almacenando
en la Lista Enlazada 'l'.
*/
void imprimirLista(LinkedList *l){
	Producto *p = l->head;
	while(p){
		printf("%s\n", p->nombre);
		p = p->next;
	}
}

/*
Funcion que se encarga de imprimir los nombres de los Productos que se estan almacenando
en la Lista Enlazada 'l'.
*/
void eliminarLista(LinkedList *l){
	Producto *p = l->head;
	Producto *aux;
	while(p){
		aux = p->next;
		free(p);
		p = aux;
	}
}