//---------------------------------------------------------
//  MARKET SIMULATOR
//
//  Fecha de elaboracion: 8/2/2018
//
//  Autores:
//           Jose Donato Bracuto Delgado 13-10173
//           Miguel Clemente Canedo Rodriguez 13-10214
//---------------------------------------------------------

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

/*
Funcion que se encarga de crear el espacio en memoria para una Cola y retornar 
un apuntador a ese espacio.
*/
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


/*
Funcion que se encarga de vaciar la Cola indicada por parametro. 
*/
void vaciarCola(Cola *);