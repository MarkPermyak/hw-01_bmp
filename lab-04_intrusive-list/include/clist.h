#ifndef CLIST_H_
#define CLIST_H_

#include <stddef.h>

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct intrusive_node{
  struct intrusive_node* next;
  //struct intrusive_node *prev;
};

typedef struct intrusive_node intrusive_node_t;

typedef struct {
  intrusive_node_t head;
} intrusive_list_t;

typedef struct {
    int x;
    int y;
    intrusive_node_t node;
} point_t;

void init_list(intrusive_list_t*);
void add_node(intrusive_list_t*, point_t*);
void apply(intrusive_list_t* l, void (*func)(intrusive_node_t*));
void free_node(intrusive_node_t* node);
void destroy(intrusive_list_t *l);
point_t* get_point(intrusive_node_t* node_ptr);
void print_point(intrusive_node_t* node);
point_t* alloc_point(int x, int y);
// void remove_node(intrusive_list /* ? */, intrusive_node /* ? */);
int list_length;
int get_length(intrusive_list_t);

#endif
