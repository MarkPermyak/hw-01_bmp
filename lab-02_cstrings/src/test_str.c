#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "str.h"
#include "test_str.h"
#define BUFFER_SIZE 50

void test_my_strcpy(){
    char dest[BUFFER_SIZE];
    char s1[] = "abc";
    char s2[] = "a";
    char s0[] = "";
    
    assert(strcmp(my_strcpy(dest, s0), "") == 0);
    assert(strcmp(my_strcpy(dest, s1), "abc") == 0);
    assert(strcmp(my_strcpy(dest, s2), "a") == 0);
    assert(strcmp(my_strcpy(s1, s2), "a") == 0);

}

void test_my_strcat(){
    char dest[BUFFER_SIZE] = "a";
    char s1[] = "bc";
    char s2[] = "defg";
    char s0[] = "";
    assert(strcmp(my_strcat(s0, s0), "") == 0);
    assert(strcmp(my_strcat(dest, s1), "abc") == 0);
    assert(strcmp(my_strcat(dest, s2), "abcdefg") == 0);
    assert(strcmp(my_strcat(dest, s0), "abcdefg") == 0);
}

void test_my_strcmp(){
    char s1[] = "abcd";
    char s2[] = "abc";
    char s3[] = "b";
    char s4[] = "abcde";
    char s0[] = "";
    assert(my_strcmp(s1, s2) == 1);
    assert(my_strcmp(s1, s3) == -1);
    assert(my_strcmp(s2, s3) == -1);
    assert(my_strcmp(s3, s4) == 1);
    assert(my_strcmp(s0, s2) == -1);
    assert(my_strcmp(s3, s0) == 1);
    assert(my_strcmp(s4, s0) == 1);
    assert(my_strcmp(s1, s1) == 0);
    assert(my_strcmp(s0, s0) == 0);
}


void test_my_strlen(){
        assert(my_strlen("Hello") == 5);
        assert(my_strlen("") == 0);
        assert(my_strlen("a") == 1);
}
