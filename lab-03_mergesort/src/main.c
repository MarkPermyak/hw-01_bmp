#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "mergesort.h"

int int_gt_comparator(const void *a, const void *b) {
    return *(int*)b - *(int*)a;  
}

int char_gt_comparator(const void *ch1, const void *ch2){
    return *(char*)ch2 - *(char*)ch1;
}

int str_gt_comparator(const void *s1, const void *s2){   
    return strcmp(*(char**)s1, *(char**)s2);
}

int* create_int_array(int array_size, int element_size){
    return malloc(array_size * element_size);
}

char* create_char_array(int array_size, int element_size){
    return malloc(array_size * element_size);
}

char** create_str_array(int array_size, int element_size){
    return malloc(array_size * element_size);
}

void fill_int_array(int *array, char **argv, int array_size){
    for (int i = 0; i < array_size; i++)
        array[i] = atoi(argv[i+2]);
}

void fill_char_array(char *array, char **argv, int array_size){
    for (int i = 0; i < array_size; i++)
        array[i] = *argv[i+2];
}

void fill_str_array(char **array, char **argv, int array_size){
    for (int i = 0; i < array_size; i++)
        array[i] = argv[i + 2];
}

void int_printer(int *array, int array_size){
    printf("%d", array[array_size - 1]);
    for (int i =0; i<array_size - 1; ++i)
        printf(" %d", array[array_size - 2 - i]);
    
    printf("\n");
}

void char_printer(char *array, int array_size){
    printf("%c", array[array_size - 1]);
    for (int i =0; i<array_size - 1; ++i)
        printf(" %c", array[array_size - 2 - i]);
    
    printf("\n");
}

void str_printer(char **array, int array_size){
    for(int i = 0; i < array_size - 1; i++)
        printf("%s ", array[i]);

    printf("%s\n", array[array_size - 1]);
}

int main(int argc, char** argv){
    if (argc == 2)
            printf("\n");
    
    else{

        int array_size = argc - 2;

        if (!strcmp(argv[1], "int")){

            size_t element_size = sizeof(int);
            comp_t comparator = int_gt_comparator;
            
            int* array = create_int_array(array_size, element_size);

            fill_int_array(array, argv, array_size);
            mergesort(array, array_size, element_size, comparator);
            int_printer(array, array_size);

            free(array);
        }    

        if (strcmp(argv[1], "char") == 0){
            
            size_t element_size = sizeof(char);
            comp_t comparator = char_gt_comparator;
                
            char* array = create_char_array(array_size, element_size);

            fill_char_array(array, argv, array_size);
            mergesort(array, array_size, element_size, comparator);
            char_printer(array, array_size);

            free(array);
        } 

        if (strcmp(argv[1], "str") == 0){
            
            size_t element_size = sizeof(char *);
            comp_t comparator = str_gt_comparator;

            char** array = create_str_array(array_size, element_size);
            
            fill_str_array(array, argv, array_size);
            mergesort(array, array_size, element_size, comparator);
            str_printer(array, array_size);

            free(array);
            
        }
    }

    return 0;
}
