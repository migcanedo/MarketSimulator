#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mercado.h"
#define true 1
#define false 0


typedef int bool;
int modalidad = 1; // 1 := Interactiva || 2 := Automatica
int nCarritos = 3;
int maxProductos = 5;
int maxPesoBanda = 240;
float velCajera = 1.0;
float velEmbolsador = 4;
int tFacturacion = 130;
int maxPesoAreaEmbolsado = 150;
int maxPesoBolsa = 120;

int tCliente = 0;
float complejidadAct = 0;
int pesoBanda;
int facturado = FALSE;
int operacion = 0;
Producto *prodBanda;
Producto *prodPila;

int main(int argc, char* argv[]){
	int opc;
	if (argc < 2){
		printf("\nError. Debe indicar el nombre del archivo donde se encuentra el Inventario.\n\n");
		exit(1);
	}
	
	LinkedList * inventario = crearInventario(argv[1]);


	printf("\nBienvenido al MarketSimulator!\n");
	while (TRUE){
		printf("-----------------------------------------------\n");
		printf("Menu Principal:\n");
		printf("\nQue desea hacer?\n\n");
		printf("\t1. Ejecutar la simulacion.\n");
		printf("\t2. Cambiar las opciones de la simulacion.\n");
		printf("\t3. Salir del Programa.\n\n");
		printf(">> ");

		scanf("%d", &opc);
		getchar();
		switch (opc){
			case 1: 
				simulacion(inventario);
				break;
			case 2: 
				menuConfiguracion();
				break;
			case 3: exit(0);
			default: printf("\nOpcion Invalida. Elija una opcion valida del menu.\n"); 
		}
	}

	eliminarLista(inventario);
}


/*
Funcion que dado el nombre del archivo donde se encuentra el inventario, crea una lista enlazada con los 
productos del mismo.
*/
LinkedList *crearInventario(char *archivo){
	FILE *fp;
	fp = fopen(archivo, "r");
	if(!fp){
		printf("\nError. No existe el Archivo.\n\n");
		exit(0);
	}

	LinkedList *inventario = crearLista();

	Producto *pp = (Producto*) malloc(sizeof(Producto));

	while (fscanf(fp, "%[^\t]\t%d\t%f\n", pp->nombre, &(pp->peso), &(pp->complejidad)) == 3){
        agregarElem(inventario, pp);
        pp = (Producto*) malloc(sizeof(Producto));
	}

    fclose(fp);
    return inventario;
}

/*

*/
void simulacion(LinkedList *inventario){
	srand(time(NULL));
	
	// Crear los carritos.
	LinkedList * carritos[nCarritos];
	Cola * banda = crearCola();
	Pila * areaEmb = crearPila();

	/**
	int p, ite;
	carritos[0] = crearLista();
	ite = 0;
	Nodo * n = inventario->head;
	p = 12;
	while (ite < p){
		n = n->next;
		ite += 1;
	}
	agregarElem(carritos[0], n->prod);

	ite = 0;
	n = inventario->head;
	p = 17;
	while (ite < p){
		n = n->next;
		ite += 1;
	}
	agregarElem(carritos[0], n->prod);

	ite = 0;
	n = inventario->head;
	p = 16;
	while (ite < p){
		n = n->next;
		ite += 1;
	}
	agregarElem(carritos[0], n->prod);

	ite = 0;
	n = inventario->head;
	p = 23;
	while (ite < p){
		n = n->next;
		ite += 1;
	}
	agregarElem(carritos[0], n->prod);

	imprimirDatos(carritos[0], banda, areaEmb);
	printf("%d%d\n", carritos[0]->cant, banda->cant);
	**/
	/**
	while(carritos[0]->cant >0){
		prodBanda = eliminarElem(carritos[0]);
		agregarCola(banda, prodBanda);
		imprimirDatos(carritos[0], banda, areaEmb);
	}
	while(banda->cant > 0){
		prodPila = quitarCola(banda);
		agregarPila(areaEmb ,prodPila);
		imprimirDatos(carritos[0], banda, areaEmb);
	}**/
	/**
	while(carritos[0]->cant > 0){
		prodBanda = eliminarElem(carritos[0]);
		agregarCola(banda, prodBanda);
		prodPila = quitarCola(banda);
		agregarPila(areaEmb ,prodPila);
		imprimirDatos(carritos[0], banda, areaEmb);
	}**/

	printf("\n====CARRITOS==CREADOS====\n");
	int i, j, cantProd, p, ite;
	for(i = 0; i < nCarritos; i++){
		carritos[i] = crearLista();
		cantProd = rand() % maxProductos + 1;
		//printf("-----------------------\n" );
		for(j = 0; j < cantProd; j++){
			p = rand() % (inventario->cant);
			ite = 0;
			Nodo * n = inventario->head;
			while (ite < p){
				n = n->next;
				ite += 1;
			}
			agregarElem(carritos[i], n->prod);
		}
		printf("\n======CARRITO==%d======\n", i);
		imprimirLista(carritos[i]);
	}

	//Ciclo que procesa a los clientes uno a uno (se empieza a procesar despues de que el cliente acterior haya sido facturado)
	pesoBanda = maxPesoBanda;
	for(i = 0; i < nCarritos; i++){
		printf("\n======CARRITO==NUMERO==%d=========\n", i);
		printf("============INSTANTE==%d=========\n", operacion);
		prodBanda = eliminarElem(carritos[i]);
		agregarCola(banda, prodBanda);
		pesoBanda = pesoBanda - prodBanda->peso;
		complejidadAct = prodBanda->complejidad;
		imprimirDatos(carritos[i], banda, areaEmb);
		++operacion;
		int t = 0;

		//ciclo en el que cada iteracion representa un instante de tiempo (como si el enter fuera presionado automaticamente)
		while(!facturado){
			printf("============INSTANTE==%d========\n", operacion);
			complejidadAct = complejidadAct - velCajera;
			//comprueba si hay espacio en la banda y saca producto del carrito hacia la banda
			if(carritos[i]->cant >0 && carritos[i]->head->prod->peso <= pesoBanda){
				prodBanda = eliminarElem(carritos[i]);
				agregarCola(banda, prodBanda);
				pesoBanda = pesoBanda - prodBanda->peso;
			}
			//comprueba si el tiempo de procesqamiento del primer objeto de la banda ya paso y cantinua con el siguiente objeto
			//printf("============PASO PRIMER IF========\n");
			if(complejidadAct <= 0){
				prodPila = quitarCola(banda);
				pesoBanda = pesoBanda + prodPila->peso;
				if(carritos[i]->cant == 0 && banda->cant == 0){
					facturado = TRUE;
				}
				else{
					complejidadAct = banda->head->prod->complejidad - complejidadAct;
				}
				agregarPila(areaEmb, prodPila);
			}
			//comprueba si hay espacio en la banda y saca producto del carrito hacia la banda
			//printf("============PASO SEGUNDO IF========\n");
			if(carritos[i]->cant >0 && carritos[i]->head->prod->peso <= pesoBanda){
				prodBanda = eliminarElem(carritos[i]);
				agregarCola(banda, prodBanda);
				pesoBanda = pesoBanda - prodBanda->peso;
			}
			//printf("============PASO TERCER IF========\n");
			++operacion;
			imprimirDatos(carritos[i], banda, areaEmb);
			++t;
		}
		//termina de procesar a un cliente y reinicia todas las variables
		tCliente = operacion - 1 + tFacturacion;
		printf("====CLIENTE NUMERO %d TARDO %d EN SER FACTURADO===\n", i, tCliente);
		operacion = 0;
		facturado = FALSE;
		vaciarPila(areaEmb);

	}
	/**
	pesoBanda = maxPesoBanda;
	printf("============OPERACION==%d=========\n", operacion);
	prodBanda = eliminarElem(carritos[0]);
	agregarCola(banda, prodBanda);
	pesoBanda = pesoBanda - prodBanda->peso;
	complejidadAct = prodBanda->complejidad;
	imprimirDatos(carritos[0], banda, areaEmb);
	++operacion;
	int t = 0;

	while(!facturado){
		printf("============OPERACION==%d========\n", operacion);
		complejidadAct = complejidadAct - velCajera;
		if(carritos[0]->cant >0 && carritos[0]->head->prod->peso <= pesoBanda){
			prodBanda = eliminarElem(carritos[0]);
			agregarCola(banda, prodBanda);
			pesoBanda = pesoBanda - prodBanda->peso;
		}
		//printf("============PASO PRIMER IF========\n");
		if(complejidadAct <= 0){
			prodPila = quitarCola(banda);
			pesoBanda = pesoBanda + prodPila->peso;
			if(carritos[0]->cant == 0 && banda->cant == 0){
				facturado = TRUE;
			}
			else{
				complejidadAct = banda->head->prod->complejidad - complejidadAct;
			}
			agregarPila(areaEmb, prodPila);
		}
		//printf("============PASO SEGUNDO IF========\n");
		if(carritos[0]->cant >0 && carritos[0]->head->prod->peso <= pesoBanda){
			prodBanda = eliminarElem(carritos[0]);
			agregarCola(banda, prodBanda);
			pesoBanda = pesoBanda - prodBanda->peso;
		}
		//printf("============PASO TERCER IF========\n");
		++operacion;
		imprimirDatos(carritos[0], banda, areaEmb);
		++t;
	}
	tCliente = operacion - 1 + tFacturacion;
	printf("CLiente numero %d tardo %d en ser facturado\n", 0, tCliente);
	operacion = 0;
	**/

	// Pasar productos del carrito a la Banda.


	// Procesar productos de la Banda.

	// Pasar productos procesados al Area de Embolsado.

	// Meter en bolsa productos del Area de Embolsado.
}


void imprimirDatos(LinkedList *lista, Cola *cola, Pila *pila){
	//printf("ComplejidadAct:%f\nPesoBanda:%d\n", complejidadAct, pesoBanda);
	imprimirLista(lista);
	imprimirCola(cola);
	imprimirPila(pila);
}

/*
Funcion que imprime en pantalla y gestiona el menu de Cambio de configuracion del MarketSimulator.
*/
void menuConfiguracion(){
	int opc2;
	char opc3;
	int aux;
	float aux1;
	bool config = true;

	while (config){
		printf("\n-----------------------------------------------\n");
		printf("Menu de Configuracion:\n");
		printf("\nQue desea hacer?\n\n");
		printf("\t1. Cambiar la modalidad.\n");
		printf("\t2. Cambiar la cantidad de carritos en la cola.\n");
		printf("\t3. Cambiar la cantidad maxima de productos por carrito.\n");
		printf("\t4. Cambiar la capacidad maxima de la banda.\n");
		printf("\t5. Cambiar la cantidad de operaciones por segundo de la cajera.\n");
		printf("\t6. Cambiar los segudos por bolsa que require el embolsador.\n");
		printf("\t7. Cambiar el tiempo de facturacion.\n");
		printf("\t8. Cambiar la capacidad maxima del area de embolsado.\n");
		printf("\t9. Cambiar la capacidad maxima de las bolsas.\n");
		printf("\t10. Salir de menu de configuracion.\n");
		printf(">> ");

		scanf("%d", &opc2);
		getchar();
		
		switch (opc2){
			case 1: 
					printf("\nLa modalidad actual es: \"%s\"\n", (modalidad ? "Interactiva" : "Automatica"));
					printf("Desea cambiarla a \"%s\"? (y: Si/otro: No)  ", (!modalidad ? "Interactiva" : "Automatica"));

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						modalidad = (modalidad + 1) % 2; 
						printf("\nModalidad cambiada exitosamente a: \"%s\"\n", (modalidad ? "Interactiva" : "Automatica"));
					}
					break;
			case 2: printf("\nLa cantidad actual de Carritos en la cola es: \"%d\"\n", nCarritos);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux = nCarritos;
						printf("Indique la nueva cantidad de Carritos que habra en la cola: ");
						scanf("%d", &nCarritos);
						getchar();
						
						printf("\nLa cantidad de Carritos en la cola se ha cambiado exitosamente de: \"%d\" a: \"%d\"\n", 
																												aux, nCarritos);
					}
					break;
			case 3: printf("\nLa cantidad actual maxima de Productos por Carrito es: \"%d\"\n", maxProductos);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux = maxProductos;
						printf("Indique la nueva cantidad maxima de Productos por Carrito: ");
						scanf("%d", &maxProductos);
						getchar();
						
						printf("\nLa cantidad maxima de Prodcutos por Carrito se ha cambiado exitosamente de: \"%d\" a: \"%d\"\n", 
																												aux, maxProductos);
					}
					break;
			case 4: printf("\nLa capacidad maxima actual de la Banda es: \"%dcc\"\n", maxPesoBanda);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux = maxPesoBanda;
						printf("Indique la nueva capacidad maxima de la Banda: ");
						scanf("%d", &maxPesoBanda);
						getchar();
						
						printf("\nLa capacidad maxima de la Banda se ha cambiado exitosamente de: \"%dcc\" a: \"%dcc\"\n", 
																												aux, maxPesoBanda);
					}
					break;
			case 5: printf("\nLa cantidad actual de Operaciones por Segundo que realiza la Cajera es: \"%f\"\n", velCajera);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux1 = velCajera;
						printf("Indique la nueva cantidad de Operaciones por Segundo que realizara la Cajera: ");
						scanf("%f", &velCajera);
						getchar();
						
						printf("\nLa cantidad de Operaciones por Segundo que realiza la Cajera se ha cambiado exitosamente de: \"%f\" a: \"%f\"\n", 
																												aux1, velCajera);
					}
					break;
			case 6: printf("\nLa cantidad actual de Segundos por Bolsa que require el Embolsador es: \"%f\"\n", velEmbolsador);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux1 = velEmbolsador;
						printf("Indique la nueva cantidad de Segundos por Bolsa que requiere el Embolsador: ");
						scanf("%f", &velEmbolsador);
						getchar();
						
						printf("\nLa cantidad de Segundos por Bolsa que requiere el Embolsador se ha cambiado exitosamente de: \"%f\" a: \"%f\"\n", 
																												aux1, velEmbolsador);
					}
					break;
			case 7: printf("\nEl tiempo actual de Facturacion es: \"%ds\"\n", tFacturacion);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux = tFacturacion;
						printf("Indique el nuevo tiempo de Facturacion: ");
						scanf("%d", &tFacturacion);
						getchar();
						
						printf("\nEl tiempo de Facturacion se ha cambiado exitosamente de: \"%ds\" a: \"%ds\"\n", 
																												aux, tFacturacion);
					}
					break;
			case 8: printf("\nLa capacidad maxima actual del Area de Embolsado es: \"%dcc\"\n", maxPesoAreaEmbolsado);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux = maxPesoAreaEmbolsado;
						printf("Indique la nueva capacidad maxima del Area de Embolsado: ");
						scanf("%d", &maxPesoAreaEmbolsado);
						getchar();
						
						printf("\nLa capacidad maxima del Area de Embolsado se ha cambiado exitosamente de: \"%dcc\" a: \"%dcc\"\n", 
																												aux, maxPesoAreaEmbolsado);
					}
					break;
			case 9: printf("\nLa capacidad maxima actual de las Bolsas es: \"%dcc\"\n", maxPesoBolsa);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux = maxPesoBolsa;
						printf("Indique la nueva capacidad maxima de las Bolsas: ");
						scanf("%d", &maxPesoBolsa);
						getchar();
						
						printf("\nLa capacidad maxima de las Bolsas se ha cambiado exitosamente de: \"%dcc\" a: \"%dcc\"\n", 
																												aux, maxPesoBolsa);
					}
					break;
			case 10: config = FALSE;
					break;
			default: printf("\nOpcion Invalida. Elija una opcion valida del menu.\n");
		}
	}
}
