#include "point_list.h"
#include "clist.h"

point_t* get_point(intrusive_node_t* node_ptr) {
    return container_of(node_ptr, point_t, node);
}

void add_point(intrusive_list_t* l, int x, int y){
    point_t* point = malloc(sizeof(point_t));
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
