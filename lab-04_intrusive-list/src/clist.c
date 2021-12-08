#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "clist.h"


void init_list(intrusive_list_t *l){
    l->head.prev = NULL;
    l->head.next = NULL;
}

void apply(intrusive_list_t* l, void (*func)(intrusive_node_t*)) {
    intrusive_node_t* cur = l->head.next;

    while (cur) {
        intrusive_node_t* next = cur->next;
        func(cur);
        //printf("%s\n", "OKapply");

        cur = cur->next;
    }
}

void add_node(intrusive_list_t *l, intrusive_node_t* new) {
        
    intrusive_node_t* first = l->head.next;

    l->head.next = new;
    //printf("%s\n", "OK");

    new->prev = &l->head;
    new->next = first;
    if(first)
        first->prev = new;
    //printf("%s\n", "OK");
}

void remove_node(intrusive_list_t* l, intrusive_node_t* del){
    
    if(del->prev)
        del->prev->next = del->next;
    
    if(del->next)
        del->next->prev = del->prev;
        
    del = NULL;
}

void remove_all_nodes(intrusive_list_t *l){
    intrusive_node_t* cur = &l->head;

    while (cur->next)
        cur = cur->next;
    
    while (cur){
        remove_node(l, cur);
        cur = cur->prev;
    }
    
    
}
void free_node(intrusive_node_t* node) {
    node = NULL;
}

int get_length(intrusive_list_t* l){
    intrusive_node_t* cur = l->head.next;
    int length = 0;
    while (cur){ 
        cur = cur->next;
        length++;
    }

    return length;
}

void test(intrusive_list_t* l){
    intrusive_node_t* cur = l->head.next;
    printf("%d %d\n", get_point(cur)->x, get_point(cur)->y);
}