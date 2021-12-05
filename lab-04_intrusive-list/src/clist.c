#include <stddef.h>
#include "clist.h"

typedef struct{
    intrusive_node *next;
    intrusive_node *prev;
} intrusive_node;

typedef struct {
    intrusive_node head;
} intrusive_list;

typedef struct {
    int x;
    int y;
    intrusive_node head;
} point_t;

void init_list(intrusive_list *l){
    l->head.prev = NULL;
    l->head.next = NULL;
}

