#include "mercado.h"
// Constantes.
#define FOR(i, a, b) int i; for(i = (a); i < (b); i++)
#define TRUE 0 == 0
#define FALSE !TRUE

//----------------------------------------------------------------------
// Estructura
//----------------------------------------------------------------------

/* 
Estructura que se comportara como una Pila trabajando con una lista enlazada,
donde se guardara la direccion del primer producto conforme se van agregando.

Para funciones de la simulacion del mercado, esta estructura servira para
simular el area de embolsado. Empilando los productos procesados por la cajera.
*/
typedef struct Pila
{	
	Nodo *head;
	int cant;
	
}Pila;

//----------------------------------------------------------------------
// Funciones.
//----------------------------------------------------------------------

/*
Funcion que se encarga de agregar un Producto 'p' a la Pila 's'.
*/
void agregarPila (Pila *, Producto *);

//ESTA FUNCION SE EBORRARA
Pila * crearPila();

/*
Funcion que se encarga de eliminar el primer Producto 'p' de la Pila 's', quien
seria la cabeza de la pila, y lo retorna.
*/
Producto *quitarPila (Pila *);

/*
Funcion que se encarga de imprimir los nombres de los Productos que se estan almacenando
en la Pila 's'.
*/
void imprimirPila (Pila *);