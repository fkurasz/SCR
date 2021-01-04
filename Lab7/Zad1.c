#include <pthread.h>
#include <stdio.h>


void *print_func(void *ID)
{
    printf("Hello SCR. Written by thread %ld \n",(long)ID);
    return NULL;
}

int main()
{
    pthread_t newThreat[5];
    
    for(int i = 0; i < 5; i++)
    {
        if(pthread_create(&newThreat[i], NULL, print_func, pthread_self)) 
        {
            fprintf(stderr, "Problem przy tworzeniu wątku!");
        }
    }
    pthread_exit(NULL);
}