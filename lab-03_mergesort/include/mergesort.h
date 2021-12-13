#ifndef __MERGESORT_H__
#define __MERGESORT_H__

#include <stddef.h>

typedef int (*comp_t)(const void *, const void *);

//typedef void (*print_t)(const void*);

void mergesort(void *array, size_t elements, size_t element_size, 
                int (*comparator)(const void *, const void *));

#endif
