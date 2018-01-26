// Constantes.
#define FOR(i, a, b) int i; for(i = (a); i < (b); i++)
#define TRUE 0 == 0
#define FALSE !TRUE


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

/*
Funcion que imprime en pantalla y gestiona el menu de Cambio de configuracion del MarketSimulator.
*/
void menuConfiguracion();


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