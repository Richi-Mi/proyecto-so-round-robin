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
    addMyPID(memory, getpid());
    int i;
    for( i = 0; i < 5; i++ ) {
        printf("\n Proceso %d i= %d I = %d\n", id, i, I );
        I++;
    }
    exit(t);
}

int main() {
    int i;

    pid_t pid;
    int p, edo;

    memory = init();
    addMyPID(memory, getpid());
    
    for( p = 0; p < N_PROCESOS; p++ ) {
        pid = fork();
        if( pid == -1 ) {
            perror("error a la llamada a fork");
            exit(-1);
        }   
        else if( pid == 0 ) {
            cod_del_proceso( getpid(), p+1 );
        }
        else {
            printf("\n\t\tSOY EL PADRE mi PID %d PPID %d pid hijo %d", getpid(), getppid(), pid );
        }
    }

    for( p = 0; p < N_PROCESOS; p++ ) {
        pid = wait( &edo );
        printf("\nTermino el proceso %d con edo %x", pid, edo >> 8 );
    }

    exit(0);

    return 0;
}