#include "Scheme.hpp"

Scheme::Scheme(int capacity){
    figures_ = new Figure*[capacity];
    capacity_ = capacity;
    figures_count_ = 0;
}

Scheme::~Scheme(){
    for(int i = 0; i < figures_count_; i++)
        delete figures_[i];
    delete[] figures_;
}

int Scheme::find_id(int need_id){
    for(int i = 0; i < figures_count_; i++)
        if(figures_[i]->get_id() == need_id)
            return i;
    return 0;
    //error otherwise
}
void Scheme::push_back_figure(Figure* fg){
    figures_[figures_count_] = fg;
    figures_count_++;
}

void Scheme::print_all_figures(){
    for(int i = 0; i < figures_count_; i++)
        figures_[i]->print();
    // figures_[1]->print();
}
void Scheme::remove_figure(int id_del){
    int del = find_id(id_del);
    delete figures_[del] ;
    // std::cout << del << '\n';
    if (del != figures_count_ - 1){
        
    
        for(int i = del + 1; i < figures_count_; i++)
            figures_[i - 1] = figures_[i];
            
        // figures_[figures_count_-1] = 0;

    }
    // figures_[del]->~Figure();
    // for(int j = del; j < figures_count_ - 1; j++)
    //     figures_[j] = figures_[j+1];
    // figures_[figures_count_-1]->~Figure(); 
    figures_count_--;
}

void Scheme::zoom_figure(int id, int factor){
    int zoom = find_id(id);
    figures_[zoom]->zoom(factor);
}

void Scheme::move(int id, int new_x, int new_y){
    int mv = find_id(id);
    figures_[mv]->move(new_x, new_y);
}

Figure* Scheme::is_inside_figure(int x, int y){
    for(int i = 0; i < figures_count_; i++)
        if((figures_[i]->is_inside(x, y)))
            return figures_[i];
    return nullptr;
}
