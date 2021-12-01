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

int main(int argc, char** argv){
    if (!strcmp(argv[1], "int")){
        
        if (argc == 2)
            printf("\n");

        else{
            size_t element_size = sizeof(int);
            comp_t comparator = int_gt_comparator;
            int array_size = argc - 2;
            int array[array_size];
            
            for (int i = 2; i < argc; i++)
                array[i-2] = atoi(argv[i]);
            
            mergesort(array, array_size, element_size, comparator);
            
            printf("%d", array[array_size - 1]);
            for (int i =0; i<array_size - 1; ++i)
                printf(" %d", array[array_size - 2 - i]);
            
            printf("\n");
        }   
    }    

    if (strcmp(argv[1], "char") == 0){
        
        if (argc == 2)
            printf("\n");
        
        else{
            size_t element_size = sizeof(char);
            comp_t comparator = char_gt_comparator;
           
            int array_size = argc - 2;    
            char array[array_size];
           
            for (int i = 2; i < argc; i++)
                array[i-2] = *argv[i];

            mergesort(array, array_size, element_size, comparator);
            
            printf("%c", array[array_size - 1]);
            for (int i =0; i<array_size - 1; ++i)
                printf(" %c", array[array_size - 2 - i]);
            
            printf("\n");
        }
    } 
 
    if (strcmp(argv[1], "str") == 0){
        if (argc == 2)
            printf("\n");

        else{
            size_t element_size = sizeof(char *);
            comp_t comparator = str_gt_comparator;

            int array_size = argc - 2;
            char** array = malloc((array_size) * sizeof(char*));
            
            for (int i = 0; i < array_size; i++)
                array[i] = argv[i + 2];
            
            mergesort(array, array_size, element_size, comparator);
            
            for(int i = 0; i < array_size - 1; i++)
                printf("%s ", array[i]);

            printf("%s\n", array[array_size - 1]);

            free(array);
        }
    } 


    return 0;
}
