/****************************************************************************************
* FILE: main.c
* DESCRIPCIÓN:
*   Ejemplo OpenMP - Usando opciones de Variable de Entorno OMP_DYNAMIC - C Version
*   El thread master consulta e imprime la cantidad de threads que se estaran utilizando
*   de acuerdo al valor dado a la variable OMP_DYNAMIC, si es true quiere decir que se
*   estará optimizando el número de cores de acuerdo al hardware, si es false se tomará
*   por defacto el valor de OMP_NUM_THREADS
* 
*       ejecutar en terminal 
* 
*       export OMP_DYNAMIC = {true | false}
* 
*       export OMP_DYNAMIC = true
*       export OMP_DYNAMIC = false
* 
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