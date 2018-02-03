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
	c->cant += 1;
}

/*
Funcion que se encarga de eliminar el primer Producto 'p' introducido de la Cola 'c', quien
seria la cola de la Cola, y lo retorna. En caso de que la cola este vacia, retornara NULL.
*/
Producto *quitarCola(Cola *c) {
	Nodo *actual = c->head;
	Producto *prodAct = actual->prod;
	if (c->cant > 0) {
		c->head = c->head->next;
		c->cant = c->cant - 1;
		free(actual);
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
	printf("\n >>>> Productos en la cola: \n");
	Nodo *actual = c->head;
	while(actual != NULL){
		printf("%s\n", actual->prod->nombre);
		actual = actual->next;
	}
}