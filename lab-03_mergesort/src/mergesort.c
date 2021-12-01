#include <stddef.h>
#include <stdlib.h>
#include "mergesort.h"

typedef int (*comp_t)(const void *, const void *);

void my_memcpy(void* dst, void* src, size_t element_size){
    for(char* pdst = dst, *psrc = src; psrc - (char*)src < element_size; *pdst++ = *psrc++);
}


void merge(void* array, size_t elements, size_t element_size, comp_t comparator){
    
    size_t middle = elements/2;
    char* new_array = malloc(elements * element_size);
    if (new_array == NULL)
        exit(1);
    
    char* pntr1 = (char*)array;
    char* pntr2 = (char*)array + middle * element_size;
    char* res = (char*)new_array;

    while ((pntr1 - (char*)array < middle * element_size) && 
    (pntr2 - (char*)array < (elements) * element_size))
    {
        if (comparator(pntr1, pntr2) <= 0)
        {
            my_memcpy(res, pntr1, element_size);
            pntr1 += element_size;
        }
        
        else{
            my_memcpy(res, pntr2, element_size);
            pntr2 += element_size;
        }
        res += element_size;
    }
    
    
    while (pntr1 - (char*)array < middle * element_size)
        *res++ = *pntr1++;
    while (pntr2 - (char*)array < elements * element_size)
        *res++ = *pntr2++;

    my_memcpy(array, new_array, elements*element_size);
    free(new_array);
    
    
   

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
