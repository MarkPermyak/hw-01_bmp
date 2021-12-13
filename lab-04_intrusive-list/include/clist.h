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
void apply(intrusive_list_t* l, void (*func)(intrusive_node_t*));
void free_node(intrusive_node_t* node);
int get_length(intrusive_list_t*);

// void add_point(intrusive_list_t*, int, int);
// void remove_point(intrusive_list_t*, int, int);
// void remove_all_points(intrusive_list_t* l);
// point_t* get_point(intrusive_node_t* node_ptr);
// void print_point(intrusive_node_t* node);
// void show_all_points(intrusive_list_t);
// point_t* alloc_point(int x, int y);

void test(intrusive_list_t*);
#endif
