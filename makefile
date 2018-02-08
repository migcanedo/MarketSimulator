CC = gcc
Structures = LinkedList.o Pila.o Cola.o

mercado: mercado.o $(Structures)
	$(CC) -o mercado mercado.o $(Structures)
mercado.o: mercado.c LinkedList.h Cola.h Pila.h mercado.h 
	$(CC) -c mercado.c
LinkedList.o: LinkedList.c LinkedList.h
	$(CC) -c LinkedList.c
Pila.o: Pila.c Pila.h Pila.h
	$(CC) -c Pila.c
Cola.o: Cola.c Cola.h Cola.h
	$(CC) -c Cola.c
clean: 
	rm mercado *.o