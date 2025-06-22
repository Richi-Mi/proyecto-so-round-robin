#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#define N_PROCESOS 3

#include "./../libraries/sharedMemory.h"

int I = 0;
SharedMemory *memory = NULL;

void cod_del_proceso( int id, int t ) {
    sendMyPID( memory, getpid() );

    sleep( 5 ); // Simulación de un proceso.
    
    finish( memory );
    exit(t);
}

int main() {
    int i;

    pid_t pid;
    int p, edo;

    memory = init();    
    for( p = 0; p < N_PROCESOS; p++ ) {
        pid = fork();
        if( pid == -1 ) {
            perror("error a la llamada a fork");
            exit(-1);
        }   
        else if( pid == 0 )
            cod_del_proceso( getpid(), p+1 );
    }

    for( p = 0; p < N_PROCESOS; p++ ) {
        pid = wait( &edo );
        printf("Termino el proceso %d con edo %x. \n", pid, edo >> 8 );
    }

    exit(0);

    return 0;
}