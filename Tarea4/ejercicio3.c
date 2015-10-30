#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <signal.h>

#define ENTRADAS 2
#define SALIDAS 2
#define LIM 10 

int contEnt[ENTRADAS];
int contSal[SALIDAS];
sem_t SemLugares;
sem_t SemRobots;
sem_t SemSalidas[SALIDAS];
sem_t SemEntradas[ENTRADAS];
sem_t critica;

void entrada(void * arg);
void salida(void * arg);
void llegaRobot(void * arg);
void saleRobot(void * arg);

int main(int argc, char** argv[]){
	int i;
	
	pthread_t thread_id[ENTRADAS + SALIDAS + 2];
	
	sem_init(&critica, 0, 1);
	
	srand(time(NULL));
	
	sem_init(&SemLugares, 0, LIM);
	sem_init(&SemRobots, 0, 0);
	
	for(i = 0; i < ENTRADAS; ++i){
		sem_init(&SemEntradas[i],0,0);
	}
	
	for(i = 0; i < SALIDAS; ++i){
		sem_init(&SemSalidas[i],0,0);
	}
	
	for(i=0;i<ENTRADAS;++i){
        pthread_create(&thread_id[i], NULL, entrada,i);
        printf("Se creó la tienda %d\n",i);
    }
	
	for(;i<(ENTRADAS + SALIDAS);++i){
        pthread_create(&thread_id[i], NULL, salida,i - ENTRADAS);
        printf("Se creó la tienda %d\n",i - ENTRADAS);
    }
	
	pthread_create(&thread_id[i], NULL, llegaRobot, NULL);
	++i;
	pthread_create(&thread_id[i], NULL, saleRobot, NULL);
	
	for(i=0;i<(ENTRADAS + SALIDAS + 2);++i){
        pthread_join(thread_id[i],NULL);
	}
	
	return 0;
}

void entrada(void * arg){
	int aux;
	int num = (int)arg;
	contEnt[num] = 0;
	while(1){

		sem_wait(&SemEntradas[num]);
		printf("La tienda %d tiene robots esperando.\n", num);
		
		sem_wait(&SemLugares);
		sem_post(&SemRobots);
		
		++contEnt[num];
		
		printf("Ya entró un robot a la tienda %d.\n", num);
		
		sem_getvalue(&SemRobots, &aux);
		printf("+++Hay un robot más en el centro comercial (Ahora hay %d robots adentro)\n", aux);
		
	}
}

void salida(void * arg){
	int num = (int)arg;
	contSal[num] = 0;
	
	while(1){
		sem_wait(&SemSalidas[num]);
		++contSal[num];
		printf("---Salió un robot por la tienda %d.", num);
	}
}

void llegaRobot(void * arg){
	int entrada;
   
	while(1){
		sleep(rand()%2);
		
		entrada = rand() % ENTRADAS;
		sem_post(&SemEntradas[entrada]);
	}
}

void saleRobot(void * arg){
	int salida;
	
	while(1){
		sleep(rand()%2);
		
		sem_wait(&SemRobots); 
		sem_post(&SemLugares);
		
		salida = rand() % ENTRADAS; 
		sem_post(&SemSalidas[salida]);
	}
}