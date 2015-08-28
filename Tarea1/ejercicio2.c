/* Tarea 1. Aritmética de Apuntadores
*  Ejercicio 2 Encuesta
*  José Luis García R
*  Programación Avanzada
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 25
#define M 50
#define P 3     
#define L 200

//Declaracion de Estructuras
typedef struct{
    char *nombre;
    int edad;
    int *respuestas;
}participante;

typedef struct{
    char *pregunta;
    char *uno;
    char *dos;
    char *tres;
    char *cuatro;
    char *cinco;
    char *seis;
}pregunta;


//Declaración de Métodos
pregunta* preguntas( pregunta *pr);
participante* participantes( participante *par, pregunta *pr, int *respuestas);
void histograma( int *respuestas);

//Variables Globales
int poblacion = 1;
int *resp;

int main(int argc, char** argv) {
    
    int op    = 0;
    
    pregunta *pr      = (pregunta *) malloc( sizeof( pregunta));
    pr                = (pregunta *) malloc( sizeof( pregunta) * P);
    participante *par = ( participante *) malloc( sizeof( participante));
    par->respuestas   = (int *) malloc( sizeof( int) * P);
    resp              = (int *) malloc( sizeof( int) * L);
    char * menu       = (char *) malloc( sizeof( char) * L);
    strcpy(menu,"\n::::\tMenu Principal\t::::\n1. Ingresar preguntas\n2. Nuevo participante\n3. Histograma de Frecuencia\n4. Salir\n\nFavor de ingresar una opción.\n");
    while(op!=4){
        
        printf("%s",menu);
        scanf("%d", &op);
        switch(op){
            case 1:
                pr=preguntas(pr);
                break;
            case 2:
                par=participantes(par, pr, resp);
                break;
            case 3:
                histograma(resp);
                break;
            case 4:
                printf("Finalizando programa. Hasta luego");
                break;
            default:
                printf("Opcion no valida, favor de ingresar otra opcion");
                break;
        }
    }
    
    pregunta * aux;
    for (aux = pr; aux < (pr+poblacion); ++aux) {
        free(pr->pregunta);
        free(pr->dos);
        free(pr->tres);
        free(pr->cuatro);
        free(pr->cinco);
        free(pr->seis);
    }
    
    free(pr);
    free(par);
    free(resp);
    free(menu);
    return 0;
}

//Implementación de Métodos
pregunta* preguntas(pregunta *pr){
    int i;
    for(i=0;i<P;++i){
        
        (pr+i)->pregunta = (char * ) malloc(sizeof(char) * M);
        printf("\nIngrese la pregunta %d \n", i+1);
        scanf("%s",(pr+i)->pregunta);
        
        (pr+i)->uno = (char * ) malloc(sizeof(char) * M);
        printf("Ingrese respuesta 1\n");
        scanf("%s",(pr+i)->uno);
        
        (pr+i)->dos = (char * ) malloc(sizeof(char) * M);
        printf("Ingrese respuesta 2\n");
        scanf("%s",(pr+i)->dos);
        
        (pr+i)->tres = (char * ) malloc(sizeof(char) * M);
        printf("Ingrese respuesta 3\n");
        scanf("%s",(pr+i)->tres);
        
        (pr+i)->cuatro = (char * ) malloc(sizeof(char) * M);
        printf("Ingrese respuesta 4\n");
        scanf("%s",(pr+i)->cuatro);
        
        (pr+i)->cinco = (char * ) malloc(sizeof(char) * M);
        printf("Ingrese respuesta 5\n");
        scanf("%s",(pr+i)->cinco);
        
        (pr+i)->seis = (char * ) malloc(sizeof(char) * M);
        printf("Ingrese respuesta 6\n");
        scanf("%s",(pr+i)->seis);
    }
    printf("Sección finalizada\n");
    return pr;
}

participante* participantes(participante *par, pregunta *pr, int *resp){
    
    participante *temp;
    int edad, i, res;
    temp =par;
    temp = (participante *) realloc( par, sizeof( participante) * poblacion);
    if( temp == NULL){
        printf("Lo sentimos, ya no hay memoria para agregar participantes.");
        return par;
    }
    par = temp;
    
    (par+poblacion)->nombre = (char * ) malloc(sizeof(char) * N);
    printf("Ingrese el nombre del participante\n");
    scanf("%s",(par+poblacion)->nombre);
    
    do{
        printf("Ingrese la edad del participante\n");
        scanf("%d", &edad);
        if( edad < 18 || edad > 120)
            printf("Lo sentimos, su edad no es válida para realizar la encuesta\n");
    }while( edad < 18 || edad > 120);
    (par+poblacion)->edad = edad;
    
    for( i=0; i<P; ++i){
        printf("Pregunta %d\n%s\n", i+1, (pr+i)->pregunta);
        printf("1) %s\n",(pr+i)->uno);
        printf("2) %s\n",(pr+i)->dos);
        printf("3) %s\n",(pr+i)->tres);
        printf("4) %s\n",(pr+i)->cuatro);
        printf("5) %s\n",(pr+i)->cinco);
        printf("6) %s\n",(pr+i)->seis);
        printf("Favor de responder con el número de la respuesta\n");
        scanf("%d", &res);
        
        if( edad >= 18 && edad <= 25)
                *(resp+( 60*0 )+( i*6 )+ res) +=1;
        if( edad >= 26 && edad <= 35)
                *(resp+( 60*1 )+( i*6 )+ res) +=1;
        if( edad >= 36 && edad <= 45)
                *(resp+( 60*2 )+( i*6 )+ res) +=1;
        if( edad >= 46 && edad <= 65)
                *(resp+( 60*3 )+( i*6 )+ res) +=1;
        if( edad >= 66 && edad <= 120)
                *(resp+( 60*4 )+( i*6 )+ res) +=1;
    }
    ++poblacion;
    
    return par;
}

void histograma(int *resp){
    int i, j;
    
    for( i=0; i<P; ++i){
        printf("Pregunta %d\n", i+1);
        printf("No. Res\tFrec 18-25\tFrec 26-35\tFrec 36-45\tFrec 56-65\tFrec 66-120\n");
        for(j=1;j<7;++j)
                printf("%7d\t%10d\t%10d\t%10d\t%10d\t%10d\n", j, *(resp+(60*0)+(i*6)+j), *(resp+(60*1)+(i*6)+j), *(resp+(60*2)+(i*6)+j), *(resp+(60*3)+(i*6)+j), *(resp+(60*4)+(i*6)+j));
    }
}