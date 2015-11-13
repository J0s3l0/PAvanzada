/****************************************************************************************
* FILE: main.c
* DESCRIPCIÓN:
*   Ejemplo OpenMP - Usando opciones de Variable de Entorno OMP_PROC_BIND - C Version
*   Cada thread realizara una parte de la suma, por lo que si la variable es true el 
*   resultado de la suma será real, mientras que si es false puede que cambie por que
*   el thread master no se espera a que terminen todos, por lo que la suma será diferente
*
*       ejecutar en terminal 
* 
*       export OMP_PROC_BIND = {true | false}
* 
*       export OMP_PROC_BIND = true
*       export OMP_PROC_BIND = false
* 
*  
* AUTHOR: José Luis García Reymundo  12.11.2015
*****************************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

int main (int argc, char *argv[]) {

    int   i;
    float a[N], b[N], sum; 
    
    for (i=0; i < N; i++)
      a[i] = b[i] = i * 1.0;
    sum = 0.0;
    
    #pragma omp parallel for reduction(+:sum)
      for (i=0; i < N; i++)
        sum = sum + (a[i] * b[i]);
    
    printf("Suma = %f\n",sum);

}