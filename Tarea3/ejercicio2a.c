/*
*	Ejercicio 2
*	Segmentos de Memoria Compartida
*	Escribe
*
*	José Luis García Reymundo
* 	A01063645
*/


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define SHMSZ 1024
#define KEY 1000

int main(){
	int shmid;
	char *shm, *s, tmp;
	
	if ((shmid = shmget(KEY, SHMSZ, 0666)) < 0) {
		perror("shmget");
		return 1;
	}
	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
		perror("shmat");
		return 1;
	}
	memset(shm,0,SHMSZ);
	s = shm;
	
	printf("Ingrese el número (-1 para salir):\n");
	while (*shm != -1) scanf(" %d", shm);
 
	if(shmdt(shm) != 0)
		fprintf(stderr, "No se pudo cerrar Segmento de Memoria.\n");
 
	return 0;
}
