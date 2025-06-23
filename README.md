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

### La cena de los filosofos.


```Bash
    sudo chmod 755 ./run_cena_f.sh
    ./run_cena_f.sh
```

### El problema del barbero.

```Bash
    sudo chmod 755 ./run_barbero.sh
    ./run_barbero.sh
```

### Extra.

Un proceso que cree un proceso hijo, el padre deberá imprimir su pid y un contador que empiece en 1 y vaya incrementando hasta que llegue a 30 con un tiempo de 2 segundos entecada impresión. El hijo igual deberá imprimir su pid y un contador que empiece en 1 y vaya incrementando hasta que llegue a 50 con un tiempo de 1 segundos entre cada impresión.

```Bash
    sudo chmod 755 ./run_extra.sh
    ./run_barbero.sh
```