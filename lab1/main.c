/**
 * Author:    Nivardo Albuquerque Leitão de Castro
 * Created:   13.09.2021
 * 
 **/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define OUTPUT_SIZE 30
#define CYCLE_FRENQUENCY 3


// --- Prototypes ---
void *fill_char_array (void *arg);
// ------------------

// --- Globals --- 
pthread_t threads[CYCLE_FRENQUENCY];
int thread_args [CYCLE_FRENQUENCY];
char output[OUTPUT_SIZE];
// ---------------

void *fill_char_array (void *arg) {

    int offset = *((int *)arg);
    char symbol = offset + 64;

    printf("Starting thread %d with symbol %c \n",offset,symbol);

    for (int idx = offset-1; idx < OUTPUT_SIZE; idx+=CYCLE_FRENQUENCY)
    {
        output[idx] = symbol;
    }

}

int main (){

    for (int thread_number = 0; thread_number < CYCLE_FRENQUENCY; thread_number++){
            thread_args[thread_number] = thread_number+1;
            pthread_create(&threads[thread_number], NULL, fill_char_array, &thread_args[thread_number]);   

    }

    for (int thread_number = 0; thread_number < CYCLE_FRENQUENCY; thread_number++){
            pthread_join(threads[thread_number], NULL);   

    }

    printf("%s\n", output);


    exit(0);
}
