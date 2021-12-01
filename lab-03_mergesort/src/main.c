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

int main(int argc, char** argv){
    if (!strcmp(argv[1], "int")){
        size_t element_size = sizeof(int);
        comp_t comparator = int_gt_comparator;
        
        if (argc == 2)
            printf("\n");
        else{
        int array[argc-2];
        for (int i = 2; i < argc; i++)
        {
            array[i-2] = atoi(argv[i]);
        }
        mergesort(array, argc-2, element_size, comparator);
        printf("%d", array[argc-3]);
        for (int i =0; i<argc-3; ++i)
            printf(" %d", array[argc - 4 - i]);
        }   
    }    
    if (strcmp(argv[1], "char") == 0){
        size_t element_size = sizeof(char);
        comp_t comparator = char_gt_comparator;
        if (argc == 2)
            printf("\n");
        else{
        char array[argc-2];
        for (int i = 2; i < argc; i++)
        {
            array[i-2] = *argv[i];
        }
        mergesort(array, argc-2, element_size, comparator);
        printf("%c", array[argc-3]);
        for (int i =0; i<argc-3; ++i)
            printf(" %c", array[argc - 4 - i]);
        printf("\n");
        }
    } 
 
    if (strcmp(argv[1], "str") == 0){
        if (argc == 2)
            printf("\n");
        else{

        }
    } 


    return 0;
}
