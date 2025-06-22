# Algoritmo de planificación Round-Robin. 

- Es un algoritmo apropiativo.
- Se establece un valor de quantum. El planificador elige al primer proceso encolado y este se ejecuta un quantum de tiempo, si su ejecución no ha terminado se vuelve a encolar.

## Ejecución.

Primero, para cualquier simulación ejecuta el archivo `./run.sh`

```Bash
    sudo chmod 755 ./run.sh
    ./run.sh
```

### 1er Ejemplo. "Ejercicio P2"

En este programa se crean 3 procesos, y todos son 1 contador del 1 - 5, pero se detienen cada segundo.

```Bash
    sudo chmod 755 ./run_p2.sh
    ./run_p2.sh
```