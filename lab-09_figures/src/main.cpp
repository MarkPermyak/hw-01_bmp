#include <stdio.h>

#include "Scheme.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"


int main() {
    Scheme scheme(10);

    //scheme.push_back_figure(new Circle(5, 2, 2, 2, "kekes"));
    scheme.push_back_figure(new Rectangle(1, 5, 5, 10, 10));
    scheme.push_back_figure(new Circle(2, 3, 3, 3, "very nice circle"));

    
    scheme.print_all_figures();

    Figure* found = scheme.is_inside_figure(5, 5);
    if (found != nullptr) {
        found->print();
    } else {
        printf("not found\n");
    }

    scheme.zoom_figure(1, 2);
    scheme.print_all_figures();
    scheme.remove_figure(1);
    scheme.print_all_figures();
  
  
    // Figure* obj = new Circle(2, 0, 1, 1, "privet");
    // obj->move(0, 0);
    // obj->zoom(2);
    // obj->print();
    // std::cout << obj->is_inside(0,0) << " " << obj->is_inside(0,2) << std::endl;
    // delete obj; 
    // Figure* kek = new Rectangle(3, 1, 4, 1, 2);
    // kek->move(0, 5);
    // kek->zoom(2);
    // kek->print();
    // std::cout << kek->is_inside(0,0) << " " << kek->is_inside(1,1) << std::endl;

    return 0;
}
