#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#define THREADS    10
#define LOOP           10000


//struktura dane watku
struct thread_data
{
   int  thread_id;
   int  circle;     //liczenie ile w kole
};

struct thread_data thread_data_array[THREADS];

int circle_detection() {
    double x, y;
    x = drand48();
    y = drand48();

    //jesli wylosowany punkt jest w okregu
    if(sqrt(((x-1) * (x-1)) + ((y-1) * (y-1))) <= 1) 
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}


void *ThreadComputing(void *threadarg) {
    struct thread_data *temp_data;

    temp_data = (struct thread_data *) threadarg;
    
    for (int i = 0; i < LOOP; i++)
    {       
        //zapisanie do org. stuktury wynikow 
        thread_data_array[temp_data->thread_id].circle += circle_detection();
    }
    
    printf("Watek %d wartosc PI: %f\n",temp_data->thread_id,(float)thread_data_array[temp_data->thread_id].circle * 4 / LOOP);
    
    sleep(1);

    pthread_exit(NULL);
}


int main()
{
    //potrzebne do drand48()
    srand48(time(NULL));

    pthread_t threads[THREADS];

    int rc;
    //tworzenie watkow
    for(int i = 0; i < THREADS; i++) {
        thread_data_array[i].thread_id = i;
        rc = pthread_create(&threads[i], NULL, ThreadComputing, (void *) &thread_data_array[i]);
        
        if (rc) {
            printf("ERROR w %d\n", rc);
            exit(-1);
        }
    }

    //czekanie na wszystkie watki
    sleep(1);
    
    int count = 0;
    //zlicza pi z wszystkich watkow
    for(int i = 0; i < THREADS; i++)
    {
        count += thread_data_array[i].circle;
    }
    printf("Wszystkie watki, wyestymowana wartosc PI: %f\n",(double)count * 4 / (THREADS * LOOP));
    pthread_exit(NULL);

}