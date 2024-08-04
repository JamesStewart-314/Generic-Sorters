#include "genSorters.h"

void gSwapVariables(void* variableA, void* variableB, uint64_t variableSize) {

    // Function used to swap the content of two variables of any type.
    // The main idea is to swap each byte of the variables, that is, 
    // swap each 8-bit block until all bytes of both variables have 
    // their contents swapped.

    int8_t tempContentSwapper;

    // Casting the pointers to 1 byte-pointers:
    int8_t* auxVariableA = (int8_t *)variableA;
    int8_t* auxVariableB = (int8_t *)variableB;

    // Swapping the content of the variables:
    while ((variableSize--) > 0) {
        tempContentSwapper = *auxVariableA;
        *auxVariableA = *auxVariableB;
        *auxVariableB = tempContentSwapper;

        // Advancing to the next 8 bytes of both variables:
        auxVariableA++;
        auxVariableB++;
    }

    return;
}

/*
void gSwapVariables(void* variableA, void* variableB, uint64_t variableSize) {
    void* auxVariable = malloc(variableSize);
    memcpy(auxVariable, variableA, variableSize);
    memcpy(variableA, variableB, variableSize);
    memcpy(variableB, auxVariable, variableSize);
    free(auxVariable);

    return;
}
*/


void* gBinarySearch(compareFunctionGenSort compareF, void* desiredElement, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!compareF || !arrayPointer || dataSize == 0 || arraySize <= 0) return NULL;

    // Trivial case:
    if (arraySize == 1) return compareF(arrayPointer, desiredElement) == 0 ? arrayPointer : NULL;

    uint64_t halfArraySize = arraySize / 2;
    uint64_t halfArrayIndex = arraySize % 2 == 0 ? halfArraySize - 1 : halfArraySize;

    void* middleElement = arrayPointer + dataSize * halfArrayIndex;
    int comparisonResult = compareF(desiredElement, middleElement);

    if (comparisonResult < 0) return gBinarySearch(compareF, desiredElement, arrayPointer, arraySize - halfArraySize - 1, dataSize);
    if (comparisonResult > 0) return gBinarySearch(compareF, desiredElement, middleElement + dataSize, arraySize - halfArrayIndex - 1, dataSize);

    // comparisonResult == 0 => Element Found:
    return middleElement;
}


void* gInsertionSortBinarySearch(compareFunctionGenSort compareF, void* desiredElement, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!compareF || !arrayPointer || dataSize == 0 || arraySize <= 1) return arrayPointer;

    uint64_t halfArraySize = arraySize / 2;
    uint64_t halfArrayIndex = arraySize % 2 == 0 ? halfArraySize - 1 : halfArraySize;

    void* middleElement = arrayPointer + dataSize * halfArrayIndex;
    int comparisonResult = compareF(desiredElement, middleElement);

    if (comparisonResult < 0) return gInsertionSortBinarySearch(compareF, desiredElement, arrayPointer, arraySize - halfArraySize - 1, dataSize);
    if (comparisonResult > 0) return gInsertionSortBinarySearch(compareF, desiredElement, middleElement + dataSize, arraySize - halfArrayIndex - 1, dataSize);

    // comparisonResult == 0 => Element Found:
    return middleElement;
}


void gMergeArrays(compareFunctionGenSort compareF, void* startPointer, void* endPointer, uint64_t dataSize) {
    if (!startPointer || !endPointer || !compareF) return;

    uint64_t arraySize = ((endPointer - startPointer) / dataSize) + 1;

    void* auxMergeArray = malloc(arraySize * dataSize);
    void* auxMergeArrayTempPointer = auxMergeArray;
    if (auxMergeArray == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory for the auxiliar array in generic Merge Sort.\n");
        return;
    }

    int comparisonResult;

    void* middlePointer = startPointer + (arraySize / 2) * dataSize;

    void *auxPointer1 = startPointer, *auxPointer2 = middlePointer;
    while ((auxPointer1 < middlePointer) && (auxPointer2 <= endPointer)) {
        comparisonResult = compareF(auxPointer1, auxPointer2);

        if (comparisonResult < 0) {
            gSwapVariables(auxMergeArrayTempPointer, auxPointer1, dataSize);
            auxMergeArrayTempPointer += dataSize;
            auxPointer1 += dataSize;
            continue;
        }

        if (comparisonResult > 0) {
            gSwapVariables(auxMergeArrayTempPointer, auxPointer2, dataSize);
            auxMergeArrayTempPointer += dataSize;
            auxPointer2 += dataSize;
            continue;
        }

        // Comparison result == 0:
        gSwapVariables(auxMergeArrayTempPointer, auxPointer1, dataSize);
        auxMergeArrayTempPointer += dataSize;
        gSwapVariables(auxMergeArrayTempPointer, auxPointer2, dataSize);
        auxMergeArrayTempPointer += dataSize;
        
        auxPointer1 += dataSize;
        auxPointer2 += dataSize;
    }

    // Copying potentially remaining elements from the first half of the array:
    while (auxPointer1 < middlePointer) {
        gSwapVariables(auxMergeArrayTempPointer, auxPointer1, dataSize);
        auxMergeArrayTempPointer += dataSize;
        auxPointer1 += dataSize;
    }

    // Copying potentially remaining elements from the second half of the array:
    while (auxPointer2 <= endPointer) {
        gSwapVariables(auxMergeArrayTempPointer, auxPointer2, dataSize);
        auxMergeArrayTempPointer += dataSize;
        auxPointer2 += dataSize;
    }

    // Transferring the contents of the auxiliary array to the original array:
    auxMergeArrayTempPointer = auxMergeArray;
    while (arraySize > 0) {
        gSwapVariables(auxMergeArrayTempPointer, startPointer, dataSize);
        auxMergeArrayTempPointer += dataSize;
        startPointer += dataSize;
        arraySize--;
    }

    free(auxMergeArray);

    return;
}


void gRecursiveMergeSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    uint64_t halfArraySize = arraySize / 2;

    gRecursiveMergeSort(compareF, arrayPointer, halfArraySize, dataSize);
    gRecursiveMergeSort(compareF, arrayPointer + dataSize * halfArraySize, arraySize - halfArraySize, dataSize);

    gMergeArrays(compareF, arrayPointer, arrayPointer + dataSize * (arraySize - 1), dataSize);

    return;
}


void gRecursiveQuickSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    //if (!arrayPointer) return;

    if (arraySize < 2) return;
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    /* Strategically choosing the pivot based on the median between the first, last and central element of the array.
     This technique, known as "median of three", helps reduce the likelihood of unbalanced partitions, which can lead 
     to poor algorithm performance — O(n²) case. By using the median of these three elements, we increase the chance of 
     obtaining a pivot closer to the central value, promoting more balanced partitions and substantially improving the 
     overall efficiency of Quicksort.
    */
    
    /*
    uint64_t medianIndex = arraySize / 2;

    void* startPointer = arrayPointer;
    void* medianPointer = arrayPointer + dataSize * medianIndex;
    void* endPointer = arrayPointer + dataSize * (arraySize - 1);
    
    if (compareF(startPointer, medianPointer) >= 0) gSwapVariables(startPointer, medianPointer, dataSize);
    if (compareF(medianPointer, endPointer) >= 0) gSwapVariables(medianPointer, endPointer, dataSize);
    if (compareF(startPointer, medianPointer) >= 0) gSwapVariables(startPointer, medianPointer, dataSize);

    if (arraySize == 3) return;

    // Ensuring that the best pivot of the median between the first, 
    // last and middle elements of the array is at the end of the array:
    gSwapVariables(medianPointer, endPointer, dataSize);
    */
    
    // Choosing the last element of the array to be the pivot:
    void* pivotPointer = arrayPointer + dataSize * (arraySize - 1);

    void* auxIndexI = arrayPointer;
    void* auxIndexJ = arrayPointer + (arraySize - 2) * dataSize;

    while (compareF(auxIndexI, pivotPointer) <= 0 && auxIndexI < auxIndexJ) auxIndexI += dataSize;
    while (compareF(auxIndexJ, pivotPointer) > 0 && auxIndexI < auxIndexJ) auxIndexJ -= dataSize;

    while (auxIndexI < auxIndexJ) {
        gSwapVariables(auxIndexI, auxIndexJ, dataSize);
        while (compareF(auxIndexI, pivotPointer) <= 0) auxIndexI += dataSize;
        while (compareF(auxIndexJ, pivotPointer) > 0) auxIndexJ -= dataSize;
    }

    if (compareF(auxIndexI, pivotPointer) >= 0) gSwapVariables(auxIndexI, pivotPointer, dataSize);

    uint64_t auxIndexIFinalIndex = (uint64_t)(auxIndexI - arrayPointer) / dataSize;

    gRecursiveQuickSort(compareF, arrayPointer, auxIndexIFinalIndex + 1, dataSize);
    gRecursiveQuickSort(compareF, auxIndexI, arraySize - auxIndexIFinalIndex, dataSize);

    return;  
}


void gHeapfy(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize, uint64_t index, bool doMaxHeap) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Heapfy if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Heapfy function cannot be zero.\n");
        return;
    }

    // doMaxHeap parameter: if true => Make a MaxHeap; else => Make a MinHeap:

    void* elementPointer = arrayPointer + dataSize * index;

    void* swapSonPointer = elementPointer;
    
    uint64_t leftSon = 2 * index + 1;
    uint64_t rightSon = 2 * index + 2;

    void* leftSonPointer = arrayPointer + dataSize * leftSon;
    void* rightSonPointer = arrayPointer + dataSize * rightSon;

    if (doMaxHeap) {
        // MaxHeap:
        if (leftSon < arraySize && compareF(leftSonPointer, swapSonPointer) > 0) swapSonPointer = leftSonPointer;
        if (rightSon < arraySize && compareF(rightSonPointer, swapSonPointer) > 0) swapSonPointer = rightSonPointer;
    } else {
        // MinHeap:
        if (leftSon < arraySize && compareF(leftSonPointer, swapSonPointer) < 0) swapSonPointer = leftSonPointer;
        if (rightSon < arraySize && compareF(rightSonPointer, swapSonPointer) < 0) swapSonPointer = rightSonPointer;
    }

    if (swapSonPointer == elementPointer) return;

    gSwapVariables(elementPointer, swapSonPointer, dataSize);

    if (swapSonPointer == leftSonPointer) gHeapfy(compareF, arrayPointer, arraySize, dataSize, leftSon, doMaxHeap);
    else gHeapfy(compareF, arrayPointer, arraySize, dataSize, rightSon, doMaxHeap);
    
    return;
}


void gBubbleSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Bubble Sort if the Array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Bubble Sort function cannot be zero.\n");
        return;
    }

    // Trivial Case:
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    bool changeMade = false;
    int comparisonResult;

    for (void* endPointer = arrayPointer + dataSize * (arraySize - 1); endPointer > arrayPointer; endPointer -= dataSize) {
        changeMade = false;

        for (void* auxPointer = arrayPointer; auxPointer < endPointer; auxPointer += dataSize) {
            comparisonResult = compareF(auxPointer, auxPointer + dataSize);
            
            if (comparisonResult > 0) {
                gSwapVariables(auxPointer, auxPointer + dataSize, dataSize);
                changeMade = true;
            }
        }

        if (changeMade == false) return;
    }

    return;
}


void gShakerSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Shaker Sort if the Array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Shaker Sort function cannot be zero.\n");
        return;
    }

    // Trivial Case:
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    bool changeMade = false;
    int comparisonResult;

    void *startPointer = arrayPointer, *endPointer = arrayPointer + dataSize * (arraySize - 1);
    void* shakerPointer = arrayPointer;
    while (startPointer < endPointer) {
        while (shakerPointer < endPointer) {
            if (compareF(shakerPointer, shakerPointer + dataSize) > 0) gSwapVariables(shakerPointer, shakerPointer + dataSize, dataSize);
            shakerPointer += dataSize;
        }
        endPointer -= dataSize;
        shakerPointer = endPointer;

        while (shakerPointer > startPointer) {
            if (compareF(shakerPointer, shakerPointer - dataSize) < 0) gSwapVariables(shakerPointer, shakerPointer - dataSize, dataSize);
            shakerPointer -= dataSize;
        }
        startPointer += dataSize;
        shakerPointer = startPointer;        
    }

    return;
}


void gInsertionSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Insertion Sort to array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Merge Sort function cannot be zero.\n");
        return;
    }

    // Trivial Case:
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    int comparisonResult;
    void* auxInsertionPointer;
    void* endPointer = arrayPointer + dataSize * arraySize;

    for (void* auxPointer = arrayPointer + dataSize; auxPointer < endPointer; auxPointer += dataSize) {
        comparisonResult = compareF(auxPointer, auxPointer - dataSize);

        if (comparisonResult >= 0) continue;

        auxInsertionPointer = auxPointer;

        while (auxInsertionPointer > arrayPointer && comparisonResult < 0) {
            gSwapVariables(auxInsertionPointer, auxInsertionPointer - dataSize, dataSize);
            auxInsertionPointer -= dataSize;

            if (auxInsertionPointer != arrayPointer) comparisonResult = compareF(auxInsertionPointer, auxInsertionPointer - dataSize);
            else break;
        }
    }

    return;
}


void gBinaryInsertionSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Insertion Sort to array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Merge Sort function cannot be zero.\n");
        return;
    }

    // Trivial Case:
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    void* auxSwapPlace = malloc(dataSize);
    if (auxSwapPlace == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory for auxiliar swap variable in generic Binary Insertion Sort.\n");
        return;
    }

    int comparisonResult;
    void* endPointer = arrayPointer + dataSize * arraySize;
    uint64_t subArraySize = 1;

    for (void* auxPointer = arrayPointer + dataSize; auxPointer < endPointer; auxPointer += dataSize) {
        void* finalDestination = gInsertionSortBinarySearch(compareF, auxPointer, arrayPointer, subArraySize++, dataSize);
        comparisonResult = compareF(auxPointer, finalDestination);

        if (finalDestination == auxPointer - dataSize) {
            if (comparisonResult < 0) gSwapVariables(auxPointer, finalDestination, dataSize);
            continue;
        }

        // Saving the value on auxPointer address:
        gSwapVariables(auxSwapPlace, auxPointer, dataSize);

        // Shiffting all elements to the right until open space for the auxPointer variable:
        finalDestination = comparisonResult < 0 ? finalDestination : finalDestination + dataSize;
        void* shifftingPlacesPointer = auxPointer - dataSize;
        while (finalDestination <= shifftingPlacesPointer) {
            gSwapVariables(shifftingPlacesPointer, shifftingPlacesPointer + dataSize, dataSize);
            shifftingPlacesPointer -= dataSize;
        }

        shifftingPlacesPointer += dataSize;
        gSwapVariables(shifftingPlacesPointer, auxSwapPlace, dataSize);
    }

    free(auxSwapPlace);

    return;
    
}


void gSelectionSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Selection Sort to array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Selection Sort function cannot be zero.\n");
        return;
    }

    // Trivial Case:
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    void* smallestElement;
    void* endPointer = arrayPointer + dataSize * arraySize;
    for (void* auxPointer = arrayPointer; auxPointer < endPointer; auxPointer += dataSize) {
        smallestElement = auxPointer;

        for (void* tempPointer = auxPointer + dataSize; tempPointer < endPointer; tempPointer += dataSize) {
            if (compareF(tempPointer, smallestElement) < 0) smallestElement = tempPointer;
        }

        gSwapVariables(auxPointer, smallestElement, dataSize);
    }

    return;
}


void gDoubleSelectionSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Double Selection Sort to array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Double Selection Sort function cannot be zero.\n");
        return;
    }

    // Trivial Case:
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    void *smallestElement, *biggestElement;
    void *startPointer = arrayPointer, *endPointer = arrayPointer + dataSize * (arraySize - 1);
    while (startPointer < endPointer) {
        smallestElement = startPointer;
        biggestElement = endPointer;

        for (void* tempPointer = startPointer; tempPointer <= endPointer; tempPointer += dataSize) {
            if (compareF(tempPointer, smallestElement) < 0) smallestElement = tempPointer;
            if (compareF(tempPointer, biggestElement) > 0) biggestElement = tempPointer;
        }

        if (smallestElement != endPointer && biggestElement != startPointer) {
            gSwapVariables(startPointer, smallestElement, dataSize);
            gSwapVariables(endPointer, biggestElement, dataSize);
        } else {
            if (smallestElement == endPointer && biggestElement != startPointer) {
                gSwapVariables(startPointer, smallestElement, dataSize);
                gSwapVariables(endPointer, biggestElement, dataSize);
            } else if (smallestElement != endPointer && biggestElement == startPointer) {
                gSwapVariables(endPointer, biggestElement, dataSize);
                gSwapVariables(startPointer, smallestElement, dataSize);
            } else {
                // smallestElement == endPointer && biggestElement == startPointer:
                gSwapVariables(startPointer, endPointer, dataSize);
            }
        }

        startPointer += dataSize;
        endPointer -= dataSize;
    }

    return;
}


void gCombSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Comb Sort to array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Comb Sort function cannot be zero.\n");
        return;
    }

    // Trivial Case:
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    uint64_t gapSize = arraySize - 1, newGapSize;
    void *currentElement, *currentElementWithGap;
    uint64_t currentIndex;
    bool changeMade;
    while (true) {
        changeMade = false;
        currentIndex = 0;

        while (currentIndex + gapSize < arraySize) {
            currentElement = arrayPointer + (currentIndex++) * dataSize;
            currentElementWithGap = currentElement + gapSize * dataSize;
            if (compareF(currentElement, currentElementWithGap) > 0) {
                gSwapVariables(currentElement, currentElementWithGap, dataSize);
                changeMade = true;
            }
        }

        if (gapSize == 1 && !changeMade) return;

        // Shortening the gapSize by a factor of 1.3:
        if (gapSize > 1) {
            newGapSize = (uint64_t)(gapSize / 1.3);
            gapSize = newGapSize > 1 ? newGapSize : 1;
        }        
    }
}


void gShellSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Shell Sort to array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Shell Sort function cannot be zero.\n");
        return;
    }

    // Trivial Case:
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    bool gapSize1Done = false;
    double shrinkFactor = 2.25;
    void* endPointer = arrayPointer + dataSize * arraySize;
    uint64_t gapSize = (uint64_t)(arraySize / shrinkFactor);
    void* auxInsertionPointer;

    while (gapSize > 0) {
        for (void* auxPointer = arrayPointer; auxPointer < endPointer; auxPointer += dataSize) {
            for (void* tempPointer = auxPointer + dataSize * gapSize; tempPointer < endPointer; tempPointer += dataSize * gapSize) {
                auxInsertionPointer = tempPointer;
                while (auxInsertionPointer > auxPointer && compareF(auxInsertionPointer, auxInsertionPointer - dataSize * gapSize) < 0) {
                    gSwapVariables(auxInsertionPointer, auxInsertionPointer - dataSize * gapSize, dataSize);
                    auxInsertionPointer -= dataSize * gapSize;
                }
            }
        }
        if (gapSize == 1) gapSize1Done = true;

        gapSize = (uint64_t)(gapSize / shrinkFactor);
    }

    if (gapSize1Done) return;

    // Insertion Sort:
    for (void* insertionSortPointer = arrayPointer + dataSize; insertionSortPointer < endPointer; insertionSortPointer += dataSize) {
        auxInsertionPointer = insertionSortPointer;
        while (auxInsertionPointer > arrayPointer && compareF(auxInsertionPointer, auxInsertionPointer - dataSize) < 0) {
            gSwapVariables(auxInsertionPointer, auxInsertionPointer - dataSize, dataSize);
            auxInsertionPointer -= dataSize;
        }
    }
    

    return;
}


void gMergeSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Merge Sort to array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Merge Sort function cannot be zero.\n");
        return;
    }

    // Trivial Case:
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    gRecursiveMergeSort(compareF, arrayPointer, arraySize, dataSize);

    return;
}


void gQuickSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Quick Sort to array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Quick Sort function cannot be zero.\n");
        return;
    }

    // Trivial Case:
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    gRecursiveQuickSort(compareF, arrayPointer, arraySize, dataSize);

    return;
}

void gHeapSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Heap Sort to array if comparison function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Heap Sort function cannot be zero.\n");
        return;
    }

    // Trivial Case:
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    // It is only necessary to apply the heapfy algorithm to half of the array:
    for (uint64_t i = arraySize / 2; i > 0; i--) gHeapfy(compareF, arrayPointer, arraySize, dataSize, i, true);
    gHeapfy(compareF, arrayPointer, arraySize, dataSize, 0, true);

    for (uint64_t i = arraySize - 1; i > 0; i--) {
        gSwapVariables(arrayPointer, arrayPointer + dataSize * i, dataSize);
        gHeapfy(compareF, arrayPointer, i, dataSize, 0, true);
    }
}


unsigned int getDigitFromNumber(int64_t value, unsigned int digit) {
    if (value == 0) return 0;
    if (value < 0) value *= (-1);

    unsigned int tenPower = (unsigned int)pow(10, digit);

    return (unsigned int)((value % tenPower) / (tenPower / 10));
}


unsigned int getQuantityOfDigits(int64_t value) {
    if (value == 0) return 1;
    if (value < 0) value *= (-1);

    return (unsigned int)(log10((double)value)) + 1;
}


void radixLSDSortDigit(integerNumericalValue *arrayPointer, uint64_t arraySize, unsigned int decimalPlace, integerNumericalValue *auxiliarArray, bool ascendingOrder) {
    integerNumericalValue* digitsPointer[10];

    // Array to count the digits from 0 to 9:
    int digitCounting[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Copying values to the auxiliar array:
    for (uint64_t index = 0; index < arraySize; index++) {
        auxiliarArray[index] = arrayPointer[index];        
        // Incrementing the digit counter variable:
        digitCounting[getDigitFromNumber(arrayPointer[index], decimalPlace)]++;
    }

    uint64_t totalSumDigits = 0;
    if (ascendingOrder) {
        for (short digits = 0; digits < 10; digits++) {
            digitsPointer[digits] = arrayPointer + totalSumDigits;
            totalSumDigits += digitCounting[digits];
        }

        for (uint64_t index = 0; index < arraySize; index++) {
            *(digitsPointer[getDigitFromNumber(auxiliarArray[index], decimalPlace)]++) = auxiliarArray[index];
        }

    } else {
        for (short digits = 9; digits >= 0; digits--) {
            digitsPointer[digits] = arrayPointer + totalSumDigits;
            totalSumDigits += digitCounting[digits];
        }

        for (uint64_t index = 0; index < arraySize; index++) {
            *(digitsPointer[getDigitFromNumber(auxiliarArray[index], decimalPlace)]++) = auxiliarArray[index];
        }
    }

    return;
}

void radixLSDSort(integerNumericalValue* arrayPointer, uint64_t arraySize) {
    if (!arrayPointer || arraySize < 2) return;

    integerNumericalValue* auxiliarArray = (integerNumericalValue *) malloc(sizeof(integerNumericalValue) * arraySize);
    if (auxiliarArray == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory for auxiliar array in radix LSDSort.\n");
        return;
    }

    // Trivial Case:
    if (arraySize == 2) {
        if (*arrayPointer > *(arrayPointer + 1)) gSwapVariables(arrayPointer, arrayPointer + 1, sizeof(integerNumericalValue));
        return;
    }

    // Separating all negative and positive numbers from the 
    // array on the left and right sides respectively:
    integerNumericalValue *startPointer = arrayPointer, *endPointer = arrayPointer + arraySize - 1;
    integerNumericalValue *auxStartPointer = startPointer, *auxEndPointer = endPointer;

    while (auxStartPointer < auxEndPointer && *auxStartPointer < 0) auxStartPointer++;
    while (auxStartPointer < auxEndPointer && *auxEndPointer >= 0) auxEndPointer--;    
    
    while (auxStartPointer < auxEndPointer) {
        gSwapVariables(auxStartPointer, auxEndPointer, sizeof(integerNumericalValue));

        while (auxStartPointer < auxEndPointer && *auxStartPointer < 0) auxStartPointer++;
        while (auxStartPointer < auxEndPointer && *auxEndPointer >= 0) auxEndPointer--;
    }

    // Calculating the final pivot stop index:
    uint64_t indexStop = ((void *)auxStartPointer - (void *)arrayPointer) / sizeof(integerNumericalValue);

    uint64_t maximumQuantityOfDigitsPositive = 1, maximumQuantityOfDigitsNegative = 1, digitsQuantity = 1;
    for (uint64_t index = 0; index < arraySize; index++) {
        digitsQuantity = getQuantityOfDigits(arrayPointer[index]);
        if (digitsQuantity > maximumQuantityOfDigitsPositive && arrayPointer[index] >= 0) maximumQuantityOfDigitsPositive = digitsQuantity;
        if (digitsQuantity > maximumQuantityOfDigitsNegative && arrayPointer[index] < 0) maximumQuantityOfDigitsNegative = digitsQuantity;
    }

    // Cases where there are only negative or positive numbers:
    if (indexStop == 0 || indexStop == (arraySize - 1)) {
        if (arrayPointer[indexStop] >= 0) {
            for (uint64_t digitIndex = 1; digitIndex <= maximumQuantityOfDigitsPositive; digitIndex++) {
                radixLSDSortDigit(arrayPointer, arraySize, digitIndex, auxiliarArray, true);
            }
        } else {
            for (uint64_t digitIndex = 1; digitIndex <= maximumQuantityOfDigitsNegative; digitIndex++) {
                radixLSDSortDigit(arrayPointer, arraySize, digitIndex, auxiliarArray, false);
            }
        }
    } else {
        for (uint64_t digitIndex = 1; digitIndex <= maximumQuantityOfDigitsNegative; digitIndex++) {
            radixLSDSortDigit(arrayPointer, indexStop + (arrayPointer[indexStop] < 0), digitIndex, auxiliarArray, false);
        }

        for (uint64_t digitIndex = 1; digitIndex <= maximumQuantityOfDigitsPositive; digitIndex++) {
            radixLSDSortDigit(arrayPointer + indexStop, arraySize - indexStop - (arrayPointer[indexStop] < 0), digitIndex, auxiliarArray, true);
        }
    }    

    free(auxiliarArray);

    return;
}

// -------------------------------------------------------------------------------------------------------------------------------------------------------- //
// -------------------------------------------------------------------------------------------------------------------------------------------------------- //
// -------------------------------------------------------------------------------------------------------------------------------------------------------- //


uint64_t getuint64tMin(uint64_t a, uint64_t b) { return (a < b) ? a : b; }

bool checkArrayIsOrdered(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return true;

    void* lastPointer = arrayPointer + dataSize * (arraySize - 1);
    while (arrayPointer < lastPointer) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) return false;
        arrayPointer += dataSize;
    }

    return true;
}


uint64_t generateRandomIndex(uint64_t start, uint64_t end) {
    if (end < start) return 0;

    srand((unsigned int)time(NULL));

    uint64_t intervalRange = end - start;

    // TODO: Improve  the generateRandomIndex function.

    if (intervalRange > RAND_MAX) {
        uint64_t offsetValue = (uint64_t)ceil((long double)intervalRange / (long double)RAND_MAX);

        // Generating previous values to clean
        // the random number generator:
        ((uint64_t)rand() * offsetValue);
        ((uint64_t)rand() % offsetValue);

        return getuint64tMin(start + ((uint64_t)rand() * offsetValue) + ((uint64_t)rand() % offsetValue), start + intervalRange);
    } else {
        // The time squared and division by 13 is just to improve the randomness:
        return ((uint64_t)rand() + (uint64_t)(time(NULL) * time(NULL)) / 13) % (intervalRange + 1) + start;
    }    
}


void gRecursiveStoogeSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (arraySize == 3) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        if (compareF(arrayPointer + dataSize, arrayPointer + 2 * dataSize) > 0) gSwapVariables(arrayPointer + dataSize, arrayPointer + 2 * dataSize, dataSize);
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    uint64_t subArraySize = (uint64_t)ceil((double_t)arraySize * 2 / 3);

    gRecursiveStoogeSort(compareF, arrayPointer, subArraySize, dataSize);
    gRecursiveStoogeSort(compareF, arrayPointer + dataSize * (arraySize - subArraySize), subArraySize, dataSize);
    gRecursiveStoogeSort(compareF, arrayPointer, subArraySize, dataSize);

    return;
}


void gBogoSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Bogo Sort to array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Bogo Sort function cannot be zero.\n");
        return;
    }

    // Randomizing the array elements:
    do {
        for (uint64_t i = arraySize - 1; i > 0; i--) {
            gSwapVariables(arrayPointer + dataSize * i, arrayPointer + dataSize * generateRandomIndex(0, i), dataSize);
        }
    } while (!checkArrayIsOrdered(compareF, arrayPointer, arraySize, dataSize));

    return;
}

void gGoodEnough(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    // hmm, ehh it's good enough...
    return;
}

void gStoogeSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Stooge Sort to array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Stooge Sort function cannot be zero.\n");
        return;
    }

    // Trivial case:
    if (arraySize == 2) {
        if (compareF(arrayPointer, arrayPointer + dataSize) > 0) gSwapVariables(arrayPointer, arrayPointer + dataSize, dataSize);
        return;
    }

    gRecursiveStoogeSort(compareF, arrayPointer, arraySize, dataSize);

    return;
}


#ifdef _WIN32
    // Defines a critical section variable to avoid conflicts:
    CRITICAL_SECTION criticalSection;

    // Variable to store the inicial address of the array:
    unsigned int* sleepSortArrayPointer = NULL;

    DWORD WINAPI sortingSleepFunction(LPVOID lpParam) {
        unsigned int data = *(unsigned int *)lpParam;
        
        //printf("Thread %ld: Sleeping by %d seconds.\n", GetCurrentThreadId(), data);
        Sleep(data * 1000);
        //printf("Thread %ld: Awake!\n", GetCurrentThreadId());

        // Synchronizing the writing stage to avoid race conditions and conflicts:
        EnterCriticalSection(&criticalSection);

        // Placing the element in correct position:
        *(sleepSortArrayPointer++) = data;

        // Leaving the synchronization step:
        LeaveCriticalSection(&criticalSection);

        return 0;            
    }

#elif __unix__ || __unix || __linux__ || __APPLE__ && __MACH__
    #include <pthread.h>
    // Not Implemented yet... ( i do not have a Linux OS to test it ;( )

#else
    // Unknown OS
    
#endif


// TODO: Finish Sleep Sort for Unix-Like OS.
void sleepSort(unsigned int* arrayPointer, uint64_t arraySize) {
    if (!arrayPointer || arraySize < 2) return;

    // Traversing the array to find out if the elements are already sorted:
    bool isOrdered = true;
    for (unsigned int* tempArrayPointer = arrayPointer; tempArrayPointer < arrayPointer + arraySize - 1; tempArrayPointer++) {
        if (*(tempArrayPointer) > *(tempArrayPointer + 1)) isOrdered = false;
    }

    if (isOrdered) return;

    // Since the array is not ordered, we will perform the following steps:

    // First, going through the entire array and
    // placing all zeros at the beginning of the array:

    unsigned int* startPivot = arrayPointer;
    unsigned int* tempPivot;
    unsigned int* endPivot = arrayPointer + arraySize;

    while (*startPivot == 0 && startPivot < endPivot) startPivot++;
    // Array filled with zeroes, just return:
    if (startPivot >= endPivot) return;

    tempPivot = startPivot;
    while (tempPivot < endPivot) {
        // Traversing the array until it finds a zero or passes the end of the array:
        while (*tempPivot != 0 || tempPivot < startPivot) tempPivot++;
        if (tempPivot >= endPivot) break;

        // Swapping the variables:
        gSwapVariables(tempPivot, startPivot, sizeof(unsigned int));

        // Relocating the startPointer to point to another non-zero element:
        while (*startPivot == 0 && startPivot < endPivot) startPivot++;
        if (startPivot >= endPivot) return;
    }

    /*
    
    Now comes the difficult part... In this section, I will use a array 
    of threads to work individually with each element of the integers array 
    that is non-zero. Each thread will wait an arbitrary number of seconds 
    corresponding to the value of the array element to which it is associated. 
    After the count ends, the thread will position the element in its respective 
    sorted location in the array.

    As different operating systems deal with threads in their native APIs 
    in different ways, I will create an implementation based on the thread 
    library available in the <Windows.h> header file on the Windows platform. 
    For Unix-like operating systems, I will opt for the <pthread.h> library.
    
    */

    #ifdef _WIN32

        InitializeCriticalSection(&criticalSection);
        sleepSortArrayPointer = startPivot;

        uint64_t remainingAmountOfElements = arraySize - ((void *)startPivot - (void *)arrayPointer) / sizeof(int);
        
        HANDLE* arrayOfThreads = (HANDLE *) malloc(remainingAmountOfElements * sizeof(HANDLE));

        // Creating a thread for each element of the array:
        for (int i = 0; i < remainingAmountOfElements; i++) {
            // Creating the thread for each element of the array:
            arrayOfThreads[i] = CreateThread(
                NULL,
                0,
                sortingSleepFunction,
                startPivot + i,
                0,
                NULL
            );

            if (arrayOfThreads[i] == NULL) {
                fprintf(stderr, "Error: Error while creating Thread %i in Sleep Sort function.\n", i);
                return;
            }
        }

        //for (int i = 0; i < remainingAmountOfElements; i++) *(newArrayStartPointer + i) = 0;
        //for (int i = 0; i < remainingAmountOfElements; i++) ResumeThread(arrayOfThreads[i]);

        WaitForMultipleObjects(remainingAmountOfElements, arrayOfThreads, TRUE, INFINITE);

        for (int i = 0; i < remainingAmountOfElements; i++) CloseHandle(arrayOfThreads[i]);

        free(arrayOfThreads);

        DeleteCriticalSection(&criticalSection);

    #elif __unix__ || __unix || __linux__ || __APPLE__ && __MACH__
        // Not Implemented Yet...
    #else
        // Unknown OS
    #endif

    return;
}


void gSurpriseSort(compareFunctionGenSort compareF, void* arrayPointer, uint64_t arraySize, uint64_t dataSize) {
    if (!arrayPointer || arraySize < 2) return;

    if (!compareF || dataSize == 0) {
        if (!compareF) fprintf(stderr, "Error: Cannot apply generic Surprise Sort to array if the compare function is NULL.\n");
        if (dataSize == 0) fprintf(stderr, "Error: DataSize parameter for generic Surprise Sort function cannot be zero.\n");
        return;
    }

    srand((unsigned int)time(NULL));

    sortingFunctionSignature allSortingAlgorithms[] = {gBinaryInsertionSort,
                                   gBubbleSort, 
                                   gCombSort, 
                                   gDoubleSelectionSort, 
                                   gInsertionSort, 
                                   gHeapSort, 
                                   gMergeSort, 
                                   gSelectionSort, 
                                   gQuickSort,
                                   gBogoSort, 
                                   gGoodEnough, 
                                   gStoogeSort};

    uint64_t numberOfAlgorithms = sizeof(allSortingAlgorithms) / sizeof(*allSortingAlgorithms);
    sortingFunctionSignature functionChoosed = allSortingAlgorithms[rand() % numberOfAlgorithms];

    functionChoosed(compareF, arrayPointer, arraySize, dataSize);
    
    return;
}
