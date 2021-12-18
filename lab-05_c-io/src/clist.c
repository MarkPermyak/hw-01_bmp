#include "clist.h"

void init_list(intrusive_list_t *l){
    l->head.prev = NULL;
    l->head.next = NULL;
}

void apply(intrusive_list_t *list, 
            void (*op)(intrusive_node_t *node, void *data), void *data){
    intrusive_node_t* cur = list->head.next;

    while (cur) {
        intrusive_node_t* next = cur->next;
        op(cur, data);
        cur = next;
    }

};

void add_node(intrusive_list_t *l, intrusive_node_t* new) {    
    // Add to the end
    intrusive_node_t* cur = &l->head;

    while (cur->next)
       cur = cur->next;
    
    cur->next = new;
    new->next = NULL;
    new->prev = cur;

    //Add to the beginning
    // intrusive_node_t* first = l->head.next;

    // l->head.next = new;

    // new->prev = &l->head;
    // new->next = first;
    // if(first)
    //     first->prev = new;
}

void remove_node(intrusive_list_t* l, intrusive_node_t* del){
    if(del->prev)
        del->prev->next = del->next;
    
    if(del->next)
        del->next->prev = del->prev;
}

void remove_all_nodes(intrusive_list_t *l){
    intrusive_node_t* cur = l->head.next;
    
    while (cur){
        remove_node(l, cur);
        cur = cur->next;
    }
        
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
