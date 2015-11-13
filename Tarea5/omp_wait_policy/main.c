/****************************************************************************************
* FILE: main.c
* DESCRIPCIÓN:
*   Ejemplo OpenMP - Usando opciones de Variable de Entorno OMP_WAIT_POLICY - C Version
*   Se especifica el comportamiento de los threads durante su tiempo de espera
*   active indica que consumirá ciclos de procesamiento mientras espera su turno 
*   pasive indica que no consumirá ciclos de procesamiento mientras espera su turno
*       ejecutar en terminal 
* 
*       export OMP_WAIT_POLICY = {active | pasive}
* 
*       export OMP_WAIT_POLICY = active
*       export OMP_WAIT_POLICY = passive
* 
*  
* AUTHOR: José Luis García Reymundo  12.11.2015
*****************************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100000
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
    #pragma omp parallel shared(a,b,c,nthreads,chunk) private(i,tid) num_threads(12)
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