/******************************************************************************
* FILE: main.c
* DESCRIPCIÓN:
*   Ejemplo OpenMP - Usando opciones de Variable de Entorno OMP_SCHEDULE - C Version
*   El thread master consulta e imprime la cantidad de threads que se estaran utilizando
*   indicando el número de thread que empezará a realizar la suma de la seccion asignada
*   así como el tipo de schedule que se estará usando
* 
*       ejecutar en terminal alguno de los siguientes ejemplos u otra variación
* 
*       export OMP_SCHEDULE = {static | dynamic | guided + chunk(opcional) | auto}
* 
*       export OMP_SCHEDULE = static
*       export OMP_SCHEDULE = guided,50
*       export OMP_SCHEDULE = dynamic,50
*       export OMP_SCHEDULE = auto
* 
*  
* AUTHOR: José Luis García Reymundo  12.11.2015
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10000

int main (int argc, char *argv[]) {
    
    int nthreads, tid, i, chunk;
    float a[N], b[N], c[N];
    double inicio, fin;
    omp_sched_t kind;
    int modifier;
    
    //Esta llamada no realiza los cambios enviados, se tiene que realizar antes de ejecutar el ejecutable
    //system("export OMP_SCHEDULE=dynamic"); 
    //sleep(2);

    
    for (i=0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    
    inicio = omp_get_wtime();
    #pragma omp parallel shared(a,b,c,nthreads,kind,modifier) private(i,tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0){
            nthreads = omp_get_num_threads();
            printf("Número de threads = %d\n", nthreads);
            omp_get_schedule (&kind, &modifier);
            
            if (kind == omp_sched_static) printf("Sched estático\n");
            else if (kind == omp_sched_guided) printf("Sched guiado\n");
            else if (kind == omp_sched_dynamic) printf("Sched dinámico\n");
            else if (kind == omp_sched_auto) printf("Sched automático\n");
        }
        printf("Thread %d empezando...\n",tid);
    
        #pragma omp for 
            for (i=0; i<N; i++){
                c[i] = a[i] + b[i];
                //printf("Thread %d: c[%d]= %f\n",tid,i,c[i]);
            }
    
    }  
    fin = omp_get_wtime();
    printf("Tiempo = %f\n", fin-inicio);
    
}