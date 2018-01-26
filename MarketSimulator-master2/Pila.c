#include <stdio.h>
#include <stdlib.h>
#include "mercado.h"

/*
Funcion que se encarga de crear el espacio en memoria para una Pila y retornar 
un apuntador a ese espacio.
*/
Pila * crearPila(){
	Pila *nueva = (Pila*) malloc(sizeof(Pila));

	return nueva;
}

/*
Funcion que se encarga de agregar un Producto 'p' a la Pila 's'.
*/
void agregarPila (Pila *s, Producto *p) {
	p->next = s->head;
	s->head = p;
	s->cant += 1;
}

/*
Funcion que se encarga de eliminar el primer Producto 'p' de la Pila 's', quien
seria la cabeza de la Pila, y lo retorna. En caso de que la lista este vacia, retornara NULL.
*/
Producto *quitarPila (Pila *s) {
	Producto *actual = s->head;
	if (s->cant > 0) {
		s->head = actual->next;
		s->cant = s->cant - 1;	
	}
	else {
		printf("La pila vacia!!\n");
	}
	return actual;
}

/*
Funcion que se encarga de imprimir los nombres de los Productos que se estan almacenando
en la Pila 's'.
*/
void imprimirPila (Pila *s) {
	printf("\n >>>> Productos en la pila: \n");
	Producto *actual = s->head;
	while(actual != NULL){
		printf("%s\n", actual->nombre);
		actual = actual->next;
	}
}