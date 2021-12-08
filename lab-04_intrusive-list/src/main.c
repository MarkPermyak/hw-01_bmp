#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "clist.h"

#define LINESIZE 239

void add_point(intrusive_list_t* l, int x, int y){
    point_t* point = malloc(sizeof(point_t));
    //intrusive_node_t* node;
    
    point->x = x;
    point->y = y;
    add_node(l, &point->node);
    
}

void remove_point(intrusive_list_t* l, int x, int y){

    intrusive_node_t* cur = l->head.next;

    while (cur){
      point_t* cur_point = get_point(cur);

      if (cur_point->x == x && cur_point->y == y){
        remove_node(l, cur);
       
        free(cur_point);
         //printf("rm %d %d\n", x, y);
      }
      cur = cur->next;
    }
}

void remove_all_points(intrusive_list_t* l) {
    intrusive_node_t* cur = &l->head;
  
    while (cur->next)
        cur = cur->next;
    if (get_length(l) != 0)
    {
      while (cur->prev){
          point_t* p = get_point(cur);
          intrusive_node_t* tmp = cur->prev;
          
          remove_node(l, cur);
          cur = tmp;
          

          free(p);
          //printf("rma\n");
        }
    }
    else
      return;
    //init_list(l);
}

void print_point(intrusive_node_t* node) {
    point_t* point = get_point(node);
    printf("(%d %d) ", point->x, point->y);
}

void show_all_points(intrusive_list_t l){
    apply(&l, print_point);
    printf("\n");
}

point_t* get_point(intrusive_node_t* node_ptr) {
    return container_of(node_ptr, point_t, node);
}

int main() {

  intrusive_list_t my_list;
  init_list(&my_list);
  char input[LINESIZE] = "";

  while (1)
  {
    scanf("%s", input);

    if (!strcmp(input, "exit")){
      remove_all_points(&my_list);
      return 0;
    }
    else if (!strcmp(input, "len"))
      printf("%d\n", get_length(&my_list));
    else if (!strcmp(input, "print"))
      show_all_points(my_list);
    else if (!strcmp(input, "rma"))
      remove_all_points(&my_list);
    else{
      int x;
      int y;
      scanf("%d%d", &x,&y);
      if(!strcmp(input, "add"))
        add_point(&my_list, x, y);  
      else if(!strcmp(input, "rm"))
        remove_point(&my_list, x, y);
      else
        printf("%s\n", "Unknown command");
      }
    
    fflush (stdout);
  }
  return 0;

}
