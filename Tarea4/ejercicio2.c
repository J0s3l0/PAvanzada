#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NHILOS 6
#define MAX 10

sem_t hombre;
sem_t mujer;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int esp_hombre = 0;
int esp_mujer = 0;

void * hombre_sale(void *arg);
void * hombre_quiere_entrar(void *arg);
void * mujer_sale(void *arg);
void * mujer_quiere_entrar(void *arg);

int i = 0;

int main(int argc, char** argv[]){
	
	pthread_t tids[NHILOS];
	int result;
	
	sem_init(&hombre, 0, 0); 
	sem_init(&mujer, 0, 1); //Prioridad a las mujeres, ellas primero

	pthread_create(&tids[0], NULL, hombre_sale, NULL);
	pthread_create(&tids[1], NULL, hombre_quiere_entrar, NULL);
	pthread_create(&tids[2], NULL, mujer_sale, NULL);
	pthread_create(&tids[3], NULL, mujer_quiere_entrar, NULL);
	
	while(1);
	
	sem_destroy(&hombre);
	sem_destroy(&mujer);
	
	return 0;
}

void *hombre_sale(void *arg){	
	while(1){

		usleep(rand() % 3);

		pthread_mutex_lock(&mutex);

		if(esp_hombre > 0){
			--esp_hombre;
			printf("<= Sale un hombre\n");

			if(esp_hombre == 0) {
				printf("---Sanitario Vacio---\n");
				sem_post(&mujer);
			}
		}
      
		pthread_mutex_unlock(&mutex);
    }
}

void *hombre_quiere_entrar(void *arg){
	
	int esperan = 0;

	while(1){
		
		usleep(rand() % 3);

		printf("=> Llega un hombre (%d en espera)\n", ++esperan);

		sem_wait(&hombre); 

		pthread_mutex_lock(&mutex);
      
		int val;
		sem_getvalue(&mujer, &val);

		if(val > 0) sem_wait(&mujer); //Hacer down
	  
		++esp_hombre;
		printf("=> Entra un hombre (%d en espera)\n", --esperan);

		sem_post(&hombre); 

		pthread_mutex_unlock(&mutex);
	}
}


void *mujer_sale(void *arg){
	while(1){
		
		usleep(rand() % 3);

		pthread_mutex_lock(&mutex);
		
		if(esp_mujer > 0){
			--esp_mujer;
			printf("<= Sale una mujer\n");

			if(esp_mujer == 0){ 
				printf("---Sanitario vacio---\n");
				sem_post(&hombre);
			}
		}

		pthread_mutex_unlock(&mutex);
	}
}

void *mujer_quiere_entrar(void *arg){
	int esperan = 0;

	while(1){
		
		usleep(rand() % 3);

		printf("=> Llega una mujer (%d en espera)\n", ++esperan);

		sem_wait(&mujer); 

		pthread_mutex_lock(&mutex);

		int val;
		sem_getvalue(&hombre, &val);

		if(val > 0) sem_wait(&hombre); // Hacer down
		
		++esp_mujer;
		printf("=> Entra una mujer (%d en espera)\n", --esperan);

		sem_post(&mujer); 

		pthread_mutex_unlock(&mutex);
    }
}