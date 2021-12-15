#include "clist.h"

struct point {
    int x;
    int y;
    intrusive_node_t node;
};

typedef struct point point_t;

point_t* get_point(intrusive_node_t* node_ptr) {
    return container_of(node_ptr, point_t, node);
}

void add_point(intrusive_list_t* l, int x, int y){
    point_t* point = malloc(sizeof(point_t));
    assert(malloc(sizeof(point_t))!= NULL);
    point->x = x;
    point->y = y;
    add_node(l, &point->node);
    
}

void remove_point(intrusive_list_t* l, int x, int y){
    intrusive_node_t* cur = l->head.next;

    while (cur){
      point_t* cur_p = get_point(cur);
      intrusive_node_t* cur_next = cur->next;

      if (cur_p->x == x && cur_p->y == y){
        remove_node(l, cur);
        free(cur_p);
      }

      cur = cur_next;
    }
}

void remove_all_points(intrusive_list_t* l) {
    intrusive_node_t* cur = l->head.next;
  
    while (cur){
      point_t* cur_p = get_point(cur);
      intrusive_node_t* cur_next = cur->next;
      
      remove_node(l, cur);
      cur = cur_next;
      free(cur_p);
    }  
}

void show_all_points(intrusive_list_t* l){
    intrusive_node_t* cur = l->head.next;
    int i = 0;
    
    while (cur){ 
        point_t* cur_p = get_point(cur);
        
        if(i)
          printf(" ");
        
        printf("(%d %d)", cur_p->x, cur_p->y);
        i = 1;
        cur = cur->next;
    }

    printf("\n");
}


int main() {

  intrusive_list_t my_list;
  init_list(&my_list);
  char input[LINESIZE] = "";

  while (1){
    scanf("%239s", input);

    if (!strcmp(input, "exit")){
      remove_all_points(&my_list);
      return 0;
    }

    else if (!strcmp(input, "add")){
      int x;
      int y;
      scanf("%239d%239d", &x,&y);
      add_point(&my_list, x, y); 
    }

    else if (!strcmp(input, "rm")){
      int x;
      int y;
      scanf("%d%d", &x,&y);
      remove_point(&my_list, x, y);
    }

    else if (!strcmp(input, "len"))
      printf("%d\n", get_length(&my_list));
    
    else if (!strcmp(input, "print"))
      show_all_points(&my_list);
    
    else if (!strcmp(input, "rma"))
      remove_all_points(&my_list);
    
    else
      printf("%s\n", "Unknown command");
  }
  return 0;
}
