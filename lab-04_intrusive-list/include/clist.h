#ifndef CLIST_H_
#define CLIST_H_

struct intrusive_node{
  struct intrusive_node* next;
  struct intrusive_node* prev;
};

typedef struct intrusive_node intrusive_node_t;

typedef struct {
  intrusive_node_t head;
} intrusive_list_t;

void init_list(intrusive_list_t*);
void add_node(intrusive_list_t*, intrusive_node_t*);
void remove_node(intrusive_list_t*, intrusive_node_t*);
void remove_all_nodes(intrusive_list_t*);
int get_length(intrusive_list_t*);

#endif
