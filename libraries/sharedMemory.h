#ifndef SHARED_MEM_H
#define SHARED_MEM_H

#include <unistd.h>

typedef struct SharedMemory {
    pid_t planificador;
    pid_t myPID;
    int type;
} SharedMemory;

SharedMemory* init();
void destroy();
void sendMyPID( SharedMemory *memory, pid_t my_pid );

#endif