// Constantes.
#define FOR(i, a, b) int i; for(i = (a); i < (b); i++)
#define TRUE 0 == 0
#define FALSE !TRUE

// //----------------------------------------------------------------------
// // Variables Globales. 
//----------------------------------------------------------------------

// extern int modalidad; // 1 := Interactiva || 2 := Automatica
// extern int nCarritos;
// extern long maxProductos;
// extern long maxPesoBanda;
// extern float velCajera;
// extern float velEmbolsador;
// extern long tFacturacion;
// extern long maxPesoAreaEmbolsado;
// extern long maxPesoBolsa;

//----------------------------------------------------------------------
// Estructuras
//----------------------------------------------------------------------

/*
Estructura que se comportara como un Nodo de diferentes estructuras de 
almacenamiento. En ella se guardara el nombre, peso y complejidad de
procesamiento del Producto; ademas de guardar la direccion del Producto 
siguiente a el mismo segun en la estructura que se eencuentre  almacenando.
*/
typedef struct Producto
{
	char nombre[100];
	int peso;
	float complejidad;
	struct Producto * next;
} Producto;

/* 
Estructura que se comportara como una Lista Enlazada, donde se guarda la 
direccion de su primer Prdocuto de la misma. 

Para funciones de la simulacion del mercado, esta estructura servira para 
simular al Carro. Ordenando sus productos segun su peso, de menor a mayor.
 */
typedef struct LinkedList
{
	Producto *head;
	int cant;

}LinkedList;


/* Area de Embolsado */
typedef struct Pila
{
	
}Pila;

/* Banda */
typedef struct Cola
{

}Cola;

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

/*
Funcion que dado el nombre del archivo donde se encuentra el inventario, crea una lista enlazada con los 
productos del mismo.
*/
LinkedList * crearInventario(char *);


