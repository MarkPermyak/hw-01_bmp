#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

typedef int (*comp_t)(const void *, const void *);

void merge(void* array, size_t elements, size_t element_size, comp_t comparator){
    
    size_t middle = elements/2;

    char* tmp_array = malloc(elements * element_size);
    if (tmp_array == NULL)
        exit(1);
    
    char* pntr1 = (char*)array;
    char* pntr2 = (char*)array + middle * element_size;
    char* res = (char*)tmp_array;

    while ((pntr1 - (char*)array < middle * element_size) && 
        (pntr2 - (char*)array < elements * element_size)){
        
        if (comparator(pntr1, pntr2) <= 0){
            memcpy(res, pntr1, element_size);
            pntr1 += element_size;
        }
        
        else{
            memcpy(res, pntr2, element_size);
            pntr2 += element_size;
        }
        
        res += element_size;
    }
    
    while (pntr1 - (char*)array < middle * element_size)
        *res++ = *pntr1++;
    while (pntr2 - (char*)array < elements * element_size)
        *res++ = *pntr2++;

    memcpy(array, tmp_array, elements*element_size);
    free(tmp_array);
}

void mergesort(void* array, size_t elements,
               size_t element_size, comp_t comparator){
    
    if (elements == 1)
        return;

    size_t middle = elements/2;
    mergesort(array, middle, element_size, comparator);
    mergesort((char*)array + middle*element_size, (elements+1)/2, element_size, comparator);

    merge(array, elements, element_size, comparator);
}
