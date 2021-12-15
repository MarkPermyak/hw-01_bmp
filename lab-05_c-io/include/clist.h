#ifndef CLIST_H_
#define CLIST_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LINESIZE 239

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct intrusive_node{
  struct intrusive_node* next;
  struct intrusive_node* prev;
};

typedef struct intrusive_node intrusive_node_t;

typedef struct {
  intrusive_node_t head;
} intrusive_list_t;

void init_list(intrusive_list_t*);
void apply(intrusive_list_t *list, void (*op)(intrusive_node_t *node, void *data), void *data);
void add_node(intrusive_list_t*, intrusive_node_t*);
void remove_node(intrusive_list_t*, intrusive_node_t*);
void remove_all_nodes(intrusive_list_t*);
int get_length(intrusive_list_t*);

#endif
