#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mercado.h"

typedef int bool;

// Variables Globales

int modalidad = 1; // 1 := Interactiva || 0 := Automatica
int nCarritos = 3;
int maxProductos = 30; 
int maxPesoBanda = 200; 
float velCajera = 1.0;
float velEmbolsador = 4;
int tFacturacion = 130;
int maxPesoAreaEmbolsado = 150;
int maxPesoBolsa = 120;

char *nombreArch;

/*
Funcion main del Programa de MarketSimulator.
*/
int main(int argc, char* argv[]){
	int opc;
	if (argc < 2){
		printf("\nError. Debe indicar el nombre del archivo donde se encuentra el Inventario.\n\n");
		exit(1);
	}
	
	
	LinkedList * inventario = crearInventario(argv[1]);
	nombreArch = argv[1];


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
			case 3:
				exit(0);
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
Funcion que se encarga de ejecutar la simulacion del mercado, con el Inventario que se le pasa por argumento y
utilizando la configuracion global del programa.
*/
void simulacion(LinkedList *inventario){

	FILE *logfile = fopen ("ArchivoDeRegistro.log", "a");
	fprintf(logfile, "Archivo: %s Cantidad carritos: %d ", nombreArch, nCarritos);

	srand(time(NULL));
	
	// Estructuras a utilizar durante la simulacion.
	LinkedList * carritos[nCarritos];
	Cola * banda = crearCola();
	Pila * areaEmb = crearPila();
	Pila * bolsas[maxProductos+1]; // Arreglo de Bolsas que en el peor de los casos habria tantas bolsas como productos en el carrito.
								 // Donde la posicion 0 es donde se guardaran los productos que no quepan en bolsas.


	// Variables locales a usar durante la simulacion.
	int tCliente = 0; // Tiempo que toma el cliente en terminar sus compras
	float complejidadAct = 0; // Variable auxiliar para evaluar el tiempo que toma procesar un producto
	int pesoBanda; // Variable auxiliar para tomar en cuenta la limitacion de la banda
	int facturado = FALSE;	// Variable que muestra si ya el cliente esta siendo facturado o no 
	int operacion = 0; // Instantes que se han recorrido
	int pesoBolsaAct;	// Varibale que sirve para llevar la cuenta de la capcidad de la bolsa
	float tiempoEmbolsadorAct = 0; // Inicio del proceso de embolsado
	int bolsaAct = 1; // Posicion de la bolsas que se esta llenando actualemente en el arreglo bolsas.
	int tiempoVaciarAreaEmb = 0; // Tiempo que se tarda en vaciar el AreaEmb luego de empezar a facturar.
	int tTotal = 0; // Tiempo total de procesar a todos los clientes.

	if (modalidad) printf("\n=========  CARRITOS CREADOS  =========\n");
	int i, j, cantProd, p, ite;
	for(i = 0; i < nCarritos; i++){
		carritos[i] = crearLista();
		cantProd = rand() % maxProductos + 1;
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
		if(modalidad){
			printf("\n======  CARRITO %d  ======\n", i+1);
			fprintf(logfile, "Productos carrito %d: %d ", i+1, carritos[i]->cant);
			imprimirLista(carritos[i]);
		}
	}

	fprintf(logfile, "Capacidad banda: %d Velocidad cajera: %f ", maxPesoBanda, velCajera);
	fprintf(logfile, "Velocidad embolsador: %f Tiempo de facturacion: %d ", velEmbolsador, tFacturacion);
	fprintf(logfile, "Capacidad area de embolsado: %d Capacidad de bolsa: %d ",  maxPesoAreaEmbolsado, maxPesoBolsa);

	printf("\n==================  INICIO DE SIMULACION  ==================\n");

	//Ciclo que procesa a los clientes uno a uno (se empieza a procesar despues de que el cliente anterior haya sido facturado)
	Producto *prodBanda;
	Producto *prodPila;
	Producto *prodBolsa;

	pesoBanda = maxPesoBanda;
	pesoBolsaAct = maxPesoBolsa;
	tiempoEmbolsadorAct = 1;
	bolsas[bolsaAct] = crearPila();
	bolsas[0] = NULL;
	for(i = 0; i < nCarritos; i++){
		if(modalidad){
			printf("\n================  CARRITO NUMERO %d  ================\n", i+1);
			printf("=================  INSTANTE %d  =================\n", operacion+1);
		}

		while(carritos[i]->head->prod->peso <= pesoBanda){
			prodBanda = eliminarElem(carritos[i]);
			agregarCola(banda, prodBanda);
			pesoBanda = pesoBanda - prodBanda->peso;
		}
		complejidadAct = prodBanda->complejidad;
		if(modalidad) imprimirDatos(carritos[i], banda, areaEmb, bolsas, bolsaAct);
		++operacion;
		int t = 0;
		
		if(modalidad){
			printf("================================================\n");	
			printf("Presione enter para pasar al siguiente instante...");
			while(getchar() != '\n');
		}

		//ciclo en el que cada iteracion representa un instante de tiempo (como si el enter fuera presionado automaticamente)
		while(!facturado || areaEmb->cant > 0){
			if(modalidad) printf("\n=================  INSTANTE %d  =================\n", operacion+1);
			complejidadAct = complejidadAct - velCajera;
			//comprueba si hay espacio en la banda y saca producto del carrito hacia la banda
			if(carritos[i]->cant > 0 && carritos[i]->head->prod->peso <= pesoBanda){
				prodBanda = eliminarElem(carritos[i]);
				agregarCola(banda, prodBanda);
				pesoBanda = pesoBanda - prodBanda->peso;
			}
			else if (carritos[i]->cant > 0 && carritos[i]->head->prod->peso > pesoBanda && pesoBanda == maxPesoBanda){
				prodBanda = eliminarElem(carritos[i]);
				agregarCola(banda, prodBanda);
				pesoBanda = 0;
			}
			//comprueba si el tiempo de procesamiento del primer objeto de la banda ya paso y cantinua con el siguiente objeto
			if(complejidadAct <= 0 && !facturado){
				prodPila = quitarCola(banda);
				if(prodPila->peso > maxPesoBanda){
					pesoBanda = maxPesoBanda;
				}
				else{
					pesoBanda = pesoBanda + prodPila->peso;
				}
				if(carritos[i]->cant == 0 && banda->cant == 0){
					facturado = TRUE;
				}
				else{
					if(banda->head == NULL){
						printf("ESTO ERAAAAAA\n");
					}
					else{
						complejidadAct = banda->head->prod->complejidad - complejidadAct;
					}
				}
				agregarPila(areaEmb, prodPila);
			}
			//comprueba si hay espacio en la banda y saca producto del carrito hacia la banda
			if(carritos[i]->cant > 0 && carritos[i]->head->prod->peso <= pesoBanda){
				prodBanda = eliminarElem(carritos[i]);
				agregarCola(banda, prodBanda);
				pesoBanda = pesoBanda - prodBanda->peso;
			}
			else if (carritos[i]->cant > 0 && carritos[i]->head->prod->peso > pesoBanda && pesoBanda == maxPesoBanda){
				prodBanda = eliminarElem(carritos[i]);
				agregarCola(banda, prodBanda);
				pesoBanda = 0;
			}

			// Comprueba si hay productos en el AreaEmb y si ha pasado el tiempo de abrir una bolsa.
			if (areaEmb->cant > 0 && tiempoEmbolsadorAct >= velEmbolsador){

				// Si el producto del AreaEmb es mayor que el peso q soporta una bolsa, se procesa de inmediato
				// y se guarda en una 'bolsa' especial para ellos.
				if (areaEmb->head->prod->peso > maxPesoBolsa){
					if (bolsas[0] == NULL) bolsas[0] = crearPila();
					prodBolsa = quitarPila(areaEmb);
					agregarPila(bolsas[0], prodBolsa);
				}
				// Si el producto antual entra en la bolsa, se guarda en ella.
				else if(areaEmb->head->prod->peso <= pesoBolsaAct){
				 	prodBolsa = quitarPila(areaEmb);
				 	agregarPila(bolsas[bolsaAct], prodBolsa);
				 	pesoBolsaAct -= prodBolsa->peso;
				}
				// Si el producto actual no entra en la bolsa, se crea la siguiente bolsa y se reinicia
				// el tiempo de abrir una bolsa.
				else{
				 	pesoBolsaAct = maxPesoBolsa;
				 	bolsaAct++;
				 	bolsas[bolsaAct] = crearPila();
				 	tiempoEmbolsadorAct = 1; // Se reinicia a 1 porq ya considero este instante actual como que ya estoy abriendo la bosla.
				}
			}

			++operacion;
			
			// Si el tiempo de abrir una bolsa aun no ha pasado, se le suma un seg
			if(tiempoEmbolsadorAct < velEmbolsador) tiempoEmbolsadorAct++;

			// Si ya esta facturado la cajera pero aun hay productos en el area de embolsado,
			// sumamos cuantos instantes toma vaciar el AreaEmb para luego restarselo al tiempo de 
			// facturado que se vaya a sumar.
			if(facturado) tiempoVaciarAreaEmb++;

			++t;
			if(modalidad){ 
				imprimirDatos(carritos[i], banda, areaEmb, bolsas, bolsaAct);
				printf("================================================\n\n");
				printf("Presione enter para pasar al siguiente instante...");
				while(getchar() != '\n');
			}
		}
		// Termina de procesar a un cliente y se calcula su tiempo de ser atendido.

		// Aqui preguntamos si el tiempo de facturacion es mayor o igual al tiempo qu tomo terminar de vaciar el AreaEmb.
		// En caso de q sea afirmativo se suma la diferencia de ambos, en caso contrario se suma solo el tiempo que tomo
		// vaciar el AreaEmb.
		tCliente = operacion + (tFacturacion >= tiempoVaciarAreaEmb ? tFacturacion - tiempoVaciarAreaEmb : tiempoVaciarAreaEmb);
		printf("\n\n============  CLIENTE NUMERO %d TARDO %dseg EN SER FACTURADO  ===========\n\n", i+1, tCliente);

		fprintf(logfile, "Tiempo cliente numero %d: %d ", i+1, tCliente);
		tTotal += tCliente;

		// Se reinician las variables, se elimina el carrito actual y se vacian las bolsas para volverlas a usar.
		operacion = 0;
		bolsaAct = 1;
		tiempoVaciarAreaEmb = 0;
		pesoBolsaAct = maxPesoBolsa;
		facturado = FALSE;

		for(j=0; j <= bolsaAct; j++){
			if (bolsas[j] != NULL) vaciarPila(bolsas[j]);
		}
		bolsas[0] = NULL;	
		eliminarLista(carritos[i]);
	}
	printf("\n\n=======  TIEMPO TOTAL: %dseg  ======\n\n", tTotal);	
	fprintf(logfile, "Tiempo total: %d \n", tTotal);
	fclose(logfile);
	
	free(banda);
	free(areaEmb);
}

/*
Funcion que se encarga de imprimir en pantalla de forma ordenada los elementos que pertenecen 
a una Lista Enlazada, una Cola, una Pila y un Arreglo de Pilas de tama;o 'cantBolsas'.
*/
void imprimirDatos(LinkedList *lista, Cola *cola, Pila *pila, Pila *bolsas[], int cantBolsas){
	//printf("ComplejidadAct:%f\nPesoBanda:%d\n", complejidadAct, pesoBanda);
	printf("\n >>>> %d productos en el Carrito: <<<<\n", lista->cant);
	imprimirLista(lista);
	printf("\n >>>> %d productos en la Banda: <<<<\n", cola->cant);
	imprimirCola(cola);
	printf("\n >>>> %d Productos en el Area de Embolsado: <<<<\n", pila->cant);
	imprimirPila(pila);
	int i;
	for(i = 0; i <= cantBolsas; i++){
		if (i == 0 && bolsas[i] != NULL){
			printf("\n >>>> %d Productos fuera de Bolsa: <<<<\n", bolsas[i]->cant);
			imprimirPila(bolsas[i]);
		}else if (i > 0){
			printf("\n >>>> %d Productos en la Bolsa %d: <<<<\n", bolsas[i]->cant, i);
			imprimirPila(bolsas[i]);
		}
	}
}

/*
Funcion que imprime en pantalla y gestiona el menu de Cambio de configuracion del MarketSimulator.
*/
void menuConfiguracion(){
	int opc2;
	char opc3;
	int aux;
	float aux1;
	int auxEvaluador;
	float auxEvaluador1;
	bool config = TRUE;

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
		printf("\t0. Salir de menu de configuracion.\n");
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
						scanf("%d", &auxEvaluador);
						getchar();

						if(auxEvaluador < 0){
							printf("\nCantidad de Carritos no valida.\n");
							break;
						}
						nCarritos = auxEvaluador;
						
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
						scanf("%d", &auxEvaluador);
						getchar();

						if(auxEvaluador < 0){
							printf("\nCantidad Maxima de Productos por Carritos no valida.\n");
							break;
						}
						maxProductos = auxEvaluador;
						
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
						scanf("%d", &auxEvaluador);
						getchar();
						
						if(auxEvaluador < 0){
							printf("\nCapacidad de la Banda no valida.\n");
							break;
						}
						maxPesoBanda = auxEvaluador;

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
						scanf("%f", &auxEvaluador1);
						getchar();

						if(auxEvaluador1 < 0){
							printf("\nVelocidad de Cajera no valida.\n");
							break;
						}
						velCajera = auxEvaluador1;
						
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
						scanf("%f", &auxEvaluador1);
						getchar();

						if(auxEvaluador1 < 0){
							printf("\nVelocidad de Embolsador no valida.\n");
							break;
						}
						velEmbolsador = auxEvaluador1;
						
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
						scanf("%d", &auxEvaluador);
						getchar();
						
						if(auxEvaluador < 0){
							printf("\nTiempo de Facturacion no valido.\n");
							break;
						}
						tFacturacion = auxEvaluador;

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
						scanf("%d", &auxEvaluador);
						getchar();

						if(auxEvaluador < 0){
							printf("\nCapacidad de Area de Embolsado no valida.\n");
							break;
						}
						maxPesoAreaEmbolsado = auxEvaluador;
						
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
						scanf("%d", &auxEvaluador);
						getchar();
						
						if(auxEvaluador < 0){
							printf("\nCapacidad de Bolsas no valida.\n");
							break;
						}
						maxPesoBolsa = auxEvaluador;

						printf("\nLa capacidad maxima de las Bolsas se ha cambiado exitosamente de: \"%dcc\" a: \"%dcc\"\n", 
																												aux, maxPesoBolsa);
					}
					break;
			case 0: config = FALSE;
					break;
			default: printf("\nOpcion Invalida. Elija una opcion valida del menu.\n");
		}
	}
}
