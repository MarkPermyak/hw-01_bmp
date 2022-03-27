#include "Rectangle.hpp"
#include <cmath>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : 
    Figure(id, x, y), width_(width), height_(height){}

Rectangle::~Rectangle(){}

void Rectangle::print() const {
    std::cout <<"Rectangle " << id <<": x = " << x <<" y = "<< y << " width = " 
        << width_ << " height = " << height_ << std::endl;
}

bool Rectangle::is_inside(int other_x, int other_y) const {
    return ((2 * abs(other_x - x) <= width_) && (2 * abs(other_y - y) <= height_));
}

void Rectangle::zoom(int factor){
    width_*=factor;
    height_*=factor;
}
