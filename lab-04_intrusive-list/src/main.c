#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "clist.h"

#define LINESIZE 239

void add_point(intrusive_list_t* l, int x, int y){
    point_t* point = malloc(sizeof(point_t));
    intrusive_node_t* node = malloc(sizeof(intrusive_node_t));
    add_node(l, &point->node);
    
    point->x = x;
    point->y = y;
}

void remove_point(intrusive_list_t* l, int x, int y){

    intrusive_node_t* cur = l->head.next;

    while (cur){
      point_t* cur_point = get_point(cur);

      if (cur_point->x == x && cur_point->y == y){
        remove_node(l, cur);
        cur_point = NULL;
      }
      cur = cur->next;
    }
}

void remove_all_points(intrusive_list_t l) {
    remove_all_nodes(&l);
    init_list(&l);
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

  while (1)
  {
    char input[LINESIZE] = "";
    fgets(input, LINESIZE, stdin);
    input[strlen(input) - 1] = '\0';
    
    if (!strcmp(input, "exit")){
      break;
      return 0;
    }
    else{
      if (!strcmp(input, "len"))
            printf("%d\n", get_length(&my_list));
      else{
        if (!strcmp(input, "print"))
          show_all_points(my_list);
        else{
          if (!strcmp(input, "rma"))
            remove_all_points(my_list);
          else{
            
              char num1[LINESIZE] = "";
              int i = 0;
              while(!isdigit((unsigned char)input[i]) && (input[i] != '-' ))
                i++;
              int j = 0;

              while(input[i] != ' '){
                num1[j] = input[i];
                j++;
                i++;
              }
              int x = atoi(num1);
              char num2[LINESIZE] = "";
              i++;
              int k = 0;
              while(input[i]){
                num2[k] = input[i];
                i++;
                k++;
              }
              int y = atoi(num2);

              if(input[0] == 'a' && input[1] == 'd' && input[2] == 'd' && input[3] == ' ')
                add_point(&my_list, x, y);  
              else{
                if(input[0] == 'r' && input[1] == 'm' && input[2] == ' ')
                  remove_point(&my_list, x, y);
                else
                  printf("%s\n", "Unknown command");
              }
            

          }
          
        }
      }
    }
    fflush (stdout);
  }
  return 0;

}
