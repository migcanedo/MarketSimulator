#include <stdio.h>
#include <stdlib.h>
#include "mercado.h"

/*
Funcion que se encarga de crear el espacio en memoria para una Cola y retornar 
un apuntador a ese espacio.
*/
Cola * crearCola(){
	Cola *nueva = (Cola*) malloc(sizeof(Cola));
	nueva->head = NULL;
	nueva->tail = NULL;
	nueva->cant = 0;

	return nueva;
}

/*
Funcion que se encarga de agregar un Producto 'p' a la Cola 'c'.
*/
void agregarCola(Cola *c, Producto *p) {
	Nodo *n = (Nodo*) malloc(sizeof(Nodo));
	n->prod = p;

	if (!(c->tail)){
		c->head = n;
		c->tail = n;
	}
	c->tail->next = n;
	c->tail = n;

	//printf("'%s' ha sido metido a la cola\n", p->nombre);
	c->cant += 1;
}

/*
Funcion que se encarga de eliminar el primer Producto 'p' introducido de la Cola 'c', quien
seria la cola de la Cola, y lo retorna. En caso de que la cola este vacia, retornara NULL.
*/
Producto *quitarCola(Cola *c) {
	Nodo *actual = c->head;
	Producto *prodAct;
	prodAct = actual->prod;
	if (c->cant > 0) {
		c->head = c->head->next;
		//printf("'%s' ha sido sacado de la cola\n", actual->prod->nombre);
		free(actual);
		c->cant = c->cant - 1;
		if(c->cant == 0){
			c->tail = NULL;
		}
	}
	else {
		printf("La cola esta vacia!!\n");
	}
	return prodAct;
}

/*
Funcion que se encarga de imprimir los nombres de los Productos que se estan almacenando
en la Cola 'c'.
*/
void imprimirCola (Cola *c) {
	Nodo *actual = c->head;
	int i = 1;
	while(i<= c->cant){
		if(actual == NULL){
			printf("NULL\n");
		}
		printf("\t%s\n", actual->prod->nombre);
		actual = actual->next;
		++i;
	}
}


/*
Funcion que se encarga de vaciar la Cola indicada por parametro. 
*/
void vaciarCola (Cola *c) {
	while(c->cant > 0){
		quitarCola(c);
	}
	free(c);
}
