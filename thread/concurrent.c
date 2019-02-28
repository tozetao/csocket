#include <pthread.h>
#include <stdio.h>

#define NLOOP 1000

int counter;
//pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *doit(void *);

int main()
{
    pthread_t tid_a, tid_b;
    pthread_mutex_t counter;
    pthread_mutex_init(&counter, NULL);

//    pthread_create(&tid_a, NULL, doit, NULL);
//    pthread_create(&tid_b, NULL, doit, NULL);
    pthread_create(&tid_a, NULL, doit, &counter);
    pthread_create(&tid_b, NULL, doit, &counter);

    pthread_join(tid_a, NULL);
    pthread_join(tid_b, NULL);

    pthread_mutex_destroy(&counter);
    return 0;
}

// 通过互斥锁，让计数器counter能够正常累加
void *doit(void *vptr)
{
    int i, val;
    pthread_mutex_t *counter_mutex = (pthread_mutex_t *)vptr;

    for (i = 0; i < NLOOP; i++) {
        pthread_mutex_lock(counter_mutex);

        val = counter;
        printf("%ld: %d\n", pthread_self(), val);
        counter = val + 1;

        pthread_mutex_unlock(counter_mutex);
    }
    
    return NULL;
}
