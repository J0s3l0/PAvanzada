#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N  8
#define E  10
#define KM 5

void compitiendo(int);

int main(int argc, char** argv){
    
    int comp[N];
    int id;
    int i;
    int j;
    int m;
    int g;

    for(j = 0; j < N; ++j){
        comp[j] = 0;
    }
    
    omp_set_num_threads(N);

    #pragma omp parallel private (id,i)
    {
		id = omp_get_thread_num();
		
        for(i = 0; i < E; ++i){

            compitiendo(id);

            #pragma omp single
            {
                comp[id]++;
                g = id;
            }
            
            #pragma omp barrier
            #pragma omp single
            {
                system("clear");
                printf("El ciclista %d ganó la etapa %d\n", g, i);
            }
        }
    }
    
    return 0;
}

void compitiendo(int id){
     printf("Competidor %d  compitiendo\n",id);
     sleep(KM);
}