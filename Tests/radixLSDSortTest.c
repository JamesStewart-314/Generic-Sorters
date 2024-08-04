#include "../genSorters.h"

#define ARRAY_SIZE 1000

// Compilation Command: gcc radixLSDSortTest.c ../genSorters.c -o executableProgram -I ../

int main(int argc, char** argv) {

    srand((unsigned int)time(NULL));
    
    clock_t benchmarkInitialTime, benchmarkEndTime;
    double timeSpent;

    unsigned int random_numbers[ARRAY_SIZE];

    
    // Inserting random values in the array:
    for (int i = 0; i < ARRAY_SIZE; i++) {
        random_numbers[i] = rand() % 100 - 50;
    }
    
    
    puts("Array of Integers Generated Before Sorting:\n");
    printf("[");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d, ", random_numbers[i]);
    }
    printf("\b\b]");
    
    
    benchmarkInitialTime = clock();
    radixLSDSort(random_numbers, (uint64_t)ARRAY_SIZE);
    benchmarkEndTime = clock();

    timeSpent = (double)(benchmarkEndTime - benchmarkInitialTime) / CLOCKS_PER_SEC;

    
    puts("\n\n\nArray of Integers Generated After Sorting:\n");
    printf("[");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d, ", random_numbers[i]);
    }
    printf("\b\b]\n");
    

    printf("\n* Time Used to Sort the Integers Array Containing %d Elements: %.2lf\n", ARRAY_SIZE, timeSpent);

    puts("\nProgram Finished. Thanks for Using!");    

    return 0;
}
