/*
*	Ejercicio 4a
*	Colas de Mensaje
*
*	José Luis García Reymundo
* 	A01063645
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

int main(){
	char buf[10];
	int msqid;
    key_t key;
    
	if ((key = ftok("ejercicio4a.c", 'B')) == -1) {
		perror("ftok");
		return 1;
	}    
	if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
		perror("msgget");
		exit(1);
	}
	printf("Ingrese un número para calcular su factoial:\n");
    
    while(fgets(buf, sizeof(buf), stdin) != NULL) {
		int len = strlen(buf);
		if (msgsnd(msqid, &buf, len+1, 0) == -1) perror("msgsnd");
	}
	if (msgctl(msqid, IPC_RMID, NULL) == -1) {
		perror("msgctl");
		exit(1);
	}
	return 0;
}