#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

#define CANTIDAD 5
#define SEGUNDOS 3

void crearDirectorio();
void comprobarDirectorio();
void gestorAlarma();
void mostrarFicheros();

char * directorio = "./datos";
int grabar;

int main(int argc, char **argv)
{
	FILE * archivo;
	int i;
	char cadena[20];
	
	sigset_t ninguna, todas;
    sigfillset(&todas);
    sigdelset(&todas, SIGALRM);
    sigprocmask(SIG_BLOCK, &todas, NULL);
	
	comprobarDirectorio();
	signal(SIGALRM, gestorAlarma);
	
	
	for(i = 0; i < CANTIDAD; ++i)
	{
		strcpy(cadena, directorio);
		strcat(cadena, "/a");
		sprintf(cadena, "%s%d", cadena, i);
		//printf("SE va a crear el archivo %s\n", cadena);
		grabar = 1;
		
		archivo = fopen(cadena, "w");
		alarm(SEGUNDOS);
		while(grabar)
		{
			fwrite("x",sizeof(char), 1, archivo);
		}
		
		fclose(archivo);
	}
	
	mostrarFicheros();
	
	return 0;
}

void crearDirectorio()
{
	mkdir(directorio,0777);
}

void mostrarFicheros()
{
	DIR *dp;
	struct dirent *ep;
	struct stat f;
	char nombrearch[20];
	
	dp = opendir(directorio);
	if(dp != NULL)
	{
		
		printf("%-10s %s\n", "Archivo", "Tamaño(B)");
		while (ep = readdir(dp) )
		{
			strcpy(nombrearch,directorio);
			strcat(nombrearch, "/");
			strcat(nombrearch, ep->d_name);
			stat(nombrearch, &f);
			if( (strcmp(ep->d_name,".") != 0) && (strcmp(ep->d_name,"..") != 0) )
			{
				printf("%-10s ", ep->d_name);
				printf("%d \n", f.st_size);
			}
		}
		closedir(dp);
	}
	else
	{
		perror("Error al abrir el directorio");
	}
	
}

void gestorAlarma()
{
	grabar = 0;
}