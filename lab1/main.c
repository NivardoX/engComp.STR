/**
 * Author:    Nivardo Albuquerque Leitão de Castro
 * Created:   13.09.2021
 * 
 **/

#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define OUTPUT_SIZE 30
#define CYCLE_FRENQUENCY 3
#define EXPECTED "ABCABCABCABCABCABCABCABCABCABC"


// --- Prototypes ---
void *fill_char_array (void *arg);
// ------------------

// --- Globals --- 
pthread_t threads[CYCLE_FRENQUENCY];
int thread_args [CYCLE_FRENQUENCY];

int thread_flags [CYCLE_FRENQUENCY];

int cursor = 0;
char output[OUTPUT_SIZE];
// ---------------


int check_if_finished(){
    return cursor >= OUTPUT_SIZE;

}

void finish(){
    for (int thread_number = 0; thread_number < CYCLE_FRENQUENCY; thread_number++){
        thread_flags[thread_number] = 1;
    }

}

void populate_output_block_and_release_others(int self){
    
        if (check_if_finished()){
            finish();
            return;
        }

        // Chars are nothing but ints represented by ASCII table
        // 'A' + 0 = 'A'
        // 'A' + 1 = 'B'
        // ...
        output[cursor++] = self + 'A';

        thread_flags[self] = 0;

        // if is the last one the % operator will return 0 which will restart the cycle
        thread_flags[(self+1) % CYCLE_FRENQUENCY] = 1;

}

void *fill_char_array (void *arg) {

    int offset = *((int *)arg);



    printf("Starting thread %d with symbol %c \n",offset,offset + 'A');

    while (cursor < OUTPUT_SIZE) {

        while (!thread_flags[offset]);
        populate_output_block_and_release_others(offset);
    }

}

int main (){
    thread_flags[0] = 1;

    for (int thread_number = 0; thread_number < CYCLE_FRENQUENCY; thread_number++){
            thread_args[thread_number] = thread_number;
            pthread_create(&threads[thread_number], NULL, fill_char_array, &thread_args[thread_number]);   

    }

    for (int thread_number = 0; thread_number < CYCLE_FRENQUENCY; thread_number++){
            pthread_join(threads[thread_number], NULL);   

    }

    printf("%s\n", output);

    if (strcmp(output, EXPECTED) == 0) {
        printf("Correct result %s = %s\n",output,EXPECTED);
    } else {
        printf("Incorrect result %s != %s\n",output,EXPECTED);
    }

    exit(0);
}
