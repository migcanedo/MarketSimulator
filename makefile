CC = gcc
Structures = LinkedList.o Pila.o Cola.o

mercado: mercado.o $(Structures)
	$(CC) -o mercado mercado.o $(Structures)

mercado.o: mercado.c mercado.h
	$(CC) -c mercado.c

LinkedList.o: LikedList.c mercado.h
	$(CC) -c LinkedList.c

Pila.o: Pila.c mercado.h
	$(CC) -c Pila.c

Cola.o: Cola.c mercado.h
	$(CC) -c Cola.c

clean: 
	rm mercado \
		mercado.o LinkedList.o Pila.o Cola.o