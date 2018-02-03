#include "mercado.h"
// Constantes.
#define FOR(i, a, b) int i; for(i = (a); i < (b); i++)
#define TRUE 0 == 0
#define FALSE !TRUE

//----------------------------------------------------------------------
// Estructura
//----------------------------------------------------------------------

/* 
Estructura que se comportara como una Lista Enlazada, donde se guarda la 
direccion de su primer Prdocuto de la misma. 

Para funciones de la simulacion del mercado, esta estructura servira para 
simular al Carro. Ordenando sus productos segun su peso, de menor a mayor.
 */
typedef struct LinkedList
{
	Nodo *head;
	int cant;

}LinkedList;

//----------------------------------------------------------------------
// Funciones.
//----------------------------------------------------------------------

/*
Funcion que se encarga de agregar un Producto 'p' a la Lista Enlazada 'l'.
*/
void agregarElem(LinkedList *, Producto *);

/*
Funcion que se encarga de eliminar el primer Producto 'p' de la Lista Enlazada 'l', quien
seria la cabeza de la lista, y lo retorna.
*/
Producto *eliminarElem(LinkedList *);

/*
Funcion que se encarga de crear el espacio en memoria para una Lista Enlazada y retornar 
un apuntador a ese espacio.
*/
LinkedList * crearLista();

/*
Funcion que se encarga de imprimir los nombres de los Productos que se estan almacenando
en la Lista Enlazada 'l'.
*/
void eliminarLista(LinkedList *);

/*
Funcion que se encarga de imprimir los nombres de los Productos que se estan almacenando
en la Lista Enlazada 'l'.
*/
void imprimirLista(LinkedList *);
