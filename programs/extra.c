#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> // Para wait()

#include "./../libraries/sharedMemory.h"

SharedMemory *memory = NULL;

int main() {
    pid_t pid_c;
    memory = init();

    pid_c = fork(); // Crear primer hijo

    if (pid_c == -1) {
        perror("Error al crear el primer hijo");
        exit(1);
    }

    if (pid_c == 0) {
        sendMyPID( memory, getpid() );
        // Proceso hijo 1
        for (int i = 1; i <= 50; i++) {
            printf("Hijo PID: %d, Contador: %d\n", getpid(), i);
            sleep(1);
        }
        finish( memory );
        exit(0);
    } else {
        sendMyPID( memory, getpid() );
        for (int i = 1; i <= 30; i++) {
            printf("Padre PID: %d, Contador: %d\n", getpid(), i);
            sleep(2);
        }
        // Proceso padre.
        waitpid(pid_c, NULL, 0);
        finish( memory );
    }
    return 0;
}