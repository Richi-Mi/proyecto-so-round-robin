#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> // Para wait()

#include "./../libraries/sharedMemory.h"

SharedMemory *memory = NULL;

int main() {
    memory = init();
    pid_t pid1, pid2;

    pid1 = fork(); // Crear primer hijo

    if (pid1 == -1) {
        perror("Error al crear el primer hijo");
        exit(1);
    }

    if (pid1 == 0) {
        sendMyPID( memory, getpid() );
        // Proceso hijo 1
        for (int i = 1; i <= 50; i++) {
            printf("Hijo 1 PID: %d, Contador: %d\n", getpid(), i);
            sleep(1);
        }
        finish( memory );
        exit(0);
    } else {
        pid2 = fork(); // Crear segundo hijo

        if (pid2 == -1) {
            perror("Error al crear el segundo hijo");
            exit(1);
        }

        if (pid2 == 0) {
            sendMyPID( memory, getpid() );
            // Proceso hijo 2
            for (int i = 1; i <= 50; i++) {
                printf("Hijo 2 PID: %d, Contador: %d\n", getpid(), i);
                sleep(1);
            }
            finish( memory );
            exit(0);
        } else {
            sendMyPID( memory, getpid() );
            // Proceso padre
            for (int i = 1; i <= 30; i++) {
                printf("Padre PID: %d, Contador: %d\n", getpid(), i);
                sleep(2);
            }

            // Esperar a los dos hijos
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

            finish( memory );

            printf("El padre ha esperado a que ambos hijos terminen.\n");
        }
    }

    return 0;
}