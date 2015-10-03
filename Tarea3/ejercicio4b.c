/*
*	Ejercicio 4b
*	Colas de Mensaje
*
*	José Luis García Reymundo
* 	A01063645
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int factorial(int );

int main(){
	char buf[10];
	int msqid, a;
	key_t key;
    
	if ((key = ftok("ejercicio4a.c", 'B')) == -1) {
		perror("ftok");
		return 1;
	}
    
	if ((msqid = msgget(key, 0644)) == -1) {
		perror("msgget");
		exit(1);
	}
	
	while(1) {
		if (msgrcv(msqid, &buf, sizeof(buf), 0, 0) == -1) {
			perror("msgrcv");
			return 1;
		}
        a = atoi(buf);
		printf("Factorial de %s = %d\n", buf, factorial(a));
	}
	return 0;
}

    
int factorial(int n){
    int a = 1;
    int i;
    for(i = 2; i<=n;++i) a*=i;
    return a;
}