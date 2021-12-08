#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "clist.h"

// typedef struct{
//     intrusive_node *next;
//     //intrusive_node *prev;
// } intrusive_node_t;

// typedef struct {
//     intrusive_node head;
// } intrusive_list_t;

// typedef struct {
//     int x;
//     int y;
//     intrusive_node node;
// } point_t;

void init_list(intrusive_list_t *l){
    //l->head.prev = NULL;
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
  new->node.next = NULL;

  intrusive_node_t* cur = &l->head;

  while (cur->next) {
    cur = cur->next;
    //printf("%s\n", "OKaddwhile");
  }

  cur->next = &new->node;
  //printf("%s\n", "OKadd");
}

point_t* get_point(intrusive_node_t* node_ptr) {
  return container_of(node_ptr, point_t, node);
}

void free_node(intrusive_node_t* node) {
  free(get_point(node));
}

void destroy(intrusive_list_t *l) {
  apply(l, free_node);
  init_list(l);
}

void print_point(intrusive_node_t* node) {
  point_t* point = get_point(node);

  printf("(%d %d) ", point->x, point->y);
}

point_t* alloc_point(int x, int y){
  intrusive_node_t* node = malloc(sizeof(intrusive_node_t));
  point_t* point = malloc(sizeof(point_t));
  point->node = *node;
  point->x = x;
  point->y = y;
  return point;
}