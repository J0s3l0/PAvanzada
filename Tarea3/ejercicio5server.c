/*
*	Ejercicio 5 server
*	Server con Socket UNIX
*
*	José Luis García Reymundo
* 	A01063645
*/


#include <stdio.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>

int main(int argc, const char * argv[]) {
    struct sockaddr_un direccion;
    char buffer[128];
    pid_t pid;
    
    int servidor, cliente;
    
    int leidos, escritos;
    
    if (argc != 2) {
        printf("Error. Use: %s Archivo \n", argv[0]);
        exit(-1);
    }
    
    //Crear el socket
    servidor = socket(PF_UNIX, SOCK_STREAM, 0);

    // Enlace con el socket
    strcpy (direccion.sun_path, argv[1]);
    
    bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));
    
    printf("(%u):Padre\n", getpid());
		
    while(1){
		// Escuchar a los clientes
		listen(servidor, 10);
			
		// Comunicación
		socklen_t tamano = sizeof(direccion);
		cliente = accept(servidor, (struct sockaddr *) &direccion, &tamano);
		
		if (cliente < 0) {
			printf("Error aceptando conexiones\n");
			return 1;
		}
		
		pid = fork();
		if(pid == 0){
			printf("(%u):Aceptando conexiones en %s\n",
				getpid(),
				direccion.sun_path);

			// Leer de socket y escribir en pantalla
			while (leidos = read(cliente, &buffer, sizeof(buffer))) {
				printf("El cliente %d dice:\n", cliente);
				write(fileno(stdout), &buffer, leidos);
				printf("Qué contestarás?\n");
				leidos = read(fileno(stdin), &buffer, sizeof(buffer));
				write(cliente, &buffer, leidos);
			}
			close(cliente);
			break;
		}
	}

    close(servidor);
        
    return 0;
}
