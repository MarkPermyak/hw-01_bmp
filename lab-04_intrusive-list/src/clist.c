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

        cur = next;
    }
}

void add_node(intrusive_list_t *l, point_t* new) {
    

    
    intrusive_node_t* first = l->head.next;

    l->head.next = &new->node;
    

    new->node.prev = &l->head;
    new->node.next = first;
    if(first)
        first->prev = &new->node;

}

void remove_point(intrusive_list_t* l, point_t* new){
    intrusive_node_t* cur = l->head.next;
    int x = new->x;
    int y = new->y;
   
    while (cur){
        point_t* cur_point = get_point(cur);
        
        if(cur_point->x == x && cur_point->y == y){
            cur->prev->next = cur->next;
            if(cur->next)
                cur->next->prev = cur->prev;
        }
        
        cur = cur->next;
    }
}

point_t* get_point(intrusive_node_t* node_ptr) {
    return container_of(node_ptr, point_t, node);
}

void free_node(intrusive_node_t* node) {
    free(get_point(node));
}

void remove_all_points(intrusive_list_t *l) {
    apply(l, free_node);
    init_list(l);
}

void print_point(intrusive_node_t* node) {
    point_t* point = get_point(node);

    printf("(%d %d) ", point->x, point->y);
}

void show_all_points(intrusive_list_t l){
    apply(&l, print_point);
    printf("\n");
}
point_t* alloc_point(int x, int y){
    intrusive_node_t* node = malloc(sizeof(intrusive_node_t));
    point_t* point = malloc(sizeof(point_t));
    point->node = *node;
    point->x = x;
    point->y = y;
    return point;
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
