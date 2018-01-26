#include <stdio.h>
#include <stdlib.h>
#include "mercado.h"
#define true 1
#define false 0


typedef int bool;
int modalidad = 1; // 1 := Interactiva || 2 := Automatica
int nCarritos = 3;
long maxProductos = 30;
long maxPesoBanda = 200;
float velCajera = 1.0;
float velEmbolsador = 4;
long tFacturacion = 130;
long maxPesoAreaEmbolsado = 150;
long maxPesoBolsa = 120;

int main(int argc, char* argv[]){
	int opc;
	int opc2;
	bool config = true;

	if (argc < 2){
		printf("\nError. Debe indicar el nombre del archivo donde se encuentra el Inventario.\n\n");
		exit(1);
	}
	
	LinkedList * inventario = crearInventario(argv[1]);

	imprimirLista(inventario);

	printf("\nBienvenido al MarketSimulator!\n");
	while (TRUE){
		printf("\nQue desea hacer?\n\n");
		printf("\t1. Ejecutar la simulacion.\n");
		printf("\t2. Cambiar las opciones de la simulacion.\n");
		printf("\t3. Salir del Programa.\n\n");
		printf(">> ");

		scanf("%d", &opc);

		switch (opc){
			case 1: break;
			case 2: 
				printf("\nMenu de configuracion:");
				while (config){
					printf("\nQue desea hacer?\n\n");
					printf("\t1. Cambiar la modalidad.\n");
					printf("\t2. Cambiar la cantidad de carritos en la cola.\n");
					printf("\t3. Cambiar la cantidad maxima de productos por carrito.\n");
					printf("\t4. Cambiar la capacidad maxima d ela banda.\n");
					printf("\t5. Cambiar la cantidad de operaciones pro segundo de la cajera.\n");
					printf("\t6. Cambiar los segudos por bolsa que require el embolsador.\n");
					printf("\t7. Cambiar el tiempo de facturacion.\n");
					printf("\t8. Cambiar la capacidad maxima del area de embolsado.\n");
					printf("\t9. Cambiar la capacidad maxima de las bolsas.\n");
					printf("\t10. Salir de menu de configuracion.\n");
					printf(">> ");

					scanf("%d", &opc2);

					switch (opc2){
						case 1: break;
						case 2: break;
						case 3: break;
						case 4: break;
						case 5: break;
						case 6: break;
						case 7: break;
						case 8: break;
						case 9: break;
						case 10: config = false;
						default: printf("\nOpcion Invalida. Elija una opcion valida del menu.\n");
					}
				}
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