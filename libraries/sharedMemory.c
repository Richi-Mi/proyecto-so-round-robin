#include "sharedMemory.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <stdio.h>

int shmg;
key_t sm_key;
sem_t sem_mem;

SharedMemory* init() {
    sm_key = ftok("/bin/ls", 10);
    // Create or search the shared memory.
    shmg = shmget( sm_key, sizeof(SharedMemory), IPC_CREAT | 0666 );
    if( shmg == -1 ) 
        return NULL;
    
    // We entry for read and write
    SharedMemory *memory = shmat( shmg, 0, 0 );
    sem_init( &sem_mem, 0, 1 );
    return memory;
}
void destroy() {
    shmctl(shmg, IPC_RMID, 0);
}
void onStartProcess() {
    printf(".\n");
}
void sendMyPID( SharedMemory *memory, pid_t my_pid ) {
    signal( SIGCONT, &onStartProcess );

    sem_wait( &sem_mem );
    memory -> myPID = my_pid;
    kill( memory->planificador, SIGUSR1 );
    sem_post( &sem_mem );
    // We Stop our process.
    printf("\n > PID encolado. %d \n", my_pid );
    pause();
}
void finish( SharedMemory *memory ) {
    sem_wait( &sem_mem );
    memory -> myPID = getpid();
    kill( memory->planificador, SIGUSR2 );
    sem_post( &sem_mem );
}