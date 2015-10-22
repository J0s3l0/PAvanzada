#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define NFUM 3 
#define TABACO 0
#define PAPEL 1
#define FOS 2 

pthread_mutex_t mesa = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_fumar, sem_vacio, sem_fumando;

void * agente(void *);
void * fumador(void *);
void fumar(int comp);
void setcomp();
int getcomp();

int comp[2];

int main(int argc, char** argv) {
    
    int i;
    
    //incializacion de semaforos
    sem_init(&sem_vacio, 0, 0);
    sem_init(&sem_fumar, 0, 0);
    sem_init(&sem_fumando, 0, 0);
    
    pthread_t tid; //agente
    pthread_t tids[NFUM]; //fumadores
    
    //creacion de threads
    pthread_create(&tid, NULL, agente, NULL);
    
    for(i=0; i<NFUM; ++i)
        pthread_create(&tids[i], NULL, fumador, (void *)i);
    
    pthread_join(tid, NULL);
    
    for(i=0; i<NFUM; ++i)
        pthread_join(tids[i], NULL);

    sem_destroy(&sem_vacio);
    sem_destroy(&sem_fumar);
    sem_destroy(&sem_fumando);
    
    return (EXIT_SUCCESS);
}

void * agente(void * args){
    
    while(1){
        pthread_mutex_lock(&mesa);
        setcomp();
        pthread_mutex_unlock(&mesa);
        sem_post(&sem_fumar);
        sem_wait(&sem_fumando);
        sem_wait(&sem_vacio); 
    }
    
}

void * fumador(void * args){
    
    int id = (int)args;
    int componente;
    switch(id){
         case TABACO: printf("Fumador %d, tengo el tabaco\n",id); break;
         case PAPEL: printf("Fumador %d, tengo el papel\n",id); break;
         case FOS: printf("Fumador %d, tengo los fosforos\n",id); break;
    }
    
    while(1){
        sem_wait(&sem_fumar);
        pthread_mutex_lock(&mesa);
        componente=getcomp();
        if(componente==id){
                fumar(componente);
                sem_post(&sem_fumando);
        }
        else{
            sem_post(&sem_fumar);
        }
        pthread_mutex_unlock(&mesa);
        sem_post(&sem_vacio);
    }
    
}

void fumar(int comp){
    
    switch(comp){
        case TABACO: printf("\nAgente ofrece papel y fosforos.\n Fumador 0 Fumando \n"); sleep(2); break;
        case PAPEL: printf("\nAgente ofrece tabaco y fosforos.\n Fumador 1 Fumando \n"); sleep(2); break;
        case FOS: printf("\nAgente ofrece tabaco y papel.\n Fumador 2 Fumando \n"); sleep(2); break;
    }
}

void setcomp(){  
    
    int opc = rand()%3;
    
    switch(opc){
        case 0: comp[0]=0; comp[1]=1; break; 
        case 1: comp[0]=1; comp[1]=2; break;
        case 2: comp[0]=2; comp[1]=0; break;
    }
}

int getcomp(){
    
    if(comp[0]!=TABACO && comp[1]!=TABACO)
        return TABACO;
    else if(comp[0]!=PAPEL && comp[1]!=PAPEL)
        return PAPEL;
    else if(comp[0]!=FOS && comp[1]!=FOS)
        return FOS;
}