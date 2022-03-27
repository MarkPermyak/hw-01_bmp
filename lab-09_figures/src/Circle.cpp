#include "Circle.hpp"
#include <cmath>

Circle::Circle(int id, int x, int y, int radius, const char* label) : 
    Figure(id, x, y), radius_(radius), label_(label){}

Circle::~Circle(){}

const char* Circle::get_label() const{ return label_.c_str();}

void Circle::print(){
    std::cout <<"Circle " << id <<": x = " << x <<" y = "<< y << " radius = " 
    << radius_ << " label = " << get_label() << '\n';
}

bool Circle::is_inside(int other_x, int other_y){
    return (((other_x - x)*(other_x - x) + (other_y - y)*(other_y - y)) <= radius_*radius_);
    // return ((pow(other_x - x, 2.0) + pow(other_y - y, 2.0) <= pow(radius_, 2.0)));
}
void Circle::zoom(int factor){
    radius_*=factor;
}

