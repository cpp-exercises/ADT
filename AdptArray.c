//
// Created by sagi yosef azulay on 21/03/2023.
//



#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define min(a, b) ((a) < (b) ? (a) : (b))
typedef struct AdptArray_ {
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
    int size;
    PElement *arr;
} AdptArray;

typedef AdptArray *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_) {
    PAdptArray PArr = (PAdptArray) malloc(sizeof(AdptArray));
    if (PArr == NULL) {
        printf("ERROR failed to allocate memory");
        return NULL;
    }
    PArr->size = 0;
    PArr->arr = NULL;
    PArr->delFunc = delFunc_;
    PArr->copyFunc = copyFunc_;
    PArr->printFunc = printFunc_;
    return PArr;
}


int GetAdptArraySize(PAdptArray pArr) {
    if (pArr == NULL) {
        printf("ERROR: EXCEPTED:Arraylist type pointer , actual: NULL");
        return FAIL;
    }
    return pArr->size;
}


Result SetAdptArrayAt(PAdptArray pArr, int index, PElement pNewElement) {
    if (index < 0) {
        printf("ERROR: EXCEPTED: index>=0 , ACTUAL: %d", index);
        return FAIL;
    }
    if (pArr == NULL) {
        printf("ERROR: EXPECTED: AdaptArray type pointer, ACTUAL: NULL");
        return FAIL;
    }
    PElement *newArr = NULL;
    if (index >= pArr->size) {
        newArr = (PElement *) calloc(index + 1, sizeof(PElement));
        if (newArr == NULL) {
            return FAIL;
        }


        //memcpy(newArr, pArr->arr, min(pArr->size, index) * sizeof(PElement));
        memcpy(newArr, pArr->arr, pArr->size * sizeof(PElement));

        free(pArr->arr);
        pArr->arr = newArr;
        pArr->size = index + 1;
    }

    if (pArr->arr[index] != NULL) {
        pArr->delFunc(pArr->arr[index]);
    }
    pArr->arr[index] = pArr->copyFunc(pNewElement);
    if (pArr->arr[index] == NULL) {
        return FAIL;
    }
    return SUCCESS;
}


void DeleteAdptArray(PAdptArray pArr) {
    // handle NULL pointer
    if (pArr == NULL) {

        printf("ERROR: EXCEPTED:Arraylist type pointer\nACTUAL: NULL");
        return;
    }

    for (int i = 0; i < pArr->size; i++) {
        if(GetAdptArrayAt(pArr,i)==NULL)
            continue;
        pArr->delFunc(pArr->arr[i]); // delete each element using the DEL_FUNC pointer
    }

    free(pArr->arr); // free the array memory
    free(pArr); // free the AdaptArray struct memory
}


void PrintDB(PAdptArray pArr) {
    if (pArr == NULL) {
        printf("ERROR: EXCEPTED:Arraylist type pointer , actual: NULL");
        return;
    }
    if (pArr->size == 0) {
        printf("ERROR: ArrayList is empty!!");
        return;
    }
    for (int i = 0; i < pArr->size; i++) {
        if (pArr->arr[i] != NULL) {
            pArr->printFunc(pArr->arr[i]);
        }
    }

}


PElement GetAdptArrayAt(PAdptArray pArr, int index) {
    if (pArr == NULL) {
        printf("ERROR: EXCEPTED:pointer to AdaptArray , actual: NULL\n");
        return NULL;
    }
    if (index >= pArr->size) {
        printf("ERROR: EXCEPTED: index is out of range,\n");
        return NULL;
    }
    if (pArr->arr[index] == NULL) {
        printf("ERROR: EXCEPTED: pElement , actual: NULL\n");
        return NULL;
    }
    PElement element = pArr->copyFunc(pArr->arr[index]);
    pArr->copyFunc(element);
    return pArr->arr[index];
}





