#include <stdio.h>
#include <signal.h>
#include <unistd.h> 
#include <stdlib.h> 

pid_t pid;	
//int x=5, y=0;
void gestor(int);
void alarma(int);

int main(int argc, const char * argv[]){
    
    int contador = 10;
	pid = fork();
	
	if(pid == 0){
		
		while(contador-- > 0){
			printf("Estoy durmiendo - %d...\n", contador);
			sleep(1);
		}
		
		kill(getppid(), SIGUSR1); //Envía la señal SIGUSR1 al padre
		
	}
	else if(pid>0){
	    
	    signal(SIGUSR1, gestor);
	    
	    //verificar que no haya error
		if(signal(SIGINT, gestor) == SIG_ERR){
			printf("Error al establecer el manejador de la señal");
			exit(EXIT_FAILURE);
		}
		
		if(signal(SIGINT, gestor) == SIG_ERR){
			printf("Error al establecer el manejador de la señal");
			exit(EXIT_FAILURE);
		}
		
		//signal(SIGALRM, alarma); 
		alarm(3);
		
		while(1);
	}
	return 0;
}

void gestor(int id){
	
	if(id == SIGUSR1){
		printf("Se ha pulsado X veces CTRL+C y se ha pulsado Y veces CTRL+Z. Acabando…\n");
		
		kill(pid, SIGKILL);
	    raise(SIGKILL);
		
	}
	else if(id == SIGINT){
		printf("Oprimiste Ctrl+C\n");
	}
	else if(id == SIGTSTP){
		printf("Oprimiste Ctrl+Z\n");
	}
	
}

void alarma(int id){
	printf("Aparezco cada d segundos\n");
	kill(pid, SIGUSR1);
}