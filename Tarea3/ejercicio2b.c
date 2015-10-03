/*
*	Ejercicio 2
*	Segmentos de Memoria Compartida
*	Calcula
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

int fact(int );
 
int main(){
	char c, tmp;
	int shmid;
	char *shm, *s;	
	
	if ((shmid = shmget(KEY, SHMSZ, IPC_CREAT | 0666)) < 0) {
		perror("shmget");
		return 1;
	}
	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
		perror("shmat");
		return 1;
	}
	memset(shm,0,SHMSZ);
	s = shm;
	
	printf("Aquí puedes ver el resultado:\n");
	while (*shm != -1){
		sleep(1);
		if(tmp == *shm)
			continue;
		fprintf(stdout, "Factorial (%d) = %d\n",*shm, fact(*shm));
		tmp = *shm;
	}
	
	if(shmdt(shm) != 0)
		fprintf(stderr, "No se pudo cerrar Segmento de Memoria.\n");
		
	return 0;
}

int fact(int n){
    int a = 1;
    int i;
    for(i = 2; i<=n;++i) a*=i;
    return a;
}