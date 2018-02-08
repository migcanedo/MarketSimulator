//----------------------------------------------------------------------
// Estructura
//----------------------------------------------------------------------
/*
Estructura que se comportara como un Nodo de diferentes estructuras de 
almacenamiento. En ella se guardara el nombre, peso y complejidad de
procesamiento del Producto; ademas de guardar la direccion del Producto 
siguiente a el mismo segun en la estructura que se eencuentre  almacenando.
*/
#ifndef NODO_PROD
#define NODO_PROD
typedef struct Producto
{
	char nombre[100];
	int peso;
	float complejidad;
} Producto;


/*
Estructura qeu se comportara como un Nodo para las diferentes estructuras 
de Almacenamiento. En ella se guardaran el apuntador al Producto que se esta
almacenando en el Nodo, el apuntador hacia el Nodo que le sigue al mismo en la 
estructura de almacenamiento y un apuntador hacia la estructura Nodo previa.
*/
typedef struct Nodo
{
	Producto * prod;
	struct Nodo * next;
	struct Nodo * prev;
}Nodo;

#endif

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

/*
Funcion que se encarga de crear el espacio en memoria para una Pila y retornar 
un apuntador a ese espacio.
*/
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


/*
Funcion que se encarga de vaciar la Pila indicada por parametro. 
*/
void vaciarPila (Pila *);
