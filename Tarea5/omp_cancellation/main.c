/****************************************************************************************
* FILE: main.c
* DESCRIPCIÓN:
*   Ejemplo OpenMP - Usando opciones de Variable de Entorno OMP_CANCELLATION - C Version
*   Variable de entorno para activar o desactivar la opción de cancelar acciones 
*
*       ejecutar en terminal 
* 
*       export OMP_CANCELLATION = { true | false}
*  
*  
* AUTHOR: José Luis García Reymundo  12.11.2015
*****************************************************************************************/

#include <stdio.h>
#include <omp.h>
#define N 10000

int main(int argc, char** argv){
    
    int tid;
    int i;
    int cancelStatus = 0;
    double inicio, fin;
    double A[N], B[N], S[N], P[N];
    
    
    for(i=0; i<N; ++i){
        A[i] = i * 1.75;
        B[i] = A[i] * 0.58;
    }
    
    
    //paralelismo anidado
    omp_set_nested(1);
    //cancelStatus = omp_get_cancellation();
    
    inicio = omp_get_wtime();
    #pragma omp parallel private(i, tid, cancelStatus) num_threads(4)
    {
        
        if(cancelStatus == 1){
            printf("omp section cancelada");
        }
            
        #pragma omp sections nowait
        {
            #pragma omp section
            for(i = 0; i < N; ++i ){
                S[i] = A[i] + B[i];
            }
            
            #pragma omp section
            for(i = 0; i < N; ++i ){
                P[i] = A[i] * B[i];
            }
            
        }
        
    }
    fin = omp_get_wtime();
    
    printf("Tiempo = %f\n", fin-inicio);
    
    
    return 0;
}