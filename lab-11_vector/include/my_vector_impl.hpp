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
        array_ = (T*) new char[sizeof(T) * capacity_];

        if(!array_)
            exit(1);
    }

    template<typename T>
    my_vector<T>::my_vector(std::size_t n){
        capacity_ = near_pow2(n);
        size_ = n;
        array_ = (T*) new char[sizeof(T) * capacity_];
        
        if(!array_)
            exit(1);

        for(std::size_t i = 0; i < n; i++)
            new(&array_[i]) T();
        
    }

    template<typename T>
    my_vector<T>::my_vector(const my_vector<T>& other){
        capacity_ = other.capacity_;
        size_ = other.size_;
        array_ = (T*) new char[sizeof(T) * capacity_];

        if(!array_)
            exit(1);

        for(std::size_t i = 0; i < size_; i++)
            new(&array_[i]) T(other.array_[i]);

    }

    template<typename T>
    my_vector<T>::~my_vector(){
        this->clear();
        delete[] (char*) array_;
    }

    template<typename T>
    void my_vector<T>::reserve(std::size_t new_capacity){
        if(new_capacity > capacity_){
            int min_cap = near_pow2(new_capacity);
            T* new_array = (T*) new char[sizeof(T) * min_cap];
            
            if(!new_array)
                exit(1);

            for(std::size_t i = 0; i < size_; i++)
                new(&new_array[i]) T(array_[i]);

            for(std::size_t i = 0; i < size_; i++)
                array_[i].~T(); 
            delete[] (char*) array_;

            array_ = new_array;
            capacity_ = min_cap;
        }
    }
    
    template<typename T>
    void my_vector<T>::push_back(const T& t){
        if(size_ == capacity_)
            reserve(2*capacity_);

        new(&array_[size_]) T(t);
        size_++;
    }

    template<typename T>
    void my_vector<T>::pop_back(){
        if(empty())
            exit(1);
        
        array_[size_-1].~T();
        size_--;
    }

    template<typename T>
    void my_vector<T>::resize(std::size_t new_size){
        if(new_size <= size_)
            for(std::size_t i = size_; i > new_size; i--)
                pop_back();

        else{
            reserve(near_pow2(new_size));
            T def_obj = T();
            for(std::size_t i = size_; i < new_size; i++)
                push_back(def_obj);
        }
        
        size_ = new_size;
    }

    template<typename T>
    std::size_t my_vector<T>::size() const { return size_ ;}
    
    template<typename T>
    std::size_t my_vector<T>::capacity() const { return capacity_ ;}

    template<typename T>
    bool my_vector<T>::empty() const { return (size_ == 0) ;}

    template<typename T>
    void my_vector<T>::clear(){
        for(std::size_t i = 0; i < size_; i++)
            array_[i].~T(); 
        size_ = 0;
    }

    template<typename T>
    T const my_vector<T>::operator[](std::size_t index) const{
        return array_[index];
    }

    template<typename T>
    my_vector<T>& my_vector<T>::operator=(const my_vector& other){
        size_ = other.size_;
        capacity_ = other.capacity_;

        T* new_array = (T*) new char[sizeof(T) * capacity_];
        
        if(!new_array)
            exit(1);

        for(std::size_t i = 0; i < size_; i++)
            new(&new_array[i]) T(other.array_[i]);
                

        delete[] (char*) array_;

        array_ = new_array;
        return *this;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const my_vector<T>& v){
        for(std::size_t i = 0; i < v.size_; i++)
            os << v.array_[i] << " ";
        return os;  
    }
    
}