/* Tarea 1. Aritmética de Apuntadores
*  Ejercicio 1 Puerto Pesquero
*  José Luis García R
*  Programación Avanzada
*
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char * nombre;
    char * apellido;
    int edad;
    int telefono;
    int cama;
} paciente;

int main(int argc, const char * argv[])
{
    
    paciente * hospital;
    paciente * aux;
    
    int cantidad = 0;
    
    printf("¿Cuántos pacientes quieres registrar?: ");
    scanf("%d", &cantidad);
    
    hospital = (paciente *) malloc(sizeof(paciente) * cantidad);
    
    paciente * final = hospital + cantidad;
    
    for (aux = hospital; aux < final; ++aux) {
        
        aux->nombre = (char * ) malloc(sizeof(char) * 25);
        
        printf("Entre el nombre del paciente: ");
        scanf("%s", aux->nombre);
        
        aux->apellido = (char * ) malloc(sizeof(char) * 25);
        
        printf("Entre el apellido del paciente: ");
        scanf("%s", aux->apellido);
        
        printf("Entre la edad del paciente: ");
        scanf("%d", &aux->edad);
        
        printf("Entre el telefono del paciente: ");
        scanf("%d", &aux->telefono);
        
    }
    
    int masPacientes = 0;
    
    printf("Quieres registrar más pacientes. ¿Cuántos?: ");
    scanf("%d", &masPacientes);
    
    if (masPacientes > 0) {
        hospital = (paciente *) realloc(hospital, sizeof(paciente) * (cantidad + masPacientes));
        
        final = hospital + cantidad + masPacientes;
        
        for (aux = hospital + cantidad; aux < final; ++aux) {
            
            aux->nombre = (char * ) malloc(sizeof(char) * 25);
        
            printf("Entre el nombre del paciente: ");
            scanf("%s", aux->nombre);
        
            aux->apellido = (char * ) malloc(sizeof(char) * 25);
        
            printf("Entre el apellido del paciente: ");
            scanf("%s", aux->apellido);
        
            printf("Entre la edad del paciente: ");
            scanf("%d", &aux->edad);
        
            printf("Entre el telefono del paciente: ");
            scanf("%d", &aux->telefono);
            
        }
        
    }
    
    
    // Mostrar los pacientes
    printf("\n\n--- Listado de pacientes ---\n\n");
    for (aux = hospital; aux < final; ++aux) {
        printf("%25s \t %25s \t %4d \t %4d \t %4d \n",
               aux->nombre,
               aux->apellido,
               aux->edad,
               aux->telefono,
               aux->cama);
    }
    
    // Liberar la memoria
    
    for (aux = hospital; aux < final; ++aux) {
        free(aux->nombre);
        free(aux->apellido);
    }
    
    free(hospital);
    
    return 0;
}