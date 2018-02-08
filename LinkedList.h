
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
