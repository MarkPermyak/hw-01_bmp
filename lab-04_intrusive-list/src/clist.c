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

        cur = cur->next;
    }
}

void add_node(intrusive_list_t *l, intrusive_node_t* new) {
        
    intrusive_node_t* first = l->head.next;

    l->head.next = new;

    new->prev = &l->head;
    new->next = first;
    if(first)
        first->prev = new;
}

void remove_node(intrusive_list_t* l, intrusive_node_t* del){
    
    if(del->prev)
        del->prev->next = del->next;
    
    if(del->next)
        del->next->prev = del->prev;
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
    free(node);
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
