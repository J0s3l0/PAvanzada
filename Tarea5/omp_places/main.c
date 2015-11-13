/****************************************************************************************
* FILE: main.c
* DESCRIPCIÓN:
*   Ejemplo OpenMP - Usando opciones de Variable de Entorno OMP_PLACES - C Version
*   al darle valor a esta variable de entorno se especifica los lugares donde serán
*   ejecutados los threads sobre cada core, socket o el número de thread que se utilizara
*   esto se especifica en forma de lista
* 
*       ejecutar en terminal 
*
*       export OMP_PLACES = threads | cores | sockets {}
* 
*       export OMP_PLACES = {0,1,2}, {3,4,5},{6,7,8}
*       export OMP_PLACES = {0:3}, {3:3},{6:3}
* * 
*  
* AUTHOR: José Luis García Reymundo  12.11.2015
*****************************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10000
#define CHUNK 100

int main (int argc, char *argv[]) {
    
    int nthreads, tid, i, chunk;
    float a[N], b[N], c[N];
    double inicio, fin;
    omp_sched_t kind;
    int modifier;
    
    for (i=0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    
    chunk = CHUNK;
    
    inicio = omp_get_wtime();
    #pragma omp parallel shared(a,b,c,nthreads,chunk) private(i,tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0){
            nthreads = omp_get_num_threads();
            printf("Número de threads = %d\n", nthreads);
            
        }
    
        #pragma omp for schedule(dynamic,chunk)
            for (i=0; i<N; i++){
                c[i] = a[i] + b[i];
            }
    
    }  
    fin = omp_get_wtime();
    printf("Tiempo = %f\n", fin-inicio);
    
}