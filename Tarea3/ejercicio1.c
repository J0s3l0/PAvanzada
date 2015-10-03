/*
*	Ejercicio 1 Demonio
*
*	José Luis García Reymundo
* 	A01063645
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>


int main(int argc, char** argv){

    pid_t pid, sid;
    pid = fork();
        
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
        
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* Cambiar la máscara de modo de archivo */
    umask(0);

    /* Crear nuevo SID para el proceso hijo */
    sid = setsid();

    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    /* Inicialización del Demonio */
    int opt, num;
    opt = getopt(argc, argv, "m:");
    if(opt){
        switch(opt){
            case 'm':
                num = atoi(optarg);
        }
    }
    else
        num = 1;
        
    while (1) {
        system("ps -fea");
        sleep(num*60);
    }

    exit(EXIT_SUCCESS);  
    return 0;
}
