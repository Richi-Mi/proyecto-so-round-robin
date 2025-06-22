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

SharedMemory* init() {
    sm_key = ftok("/bin/ls", 10);
    // Create or search the shared memory.
    shmg = shmget( sm_key, sizeof(SharedMemory), IPC_CREAT | 0666 );
    if( shmg == -1 ) 
        return NULL;
    
    // We entry for read and write
    SharedMemory *memory = shmat( shmg, 0, 0 );
    return memory;
}
void destroy() {
    shmctl(shmg, IPC_RMID, 0);
}
void onStartProcess() {
    printf("\n > PID desencolado. %d \n", getpid() );
}
void sendMyPID( SharedMemory *memory, pid_t my_pid ) {
    signal( SIGCONT, &onStartProcess );
    memory -> myPID = my_pid;
    kill( memory->planificador, SIGUSR1 );
    // We Stop our process.
    printf("\n > PID encolado. %d \n", my_pid );
    pause();
}