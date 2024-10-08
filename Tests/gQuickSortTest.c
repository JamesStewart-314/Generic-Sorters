#include "../genSorters.h"

#define ARRAY_SIZE 100

// Compilation Command: gcc gQuickSortTest.c ../genSorters.c -o executableProgram -I ../
// -O / -O2 / -O3 

typedef struct {
    char* name;
    unsigned int id;
} Person;


void impressFPerson(void* data);
int compareFPerson(void* data1, void* data2);
void destroyFPerson(void* data);
int compareFIntegers(void* data1, void* data2);
Person createPerson(char* name, unsigned int id); // Function determined to speed up the process of creating persons.
char* getRandomName();
unsigned int getRandomID();


int main(int argc, char** argv) {

    srand((unsigned int)time(NULL));
    
    clock_t myBenchmarkInitialTime, myBenchmarkEndTime, CLibraryBenchmarkInitialTime, CLibraryBenchmarkEndTime;
    double myTimeSpent, CLibraryTimeSpent;

    int random_numbers[ARRAY_SIZE];

    
    // Inserting random values in the array:
    for (int i = 0; i < ARRAY_SIZE; i++) {
        random_numbers[i] = rand() % 10;
    }
    
    
    puts("Array of Integers Generated Before Sorting:\n");
    printf("[");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d, ", random_numbers[i]);
    }
    printf("\b\b]");
    
    

    myBenchmarkInitialTime = clock();
    gQuickSort(compareFIntegers, random_numbers, (uint64_t)ARRAY_SIZE, (uint64_t)sizeof(int));
    myBenchmarkEndTime = clock();

    myTimeSpent = (double)(myBenchmarkEndTime - myBenchmarkInitialTime) / CLOCKS_PER_SEC;

    
    puts("\n\n\nArray of Integers Generated After Sorting:\n");
    printf("[");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d, ", random_numbers[i]);
    }
    printf("\b\b]\n");
    
    

    // Inserting random values in the array:
    for (int i = 0; i < ARRAY_SIZE; i++) {
        random_numbers[i] = rand() % 100;
    }

    CLibraryBenchmarkInitialTime = clock();
    qsort(random_numbers, ARRAY_SIZE, sizeof(int), compareFIntegers);
    CLibraryBenchmarkEndTime = clock();

    CLibraryTimeSpent = (double)(CLibraryBenchmarkEndTime - CLibraryBenchmarkInitialTime) / CLOCKS_PER_SEC;

    printf("\n* Time Used to Sort the Integers Array Containing %d Elements with my Sorting Algorithm: %.5lf\n", ARRAY_SIZE, myTimeSpent);
    printf("\n* Time Used to Sort the Integers Array Containing %d Elements with C Library Sorting Algorithm: %.5lf\n", ARRAY_SIZE, CLibraryTimeSpent);

    printf("\n[ Ratio Between my Time and C Library Time: %.5lf ]\n", myTimeSpent / CLibraryTimeSpent);

    
    Person personArray[ARRAY_SIZE];
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        char* name = getRandomName();
        unsigned int id = getRandomID();
        personArray[i] = createPerson(name, id);
    }

    /*
    puts("\n\n\nArray of Persons Generated Before Sorting:");
    printf("\n[");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        impressFPerson(personArray + i);
        printf(", ");
    }
    printf("\b\b]\n");
    */
    

    myBenchmarkInitialTime = clock();
    gQuickSort(compareFPerson, personArray, (uint64_t)ARRAY_SIZE, (uint64_t)(sizeof(Person)));
    myBenchmarkEndTime = clock();

    myTimeSpent = (double)(myBenchmarkEndTime - myBenchmarkInitialTime) / CLOCKS_PER_SEC;

    for (int i = 0; i < ARRAY_SIZE; i++) destroyFPerson(personArray + i);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        char* name = getRandomName();
        unsigned int id = getRandomID();
        personArray[i] = createPerson(name, id);
    }

    CLibraryBenchmarkInitialTime = clock();
    qsort(personArray, (uint64_t)ARRAY_SIZE, (uint64_t)(sizeof(Person)), compareFPerson);
    CLibraryBenchmarkEndTime = clock();

    CLibraryTimeSpent = (double)(CLibraryBenchmarkEndTime - CLibraryBenchmarkInitialTime) / CLOCKS_PER_SEC;

    /*
    puts("\n\n\nArray of Persons Generated After Sorting:");
    printf("\n[");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        impressFPerson(personArray + i);
        printf(", ");
    }
    printf("\b\b]\n");
    */

    printf("\n* Time Used to Sort the Persons Array Containing %d Elements with my Sorting Algorithm: %.5lf\n", ARRAY_SIZE, myTimeSpent);
    printf("\n* Time Used to Sort the Persons Array Containing %d Elements with C Library Sorting Algorithm: %.5lf\n", ARRAY_SIZE, CLibraryTimeSpent);

    printf("\n[ Ratio Between my Time and C Library Time: %.5lf ]\n\n", myTimeSpent / CLibraryTimeSpent);

    printf("\n( Trust me bro, it's sorted... You don't want to see %ik array items in your terminal, do you...? ;) )", ARRAY_SIZE / 1000);

    puts("\nProgram Finished. Thanks for Using!");

    for (int i = 0; i < ARRAY_SIZE; i++) destroyFPerson(personArray + i);

    return 0;
}


void impressFPerson(void* data) {
    if (!data) return;

    Person* originalPerson = (Person *)data;
    printf("Person(%s, %u)", (originalPerson->name != NULL) ? originalPerson->name : "NULL", originalPerson->id);

    return;
}


int compareFPerson(void* data1, void* data2) {
    if (!data1 || !data2) {
        if (!data1 && !data2) return 0;     // Both pointers are NULL
        return (data1 == NULL) ? (-1) : 1;  // At least one pointer is NULL. The smallest is the NULL pointer.
    }

    // Pointer casting:
    Person* aux1 = (Person *)data1;
    Person* aux2 = (Person *)data2;

    do {
        if (!(aux1->name) || !(aux2->name)) {
            // At least one of the names is NULL:

            // Both are null and, consequently, equal. 
            // Ending the loop and proceeding to compare the IDs:
            if (!(aux1->name) && !(aux2->name)) break; 

            return (aux1->name == NULL) ? (-1) : 1;
        } else {
            int nameComparisonResult = strcmp(aux1->name, aux2->name);
            if (nameComparisonResult != 0) return nameComparisonResult;
            break;
        }
    } while(false);

    // Comparison of IDs if the names are the same or both are NULL:
    if (aux1->id > aux2->id) return 1;
    if (aux1->id < aux2->id) return -1;

    return 0;
}


void destroyFPerson(void* data) {
    if (!data) return;

    // Deallocating the memory reserved for the name:
    if(((Person *)data)->name) free(((Person *)data)->name);
    //free(data); data = NULL;

    return;
}


Person createPerson(char* name, unsigned int id) {
    Person* newPerson = (Person *) malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Error: Failed while trying to allocate memory for a new Person.\n");
        exit(EXIT_FAILURE);
    }

    newPerson->id = id;
    if (name == NULL) { newPerson->name = NULL; return *newPerson; }
    // debbuging:
    // printf("Name Size: %d\n", strlen(name) + 1);
    newPerson->name = (char *) malloc(strlen(name) + 1);
    strcpy(newPerson->name, name);

    Person aux = *newPerson;

    free(newPerson);

    return aux;
}


int compareFIntegers(void* data1, void* data2) {
    if (!data1 || !data2) {
        if (!data1 && !data2) return 0;
        return (data1 == NULL) ? (-1) : 1;
    }

    int aux1 = *(int *)data1;
    int aux2 = *(int *)data2;

    if (aux1 > aux2) return 1;
    if (aux1 < aux2) return -1;

    return 0;
}


char* getRandomName() {
    char* names[] = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Henry", "Ivy", "Jack"};
    int numNames = sizeof(names) / sizeof(names[0]);
    int index = rand() % numNames;
    return names[index];
}


unsigned int getRandomID() {
    return rand() % 1000 + 1; // IDs entre 1 e 1000
}