#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>

#define WEB 100
#define MOVIL 200
#define TAQ 300

#define ITEMS 100
#define CAPACIDAD 50 
#define ENTRADAS 25 
#define SALIDAS 25 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t entra = PTHREAD_COND_INITIALIZER;
pthread_cond_t sale = PTHREAD_COND_INITIALIZER;

void * entra_persona(void *);
void * sale_persona(void *);

int in = 0, out = 0, count = 0, entradas = 0, salidas = 0;
int buffer[CAPACIDAD];

int main(int argc, char **argv){

	pthread_t hilos[ENTRADAS+SALIDAS];
	int resultado, i, nh;
	nh = ENTRADAS + SALIDAS;

	for (i = 0; i<ENTRADAS; ++i){
		resultado = pthread_create(&hilos[i], NULL, entra_persona, (void *) i);
		if (resultado)
			printf("Error al crear el hilo de entrar_persona.\n");

	}

	for (i = 0; i < SALIDAS; ++i){
		resultado = pthread_create(&hilos[ENTRADAS+i], NULL, sale_persona, (void *)i);
		if (resultado)
			printf("Error al crear el hilo sale_persona.\n");
	}

	for (i = 0; i < ENTRADAS+SALIDAS; ++i){
		resultado = pthread_join(hilos[i], NULL);
		if (resultado)
			printf("Error al adjuntar el hilo %d.\n", i);
	}

	pthread_exit(NULL);

	return 0;
}

void *entra_persona(void * arg){

	int i, items[ITEMS];
	int id = (int) arg;

	printf("+++ El usuario %d entra al sitio Web\n", id);
	/*for (i = 0; i < ITEMS; ++i)
		items[i] = i;*/

	for (i = 0; i < ITEMS; ++i){
		
		pthread_mutex_lock(&mutex);
		sleep(rand()%3);
		
		if (count < CAPACIDAD){ 
			
			buffer[in] = items[i];
			//printf("+++ Ingresó una persona a la sala %d\n", /*buffer[in]*/ id);
			printf("+++ Ingresó una persona a la sala %d\n", id);
			
			++in;

			in %= CAPACIDAD;

			++count;
			++entradas;
			if (count == 1) pthread_cond_broadcast(&sale);

		} else {
			printf("------------El sitio web esta en espera de resultados de la sala %d ------------\n", id);
			pthread_cond_wait(&entra, &mutex);
			printf("------------El sitio web ya esta disponible para nuevas compras de la sala------------\n");
		}
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

void *sale_persona(void * arg){
	int i;
	int id = (int) arg;

	printf("--- Termina la funcion en la sala número %d\n", id);

	for (i = 0; i < ITEMS; ++i){
		sleep(rand()%3);
		pthread_mutex_lock(&mutex);
		
		if (count > 0){ //ya existen lugares disponibles en la sala
		
			printf("--- Salió una persona por la sala %d \n", id);
			++out;
			out %= CAPACIDAD;
			--count;
			++salidas;
			
			if (count == (CAPACIDAD-1)) pthread_cond_broadcast(&entra);
			
		} else {
			printf("------------Sitio Web resolviendo peticion de la sala %d para nuevas compras------------\n", id);
			pthread_cond_wait(&sale, &mutex);
			printf("------------Sitio Web resolvio la peticion de la sala %d, lista para nuevas compras------------\n", id);
		}

		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}