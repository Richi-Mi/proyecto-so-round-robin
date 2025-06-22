#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "./../libraries/sharedMemory.h"

#define N_CLIENTS 10
#define NUM_SILLAS 3

SharedMemory *memory = NULL;

sem_t clientes;
sem_t barbero;
// Semaforo usado para manejar acceso a 'esperando'
pthread_mutex_t mutex;

int esperando = 0;

void* funcion_barbero(void* arg) {
    do {
        // Espera a que haya al menos un cliente, si no el barbero se va a dormir
        sem_wait(&clientes);

        pthread_mutex_lock(&mutex);
        
        esperando--; // Atiende a un cliente.
        printf(" * B: Barbero empieza a cortar. \n * * B: Clientes esperando: %d\n", esperando);

        pthread_mutex_unlock(&mutex);

        sem_post(&barbero); // Señala al cliente que ya puede ser atendido

        // Simula tiempo de espera en el cliente.
        sleep(2);
        printf(" * B: Barbero termino de atender al cliente. \n");
    } while(1);
}

void* funcion_cliente(void* arg) {
    int id = *( int *) arg;
    pthread_mutex_lock(&mutex);
    if (esperando < NUM_SILLAS) {
        esperando++;
        printf("C[%d]: Cliente entra y espera. Clientes esperando: %d\n", id, esperando);
        // Notifica al barbero que hay un cliente
        sem_post(&clientes);  
        pthread_mutex_unlock(&mutex);

        // Espera a que el barbero esté listo.
        sem_wait(&barbero);   
        printf("C[%d]: Cliente se está cortando el cabello\n", id);
    } else {
        pthread_mutex_unlock(&mutex);
        printf("C[%d]: Cliente se fue (sin sillas disponibles)\n", id);
    }
    return NULL;
}

int main() {
    memory = init();

    sendMyPID( memory, getpid() );

    pthread_t th_barbero;
    pthread_t th_clientes[N_CLIENTS];
    int th_clientes_id[N_CLIENTS];

    sem_init(&clientes, 0, 0);
    sem_init(&barbero, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&th_barbero, NULL, funcion_barbero, NULL);

    for (int i = 0; i < N_CLIENTS; i++) {
        // Simula que los clientes llegan en distintos tiempos.
        sleep(rand() % 4); 
        th_clientes_id[i] = i + 1;
        pthread_create(&th_clientes[i], NULL, funcion_cliente, &th_clientes_id[i]);
    }

    for (int i = 0; i < N_CLIENTS; i++) {
        pthread_join(th_clientes[i], NULL);
    }
    sem_destroy(&clientes);
    sem_destroy(&barbero);
    pthread_mutex_destroy(&mutex);

    finish( memory );

    return 0;
}
