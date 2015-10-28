#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define ENANOS 7
#define SILLAS 4


void * enano (void *);
void * blancanieves (void *);

pthread_mutex_t silla[SILLAS];
int sillas[SILLAS]={0,0,0,0};

sem_t come;
sem_t lleno;
sem_t vacio;

int checasilla();
 
int main(int argc, char** argv) {


    pthread_t en[ENANOS];
    pthread_t bn;
    int i;

    sem_init(&vacio, 0, SILLAS);
    sem_init(&lleno, 0,0);
    sem_init(&come, 0,0);

    printf("Creando Blancanieves \n");
    pthread_create(&bn,NULL,blancanieves,NULL);

    for(i=0;i<ENANOS;++i){

         printf("Creando al enano: %d \n",i);
         pthread_create(&en[i],NULL,enano,(void*)i);

    }

    for(i=0;i<ENANOS;++i){

        pthread_join(en[i],NULL);
    }

    pthread_join(bn,NULL);


    sem_destroy(&vacio);
    sem_destroy(&lleno);
    sem_destroy(&come);
    pthread_exit(NULL);

    return (EXIT_SUCCESS);
}

void * enano (void * tid){


    int id;
    id= (int)tid;

    while(1){

        sem_wait(&lleno);
        int i;
        int uno, dos, tres, cuatro;
    
        int libre= checasilla();
    
        if(libre == 5){
    
            printf("Ninguna silla esta vacia\n");
        }else{
            
            pthread_mutex_lock(&silla[libre]);
            printf("Enano %d sentado en silla %d, esperando comer\n",tid,libre);
            sem_wait(&come);
    
            printf("Enano %d comiendo\n",tid);
            sillas[libre]=1;
            sleep(8);
    
            printf("Enano %d termino, dejando silla\n",tid);
            sillas[libre]=0;
    
            sem_post(&vacio);
            pthread_mutex_unlock(&silla[libre]);
        }

    }

}

void * blancanieves (void * tid){

    int valor;
    printf("Soy blancanieves\n");

    while(1){

        sem_wait(&vacio);
        sleep(4);
        sem_post(&come);
        sem_post(&lleno);
        sem_getvalue(&vacio,&valor);
        if (valor == 0 ) printf("Sillas llenas, esperar a que terminen\n");
        if(valor == 4) printf("Nadie sentado, me voy de paseo\n");

    }
}

int checasilla(){

    int i;

    for(i=0;i<SILLAS;++i){
        
        if(sillas[i] != 1) return i;
    }

    return 5;
}