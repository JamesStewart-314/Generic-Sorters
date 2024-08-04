#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#elif __unix__ || __unix || __linux__ || __APPLE__ && __MACH__
    #include <pthread.h>
#else
    // Unknown OS
#endif

#ifndef GENERICSORTERS_H
#define GENERICSORTERS_H

typedef int integerNumericalValue;
typedef int (*compareFunctionGenSort)(void* data1, void* data2);
typedef void (*sortingFunctionSignature)(compareFunctionGenSort, void*, uint64_t, uint64_t);

void gBubbleSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gShakerSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gInsertionSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gBinaryInsertionSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gSelectionSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gDoubleSelectionSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);

void gCombSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gShellSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gMergeSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gQuickSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gHeapSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);

void radixLSDSort(integerNumericalValue* arrayPointer, uint64_t arraySize);

void gBogoSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gGoodEnough(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gStoogeSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);
void gSurpriseSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize);

void sleepSort(unsigned int *arrayPointer, uint64_t arraySize);

#endif
