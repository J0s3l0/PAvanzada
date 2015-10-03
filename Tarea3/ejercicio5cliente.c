/*
*	Ejercicio 5 cliente
*	Cliente con Socket UNIX
*
*	José Luis García Reymundo
* 	A01063645
*/


#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>

int main(int argc, const char * argv[]) {
    
    struct sockaddr_un direccion;
    char buffer[128];
    
    int cliente;
    
    int leidos, escritos;
    
    if (argc != 2) {
        printf("Error. Use: %s Archivo \n", argv[0]);
        exit(-1);
    }
    
    //Crear el socket
    cliente = socket(PF_UNIX, SOCK_STREAM, 0);
    
    // Establecer conexión
    strcpy (direccion.sun_path, argv[1]);
    
    int estado = connect(cliente, (struct sockaddr *) &direccion, sizeof(direccion));
    
    // Comunicación
    if (estado == 0) {
        printf("Conectado a %s \n",
               direccion.sun_path);
        
        // Leer de teclado y escribir en socket
        printf("Escribele al servidor:\n");
        while (leidos = read(fileno(stdin), &buffer, sizeof(buffer))) {
			write(cliente, &buffer, leidos);
            
			leidos = read(cliente, &buffer, sizeof(buffer));
			printf("El servidor te contestó:\n");
            write(fileno(stdout), &buffer, leidos);
			printf("Escribele al servidor:\n");
        }
    }else return 1;
    
    // Cerrar el socket
    close(cliente);
    
    return 0;
}
