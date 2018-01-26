#include <stdio.h>
#include <stdlib.h>
#include "mercado.h"
#define true 1
#define false 0


typedef int bool;
int modalidad = 1; // 1 := Interactiva || 2 := Automatica
int nCarritos = 3;
int maxProductos = 30;
int maxPesoBanda = 200;
float velCajera = 1.0;
float velEmbolsador = 4;
int tFacturacion = 130;
int maxPesoAreaEmbolsado = 150;
int maxPesoBolsa = 120;

int main(int argc, char* argv[]){
	int opc;
	

	if (argc < 2){
		printf("\nError. Debe indicar el nombre del archivo donde se encuentra el Inventario.\n\n");
		exit(1);
	}
	
	LinkedList * inventario = crearInventario(argv[1]);

	imprimirLista(inventario);

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
			case 1: break;
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
Funcion que imprime en pantalla y gestiona el menu de Cambio de configuracion del MarketSimulator.
*/
void menuConfiguracion(){
	int opc2;
	char opc3;
	int aux;
	bool config = true;

	while (config){
		printf("\n-----------------------------------------------\n");
		printf("Menu de configuracion:\n");
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
			case 2: printf("\nLa cantidad actual de carritos en la cola es: \"%d\"\n", nCarritos);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux = nCarritos;
						printf("Indique la nueva cantidad de carritos que habra en la cola: ");
						scanf("%d", &nCarritos);
						getchar();
						
						printf("\nLa cantidad de Carritos en la cola se ha cambiado exitosamente de: \"%d\" a: \"%d\"\n", 
																												aux, nCarritos);
					}
					break;
			case 3: printf("\nLa cantidad actual maxima de productos por carrito es: \"%d\"\n", maxProductos);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux = maxProductos;
						printf("Indique la nueva cantidad maxima de prodcutos por carrito: ");
						scanf("%d", &maxProductos);
						getchar();
						
						printf("\nLa cantidad maxima de Prodcutos por Carrito se ha cambiado exitosamente de: \"%d\" a: \"%d\"\n", 
																												aux, maxProductos);
					}
					break;
			case 4: printf("\nLa capacidad maxima actual de la Banda es: \"%d\"\n", maxPesoBanda);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux = maxPesoBanda;
						printf("Indique la nueva capacidad maxima de la Banda: ");
						scanf("%d", &maxPesoBanda);
						getchar();
						
						printf("\nLa capacidad maxima de la Banda se ha cambiado exitosamente de: \"%d\" a: \"%d\"\n", 
																												aux, maxPesoBanda);
					}
					break;
			case 5: 
					break;
			case 6: 
					break;
			case 7: 
					break;
			case 8: printf("\nLa capacidad maxima actual del Area de Embolsado es: \"%d\"\n", maxPesoAreaEmbolsado);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux = maxPesoAreaEmbolsado;
						printf("Indique la nueva capacidad maxima del Area de Embolsado: ");
						scanf("%d", &maxPesoAreaEmbolsado);
						getchar();
						
						printf("\nLa capacidad maxima del Area de Embolsado se ha cambiado exitosamente de: \"%d\" a: \"%d\"\n", 
																												aux, maxPesoAreaEmbolsado);
					}
					break;
			case 9: printf("\nLa capacidad maxima actual de las Bolsas es: \"%d\"\n", maxPesoBolsa);
					printf("Desea cambiarla? (y: Si/otro: No)  ");

					scanf("%c", &opc3);
					getchar();

					if (opc3 == 'y') {
						aux = maxPesoBolsa;
						printf("Indique la nueva capacidad maxima de las Bolsas: ");
						scanf("%d", &maxPesoBolsa);
						getchar();
						
						printf("\nLa capacidad maxima de las Bolsas se ha cambiado exitosamente de: \"%d\" a: \"%d\"\n", 
																												aux, maxPesoBolsa);
					}
					break;
			case 10: config = FALSE;
					break;
			default: printf("\nOpcion Invalida. Elija una opcion valida del menu.\n");
		}
	}
}
