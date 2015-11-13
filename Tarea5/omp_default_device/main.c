/****************************************************************************************
* FILE: main.c
* DESCRIPCIÓN:
*   Ejemplo OpenMP - Usando opciones de Variable de Entorno OMP_DEFAULT_DEVICE - C Version
*   Variable de entorno para inicializar el valor de default-device-var ICV
*   debe ser un entero no negativo
*
*       ejecutar en terminal 
* 
*       export OMP_DEFAULT_DEVICE = # número entero positivo
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
    double inicio, fin;
    double A[N], B[N], S[N], P[N];
    
    
    for(i=0; i<N; ++i){
        A[i] = i * 1.75;
        B[i] = A[i] * 0.58;
    }
    
    
    omp_set_nested(1);
    
    inicio = omp_get_wtime();
    #pragma omp parallel private(i, tid) num_threads(8)
    {
            
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