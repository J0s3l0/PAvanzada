/*
*	Ejercicio 3
*	Semáforo
*
*	José Luis García Reymundo
* 	A01063645
*/


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>

union semaforo {
	int val;
};

void leer(int );
void escribir(int );
int factorial(int );

union semaforo s;

int main (int argc, const char * argv[]){
    pid_t pid;
    int estado;
    key_t llave;
    int idSemaforo;
    
    llave = ftok("/tmp/testSem", 'S');
    idSemaforo = semget(llave, 'S', 0666 | IPC_CREAT);
    
    pid = fork();
    
    if(pid == -1) printf("Error al crear el hijo\n");
    else if(pid == 0) escribir(idSemaforo);
    else{
		wait(&estado);
		leer(idSemaforo);
	}
    return 0;
}

void escribir(int sem){
    int fact, i;
    while(1){
		printf("Ingresa un número: ");
		scanf("%d",&fact);
		s.val = fact;
		semctl(sem, 0, SETVAL,s);
		leer(sem);
		if(fact == -1) break;
    }
}

void leer(int sem){
    int c, i;
    while(1){
		c = semctl(sem,0,GETVAL,s);
		printf("Se recibió el número: %d y su factorial es: %d \n", c, factorial(c));
        escribir(sem);
     
        if(c == -1) break;
    }
}

int factorial(int n){
    int a = 1;
    int i;    
    for(i = 2; i<=n;++i) a*=i;
    
    return a;
}