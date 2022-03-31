#include "my_vector.hpp"

int near_pow2(int x){
    int pow2 = 1;
    while(pow2 < x)
        pow2*=2;

    return pow2;
};

namespace containers{

    template<typename T>
    my_vector<T>::my_vector(){
        capacity_ = 2;
        size_ = 0;
        array_ = (T*)malloc(sizeof(T)*capacity_);
    }

    template<typename T>
    my_vector<T>::my_vector(std::size_t n){
        capacity_ = near_pow2(n);
        size_ = n;
        array_ = (T*)malloc(sizeof(T)*capacity_);
        for(int i = 0; i < n; i++){
            T new_obj;
            memcpy(array_[i], new_obj, sizeof(new_obj));
        }
    }

    template<typename T>
    my_vector<T>::my_vector(const my_vector<T>& other){
        capacity_ = other.capacity_;
        size_ = other.size_;
        array_ = (T*)malloc(sizeof(T)*capacity_);
        memcpy(array_, other.array_, sizeof(T)*size_);
    }

    template<typename T>
    my_vector<T>::~my_vector(){
        free(array_);
    }

    //TODO
    template<typename T>
    void my_vector<T>::push_back(T t){
        array_[size_] = t;
        size_++;
    }

    template<typename T>
    T my_vector<T>::operator[](std::size_t index){
        return array_[index];
    }
}