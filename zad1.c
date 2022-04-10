#include <pthread.h>
#include <sys/fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void printSthg(pthread_mutex_t* console_mutex){
    unsigned long now = (unsigned long) time(NULL);
    sleep(1); 
    unsigned long now2 = (unsigned long) time(NULL);
    pthread_mutex_lock(console_mutex);
    printf("SECONDS: %lu \n", now2 - now);
     // iskam da zakliucha i shte 
     // go napravq v pyrviq moment v kojto e otkliucheno
    for(int i=0;i<10;i++){
        printf("%d", i);
    }
    pthread_mutex_unlock(console_mutex);
    printf("\n");
}

int main(int argc, char** argv){
    uint32_t N = 1;
    sscanf(argv[1], "%d", &N);
    pthread_t *threads;
    pthread_mutex_t console_mutex;
    pthread_mutex_init(&console_mutex, NULL);
    for(int i=0;i<argc; i++)
        printf("argv[%d]: %s\n", i, argv[i]);

    threads = (pthread_t *)malloc(N * sizeof(pthread_t*));
    for(int i=0;i<N;i++){
        pthread_create(threads + i, NULL, (void *) printSthg, (void *)&console_mutex);
    }
    for(int i=0;i<N;i++){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&console_mutex);
    free(threads);
    return 0;
}