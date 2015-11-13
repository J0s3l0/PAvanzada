/****************************************************************************************
* FILE: main.c
* DESCRIPCIÓN:
*   Ejemplo OpenMP - Usando opciones de Variable de Entorno OMP_THREAD_LIMIT - C Version
*   El thread master consulta e imprime la cantidad de threads que se estaran utilizando
*   de acuerdo al valor dado a la variable OMP_THREAD_LIMIT, que puede incrementar el 
*	número de threads por defacto, es decir aumenta el número de threads para que pueda 
*   existir mayor paralelismo sin importar el hardware que se tenga, se debe tener cuidado
*   con no aumentar demasiado porque puede no favorecer
* 
*       ejecutar en terminal 
* 
*       export OMP_THREAD_LIMIT = # NÚMERO POSITIVO TOTAL DE THREADS QUE SE QUIEREN SOPORTAR
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
    
    for (i=0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    
    chunk = CHUNK;
    
    inicio = omp_get_wtime();
    #pragma omp parallel shared(a,b,c,nthreads,chunk) private(i,tid) num_threads(16)
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