#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define TCP_PORT 7000
#define TIME 30 //tiempo predeterminado de ALARMA
#define ARCHIVO "archivo.txt" //archivo para almacenar lecturas

void * sensor ();
void escribir(int t);

int main(int argc, char **argv)
{
	struct sockaddr_in direccion;
	char buffer[1000];
	int  cliente;
	int leidos, escritos;
	
	// REcibe como argumento la IP del servidor
	if (argc != 2)
	{
		printf("Use: %s IP_Servidor\n", argv[0]);
		exit(-1);
	}
	
	//Crear el socket
	cliente = socket(PF_INET, SOCK_STREAM, 0);
	
	// Hacer enlace con el socket
	inet_aton(argv[1], &direccion.sin_addr);
	direccion.sin_port = htons(TCP_PORT);
	direccion.sin_family =  AF_INET;
	
	escritos = connect(cliente, (struct sockaddr *) &direccion, sizeof(direccion));
	
	if (escritos == 0)
	{
		printf("Conectado a  IP: %s y Puerto TCP: %d \n", inet_ntoa(direccion.sin_addr), 
		ntohs(direccion.sin_port) );
	
		// Leer del socket
		while ( leidos = read(fileno(stdin), &buffer, sizeof(buffer)))
		{
			write(cliente, &buffer, leidos);
		}
	}
	
	// Cerrar sockets
	close(cliente);
	
	return 0;
}


void * sensor (){

    int temp;
    int time=0, tiempo;//tiempo en que se lee

    time = 1+rand()%60;
    tiempo= time;

    while(1){

        temp= 1+rand()%99;
        
        time=tiempo;
        
        printf("Temp: %d\n",temp);
        
        escribir(temp);

        if(time > 0){
            printf("Tiempo:%d \n    ",time);
        }
        sleep(time);
    }


}

void escribir (int t){

    FILE *file = fopen(ARCHIVO, "a+");
    
    fprintf(file, "temp: %d\n",t);
    fclose(file);

}
