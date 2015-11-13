/******************************************************************************
* FILE: main.c
* DESCRIPCIÓN:
*   Ejemplo OpenMP - Usando opciones de Variable de Entorno OMP_NUM_THREADS - C Version
*   El thread master consulta e imprime la cantidad de threads que se estaran utilizando
*   de acuerdo a los threads de la variable de entorno definida
* 
*       ejecutar en terminal
* 
*       export OMP_NUM_THREADS = {# IGUAL AL NÚMERO DE CORES PARA UN MEJOR RENDIMIENTO}
* 
*       export OMP_NUM_THREADS = 8
* 
*  
* AUTHOR: José Luis García Reymundo  12.11.2015
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int nthreads, tid;

    #pragma omp parallel private(nthreads, tid)
    {
    
        tid = omp_get_thread_num();
        printf("Hola Mundo desde el thread = %d\n", tid);
    
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Número de threads = %d\n", nthreads);
        }
    
      }  

}