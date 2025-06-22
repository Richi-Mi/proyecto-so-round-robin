#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <semaphore.h>
#include <pthread.h>

#define NF 5 

#define HAMBRIENTO 0 
#define COMIENDO 1
#define PENSANDO 2

#include "./../libraries/sharedMemory.h"

/**
 * * La cena de los filosofos.
 * @author Mendoza Castañeda José Ricardo.
 */

SharedMemory *memory = NULL;

sem_t sfilo[5];
sem_t sedo; 
int edo_filo[NF]; 

void pensar(){
    sleep(3); 
}
void comer(){  
    sleep(3); 
}

int tenedorIzq(int idF){
    if(idF==0)//no esta ocupado 
        return NF-1; 
    else 
        return idF-1; 
}
int tenedorDer(int idF){ 
    if(idF == (NF-1))
        return 0; 
    else 
        return idF+1; 
}
void tenedoresDisponible(int idF){
    int izq, der; 
    
    izq = tenedorIzq(idF); 
    der = tenedorDer(idF); 
    
    // Comprueba que ninguno de los filoso d alado esten comiendo ocupando tenedor
    if(edo_filo[idF]==HAMBRIENTO && edo_filo[izq]!=COMIENDO&& edo_filo[der]!=COMIENDO){ 
        edo_filo[idF]=COMIENDO; 
        printf("\nfilosofo %i estoy comiendo", idF); 
        sem_post(&sfilo[idF]); //up desbloquea el sem incrmentando su valor en 1 //deja los tenedores
    }
}
void tomarTenedor(int idF){//recurso compartido 

    sem_wait(&sedo); //down
    edo_filo[idF]=HAMBRIENTO;
    printf("\nfilosofo %i tengo hambre, intentare comer(tomar tenedor)\n", idF); 
    tenedoresDisponible(idF); 
    sem_post(&sedo); //up 
    sem_wait(&sfilo[idF]);//down 

}
void dejarTenerdor(int idF){
    int izq, der; 
    izq=tenedorIzq(idF); 
    der=tenedorDer(idF);
    sem_wait(&sedo); //bloqueo dow sem_edos 
    edo_filo[idF]=PENSANDO; 
    printf("\nfilosofo %d estoy pensando \n", idF); 
    tenedoresDisponible(izq); 
    tenedoresDisponible(der); 
    sem_post(&sedo); // up sem_edo 
}
void *filosofo(void *idF){
    int idFilo=*(int *)idF; 
    while(1){
        pensar(); 
        tomarTenedor(idFilo); 
        comer(); 
        dejarTenerdor(idFilo); 
    }
}

int main(){
    memory = init();
    sendMyPID( memory, getpid() );

    int id[NF]={0,1,2,3,4}; 
    int i; 

    pthread_t filosofos[NF];
    sem_init(&sedo, 0, 1); 

    for(i=0; i<NF; i++)
        sem_init(&sfilo[i], 0,0); 
    for(i=0; i<NF; i++)
        pthread_create(&filosofos[i], NULL, filosofo, &id[i]); 
    for(i=0; i<NF; i++)
        pthread_join(filosofos[i], NULL); 
    
    finish( memory );
    return 0; 
}