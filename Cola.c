#include <stdio.h>
#include <stdlib.h>
#include "mercado.h"

/*
Funcion que se encarga de crear el espacio en memoria para una Cola y retornar 
un apuntador a ese espacio.
*/
Cola * crearCola(){
	Cola *nueva = (Cola*) malloc(sizeof(Cola));

	return nueva;
}

/*
Funcion que se encarga de agregar un Producto 'p' a la Cola 'c'.
*/
void agregarCola(Cola *c, Producto *p) {
	if (!(c->tail)){
		c->head = p;
		c->tail = p;
	}
	c->tail->next = p;
	c->tail = p;
	c->cant += 1;
}

/*
Funcion que se encarga de eliminar el primer Producto 'p' introducido de la Cola 'c', quien
seria la cola de la Cola, y lo retorna. En caso de que la cola este vacia, retornara NULL.
*/
Producto *quitarCola(Cola *c) {
	Producto *actual = c->head;
	if (c->cant > 0) {
		c->head = c->head->next;
		free(actual);
		if(c->cant > 0) {
			c->tail = NULL;
		}
	}
	else {
		printf("La cola esta vacia!!\n");
	}
	return actual;
}

/*
Funcion que se encarga de imprimir los nombres de los Productos que se estan almacenando
en la Cola 'c'.
*/
void imprimirCola (Cola *c) {
	printf("\n >>>> Productos en la cola: \n");
	Producto *actual = c->head;
	while(actual != NULL){
		printf("%s\n", actual->nombre);
		actual = actual->next;
	}
}