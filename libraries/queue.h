#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Nodo {
    pid_t value;
    struct Nodo *siguiente;
} Nodo;

typedef struct Queue {
    struct Nodo *inicio;
    int i;
} Queue;

Queue* initQueue();

void enQueue( Queue *myQueue, pid_t element );
pid_t deQueue( Queue *myQueue );
void showElements( Queue *myQueue );
int isEmpty( Queue *myQueue );

#endif