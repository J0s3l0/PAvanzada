#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define TCP_PORT 7000

int main(int argc, char **argv)
{
	struct sockaddr_in direccion;
	char buffer[1000];
	int servidor, cliente;
	int leidos, escritos;
	
	// REcibe como argumento la IP del servidor
	if (argc != 2)
	{
		printf("Use: %s IP_Servidor\n", argv[0]);
		exit(-1);
	}
	
	//Crear el socket
	servidor = socket(PF_INET, SOCK_STREAM, 0);
	
	// Hacer enlace con el socket
	inet_aton(argv[1], &direccion.sin_addr);
	direccion.sin_port = htons(TCP_PORT);
	direccion.sin_family =  AF_INET;
	
	bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));
	
	listen(servidor, 10);
	escritos = sizeof(direccion);
	
	cliente = accept(servidor, (struct sockaddr *) &direccion, &escritos);
	
	if (cliente >= 0)
	{
		printf("Aceptando comunicaciones en IP: %s y Puerto TCP: %d \n", inet_ntoa(direccion.sin_addr), 
		ntohs(direccion.sin_port) );
	
		// Leer del socket
		while ( leidos = read(cliente, &buffer, sizeof(buffer)))
		{
			write(fileno(stdout), &buffer, leidos);
		}
	}
	
	// Cerrar sockets
	close(servidor);
	close(cliente);
	
	return 0;
}
