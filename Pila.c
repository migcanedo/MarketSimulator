#include <stdio.h>
#include <stdlib.h>
#include "mercado.h"

/*
Funcion que se encarga de crear el espacio en memoria para una Pila y retornar 
un apuntador a ese espacio.
*/
Pila * crearPila(){
	Pila *nueva = (Pila*) malloc(sizeof(Pila));
	nueva->head = NULL;
	nueva->cant = 0;

	return nueva;
}

/*
Funcion que se encarga de agregar un Producto 'p' a la Pila 's'.
*/
void agregarPila (Pila *s, Producto *p) {
	Nodo *n = (Nodo*) malloc(sizeof(Nodo));
	n->prod = p;
	n->next = s->head;
	s->head = n;
	//printf("'%s' ha sido metido a la pila\n", p->nombre);
	s->cant += 1;
}

/*
Funcion que se encarga de eliminar el primer Producto 'p' de la Pila 's', quien
seria la cabeza de la Pila, y lo retorna. En caso de que la lista este vacia, retornara NULL.
*/
Producto *quitarPila (Pila *s) {
	Nodo *actual = s->head;
	Producto *prodAct = actual->prod;
	if (s->cant > 0) {
		s->head = actual->next;
		s->cant = s->cant - 1;
		free(actual);	
	}
	else {
		printf("La pila vacia!!\n");
	}
	return prodAct;
}

/*
Funcion que se encarga de imprimir los nombres de los Productos que se estan almacenando
en la Pila 's'.
*/
void imprimirPila (Pila *s) {
	Nodo *actual = s->head;
	int i = 1;
	while(i<= s->cant){
		printf("\t%s\n", actual->prod->nombre);
		actual = actual->next;
		++i;
	}
}

void vaciarPila (Pila *s) {
	int i = 0;
	while(i < s->cant){
		quitarPila(s);
	}
}