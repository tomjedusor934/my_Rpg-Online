#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define THREAD_COUNT 10
#define THREAD_LOOP 1000000

typedef struct test_s {
    long id;
    int count;
    struct test_s *next;
} test_t;

// Une ressource partagée sur laquelle synchroniser nos threads.
mtx_t mutex;
unsigned long counter = 0;
test_t *test = NULL;

void add_node(long id, int count) {
    printf("add_node\n");
    test_t *node = malloc(sizeof(test_t));
    node->id = id;
    node->count = count;
    node->next = test;
    test = node;
}

// Définition de la fonction sur laquelle amorcer tous nos threads.
int threadFunction(void* data) {

    //long i = *(long *) data;
    mtx_lock(&mutex);
    add_node((long) data, rand() % 100);
    mtx_unlock(&mutex);
    for( int i = 0; i<THREAD_LOOP; i++ ) {
        mtx_lock( &mutex );
        counter ++;
        mtx_unlock( &mutex );
    }

    printf( "Thread %ld terminé\n", (long) data );

    return thrd_success;
}

int main() {

    mtx_init( &mutex, mtx_plain );

    // On démarre tous nos threads sur la fonction définie ci-dessus.
    thrd_t threads[THREAD_COUNT];
    for( long i=0; i<THREAD_COUNT; i++ ) {
        // long *a = malloc(sizeof(long));
        // *a = i;
        thrd_create( &threads[i], threadFunction, (long *)i );
    }

    // On attend la terminaison de tous nos threads.
    for( int i=0; i<THREAD_COUNT; i++ ) {
        thrd_join( threads[i], NULL );
    }

    // Affichage du compteur et libération du mutex.
    printf( "Counter == %ld\n", counter );
    mtx_destroy( &mutex );
    while(test) {
        printf("id: %ld, count: %d\n", test->id, test->count);
        test = test->next;
    }
    return EXIT_SUCCESS;
}