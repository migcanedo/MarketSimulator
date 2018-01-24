// Constantes.
#define FOR(i, a, b) int i; for(i = (a); i < (b); i++)
#define TRUE 0 == 0
#define FALSE !TRUE
#define MAX_LINE 1000

// //----------------------------------------------------------------------
// // Variables Globales. 
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
	Producto *head;
	int cant;
	
}Pila;

/* Banda */
typedef struct Cola
{
	Producto *head, *tail;
	int cant;

}Cola;

//----------------------------------------------------------------------
// Funciones.
void agregarLista (LinkedList *, Producto *);

LinkedList * crearInventario(char *);

void agregarPila (Pila *, Producto *);

Pila * crearPila(char *);

void quitarPila (Pila *);

void imprimirPila (Pila *);

void agregarCola (Cola *, Producto *);

Cola * crearCola (char *);

void quitarCola (Cola *);

void imprimirCola(Cola *);


