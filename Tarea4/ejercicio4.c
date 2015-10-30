#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#define TIME 6 
#define N 3
#define TM 30 
#define HM 25 
#define VM 20 
#define TMI 2 
#define HMI 6 
#define VMI 2 
#define VAR 2 
#define ARCHIVO "test.txt" 

pthread_mutex_t imp = PTHREAD_MUTEX_INITIALIZER;

void * sensor (void *);
void escribir(int , int, int, int);

int main(int argc, char** argv) {

    pthread_t sensores[N];
    int i;

    //sigset_t set;

    //sigemptyset(&set);
    //sigaddset(&set,SIGINT);
    
    //pthread_sigmask(SIG_BLOCK, &set, NULL);

    for(i=0; i<N ; ++i){
        pthread_create(&sensores[i], NULL, sensor, (void *) i);
    }

    for(i=0; i<N; ++i){
        pthread_join(sensores[i], NULL);
    }

    return (EXIT_SUCCESS);
}

void * sensor (void * arg){


    int tid = (int) arg;
    int temp;
    int hum;
    int vel;
    int time=0,tiempo;

    //srand(time(NULL));

    time = 1+rand()%7;
    tiempo= time;

    while(1){

        temp= (TMI-VAR)+rand()%(TM+VAR);
        hum = (HMI-VAR)+rand()%(HM+VAR);
        vel = (VMI-VAR)+rand()%(VM+VAR);
        int arriba=0;
        int abajo=0; 
        int sig;
        
        //sigset_t wait;
        //sigemptyset(&wait);
        //sigaddset(&wait,SIGINT);
        time=tiempo;

        pthread_mutex_lock(&imp);
        printf(" *** Sensor %d ***\n",tid);
        printf("Temp: %d\n",temp);
        printf("Hum: %d\n",hum);
        printf("Vel: %d\n",vel);
        escribir(tid, temp, hum, vel);
        pthread_mutex_unlock(&imp);

        
        if(time > 0){
            printf("Tiempo:%d \n",time);
        }
        sleep(time);
    }


}

void escribir (int s,int t,int h,int v){

    FILE *file = fopen(ARCHIVO, "a+");
    fprintf(file,"Sensor: %d\n",s);
    fprintf(file, "temp: %d, humedad: %d,velocidad:%d\n",t,h,v);
    fclose(file);

}