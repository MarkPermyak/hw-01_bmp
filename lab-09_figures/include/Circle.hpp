#pragma once

#include "Figure.hpp"

class Circle : public Figure {
public:
    Circle(int id, int x, int y, int radius, const char* label);
    ~Circle();
    
    void print() override;
    bool is_inside(int x, int y) override;
    void zoom(int factor) override;

private: 
    int radius_;
    std::string label_;
};
