#include "mercado.h"
#define FOR(i, a, b) int i; for(i = (a); i < (b); i++)
#define TRUE 0 == 0
#define FALSE !TRUE

//----------------------------------------------------------------------
// Estructura
//----------------------------------------------------------------------

/* 
Estructura que se comportara como una COla trabajando con una lista enlazada,
donde se guardara la direccion tanto del primer como del ultimo elemento agregado.

Para funciones de la simulacion del mercado, esta estructura servira para 
simular la Banda. Agregando los productos que salen del carro y sacando los procesados.
*/
typedef struct Cola
{
	Nodo *head, *tail;
	int cant;

}Cola;

//----------------------------------------------------------------------
// Funciones.
//----------------------------------------------------------------------

/*
Funcion que se encarga de agregar un Producto 'p' a la Cola 'c'.
*/
void agregarCola (Cola *, Producto *);

//ESTA FUNCION SE BORRARA
Cola * crearCola ();

/*
Funcion que se encarga de eliminar el primer Producto 'p' introducido en la Cola 'c', quien
seria la cola de la Cola, y lo retorna.
*/
Producto *quitarCola (Cola *);

/*
Funcion que se encarga de imprimir los nombres de los Productos que se estan almacenando
en la Cola 'c'.
*/
void imprimirCola(Cola *);