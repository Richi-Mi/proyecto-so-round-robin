#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

Queue* initQueue() {
    Queue *myQueue = (Queue *) malloc( sizeof(Queue) );
    myQueue->i = 0;
    myQueue->inicio = NULL;

    return myQueue;
}
void enQueue( Queue *myQueue, pid_t element ) {
    // Creacion del nuevo nodo
    Nodo *nuevo = (Nodo *) malloc( sizeof( Nodo ) );
    nuevo -> value = element;
    // Inicia en el primer elemento
    if( myQueue -> inicio == NULL ) {
        nuevo -> siguiente = nuevo;
        myQueue -> inicio = nuevo;
    }
    // Ya hay elementos
    else {
        Nodo *aux = myQueue -> inicio;
        nuevo -> siguiente = aux -> siguiente;
        aux -> siguiente = nuevo;

        myQueue -> inicio = nuevo;
    }
    myQueue->i++;
}
pid_t deQueue( Queue *myQueue ) {
    // Nodo *elementToDeQueue = myQueue -> inicio -> siguiente;
    int element = 0;
    if( myQueue -> inicio == NULL )
        return element; // Comprobamos que no este vacia 

    // Si solo hay un elemento.
    if( myQueue -> inicio == myQueue -> inicio -> siguiente ) {
        element = myQueue -> inicio -> value;

        free( myQueue -> inicio );
        myQueue -> inicio = NULL;

        myQueue->i--;
        return element;
    }
    else {
        Nodo *aux = myQueue -> inicio -> siguiente;
        element = aux -> value;

        myQueue -> inicio -> siguiente = aux -> siguiente; 
        free( aux );

        myQueue->i--;
        return element;
    }
}
void showElements( Queue *myQueue ) {
    Nodo *aux = myQueue -> inicio;
    if( aux != NULL ) {
        printf(" * \n" );

        if ( aux -> siguiente == myQueue -> inicio ) {
            printf(" | %d |\n", myQueue -> inicio -> value );
        }
        else {         
            while ( aux -> siguiente != myQueue -> inicio ) {
                printf(" | %d | ->", aux -> value );
                aux = aux -> siguiente;

                if( aux -> siguiente == myQueue -> inicio ) {
                   printf(" | %d | -> * \n", aux -> value );
                }
            }     
        }
    }
    else {
        printf(" * Cola Vacia \n");
    }
}
int isEmpty( Queue *myQueue ) {
    if( myQueue->inicio == NULL && myQueue->i == 0)
        return 1;
    else 
        return 0;
}