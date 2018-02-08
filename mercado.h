#include "LinkedList.h"
#include "Cola.h"
#include "Pila.h"

// Constantes.
#define TRUE 0 == 0
#define FALSE !TRUE

//----------------------------------------------------------------------
// Funciones.
//----------------------------------------------------------------------
/*
Funcion que dado el nombre del archivo donde se encuentra el inventario, crea una lista enlazada con los 
productos del mismo.
*/
LinkedList * crearInventario(char *);

/*
Funcion que se encarga de ejecutar la simulacion del mercado, con el Inventario que se le pasa por argumento y
utilizando la configuracion global del programa.
*/
void simulacion(LinkedList *);

/*
Funcion que se encarga de imprimir en pantalla de forma ordenada los elementos que pertenecen 
a una Lista Enlazada, una Cola, una Pila y un Arreglo de Pilas de tama;o 'cantBolsas'.
*/
void imprimirDatos(LinkedList *lista, Cola *cola, Pila *pila, Pila *bolsas[], int cantBolsas);

/*
Funcion que imprime en pantalla y gestiona el menu de Cambio de configuracion del MarketSimulator.
*/
void menuConfiguracion();