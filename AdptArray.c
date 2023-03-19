#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct AdptArray_ 
{
    PElement *head;
    int size; 
    DEL_FUNC del;
    COPY_FUNC cpy;
    PRINT_FUNC prnt;
} AdptArray_, *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC cpy, DEL_FUNC del,PRINT_FUNC prnt){
    PAdptArray arr = (PAdptArray)malloc(sizeof(AdptArray_));
    if(arr!=NULL)
    {
        arr->head = NULL;
        arr->size = 0;
        arr->cpy = cpy;
        arr->del = del;
        arr->prnt = prnt;
    }
    return arr;
}

void DeleteAdptArray(PAdptArray arr){
    if(arr!=NULL)
    {
        // if array has been initialized 
        if(arr->head!=NULL)
        {
            for(int i=0; i<arr->size;i++)
            {
                //if item at index have been intialized do proper delete 
                if(arr->head[i]!=NULL)
                {
                    arr->del(arr->head[i]);
                }
            }
        }
        //free pointers 
        free(arr->head);
        free(arr);
    }
}

Result SetAdptArrayAt(PAdptArray arr, int index, PElement p)
{
// if the index in the array bounds 
if(index<arr->size)
{
    //if an item alreay exist at this index
    if(arr->head[index]!=NULL)
    {
        // free the item at index using the delete func
        arr->del(arr->head[index]);
        //set the new item in the index
        arr->head[index]=p;
        return SUCCESS;
    }
}   
// if the index out of array bounds
else
{
    // calloc new array to index size+1
    PElement *new_head = (PElement *)(calloc(sizeof(PElement), index+1));
    //if the calloc failed 
    if (new_head == NULL)
    {
        return FAIL;
    }
    // check if an array ever existed 
    if(arr->head != NULL)
    {
        // realloc old array to new array 
        for(int i=0;i<arr->size;i++)
        {
            new_head[i]=arr->head[i];
        }
        // free old array
        free(arr->head);
    }
    // set element at index 
    new_head[index]=arr->cpy(p);
    //set new array as the array 
    arr->head = new_head;
    // set size to size of new array
    arr->size = index+1;
    return SUCCESS;
}
return FAIL;
}

PElement GetAdptArrayAt(PAdptArray arr, int index)
{
    //if index in array
    if(index<arr->size)
    {
        // index has not intialized yet
        if(arr->head[index]==NULL)
        {
            return NULL;
        }
        // item at index have been intialized 
        else
        {
            return arr->cpy(arr->head[index]);
        }

    }
    // index out of array bound
    return NULL;
}

int GetAdptArraySize(PAdptArray arr)
{
    //if array has initialized 
    if(arr->head!=NULL)
    {
        return arr->size;
    }
    return -1;

}

void PrintDB(PAdptArray arr)
{
    //if array has intialized 
    if(arr->head != NULL)
    {
        for(int i=0; i<arr->size; i++)
        {
            if(arr->head[i]!=NULL)
            {
                arr->prnt(arr->head[i]);
            }
        }
    }
}






