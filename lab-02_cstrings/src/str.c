#include "str.h"                

char *my_strcpy(char* s1, char* s2){
        char *res = s1;
        
        while (*s2 != 0){                
                *s1++ = *s2++;
        }
        
        *s1 = '\0';
        
        return res;
        
}

char *my_strcat(char* s1, char* s2){
        char *res = s1;

        while (*s1 != 0)
                s1++;

        while (*s2 != 0){     
                *s1++ = *s2++;
        }
        
        *s1 = '\0';
        
        return res;
}

int my_strcmp(char* s1, char* s2){
        int res = 0;
        while (*s1 == *s2 && *s1 != 0 && *s2 != 0){
                s1++;
                s2++;
        }
        if (*s1 < *s2)
                res = -1;                
        if (*s1 > *s2)
                res = 1;
        
        return res;
}

size_t my_strlen(char* s){
        int len = 0;
        while (*s != 0){
                s++;
                len++;
       }
        return len;
}
