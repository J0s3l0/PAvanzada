/****************************************************************************************
* FILE: main.c
* DESCRIPCIÓN:
*   Ejemplo OpenMP - Usando opciones de Variable de Entorno OMP_MAX_ACTIVE_LEVELS - C Version
*   Con esta variable se indica el nivel de paralelismo anidado, dependiendo de los niveles de
*   anidamiento que se tenga dentro de la región de paralelismo
*
*       ejecutar en terminal 
* 
*       export OMP_MAX_ACTIVE_LEVELS = # número positivo
* 
*       export OMP_MAX_ACTIVE_LEVELS = 3
* 
*  
* AUTHOR: José Luis García Reymundo  12.11.2015
*****************************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    int i = -1, j = -1, nested;
    
    nested = omp_get_nested();
    
    if(nested == 1) printf("Nested activo\n");
    else if(nested == 0) printf("Nested desactivado\n");
    
    
    #pragma omp parallel num_threads (8)
    {
        #pragma omp single
        {
            i = omp_get_thread_num () + omp_get_num_threads () * 256;
            #pragma omp parallel num_threads (4)
            {
                #pragma omp single
                {
                    j = omp_get_thread_num () + omp_get_num_threads () * 256;
                }
            }
        }
    }
    
    if (i < 4 * 256 || i >= 4 * 256 + 4)
        abort ();
    if (j < 2 * 256 || j >= 2 * 256 + 2)
        abort ();
  
  return 0;
  
}