#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <stdbool.h>

#include "./libraries/sharedMemory.h"
#include "./libraries/queue.h"

SharedMemory *memory = NULL;
Queue *myQueue       = NULL;
int quantum          = 0;
pid_t currentPID     = 0;

void stopProcess( pid_t pid ) {
    kill( pid, SIGSTOP );
}
void startProcess( pid_t pid ) {
    kill( pid, SIGCONT );
}

void onEnQueueProcess() {
    // Add the procces PID to the queue
    pid_t pidAct = memory->myPID;
    enQueue(myQueue, pidAct);
    showElements( myQueue );
}

void onTestFinish() {
    printf(" * Planificador terminado con exito. \n");
    destroy();
    exit(0);
}

int main(int a, char *argv[]) {
    if( !isnumber(argv[1][0]) ) {
        perror("Ingrese un quantum valido");
        exit(1);
    }
    quantum = atoi( argv[1] );

    signal(SIGUSR1, &onEnQueueProcess );
    signal(SIGINT,  &onTestFinish );

    memory = init();
    memory -> planificador = getpid();

    myQueue = initQueue();
    
    printf(" * ---------------------------- * \n");
    printf(" * -------- Round Robin ------- * \n");
    printf(" * ---------------------------- * \n\n");

    printf(" * Quantum de %d segundos. \n", quantum);
    printf(" * My PID es: %d \n", getpid() );

    do {
        if( isEmpty(myQueue) ) {
            printf("Esperando procesos... \n");
            pause();
        }
        else {
            pid_t pidDq = deQueue(myQueue);
            showElements( myQueue );
            
            startProcess( pidDq );
        }

    } while(1);

    return 0;
}