#ifndef __MERGESORT_H__
#define __MERGESORT_H__

#include <stddef.h>
typedef int (*comp_t)(const void *, const void *);

void merge(void* array, size_t elements, size_t element_size, comp_t comparator);
void mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *));
void* shift_to(void* array, size_t element_size, size_t count);
void my_memcpy(void* dst, void* src, size_t element_size);
#endif
