#include <iostream>
#include <cassert>
#include "my_vector.hpp"

namespace product {

class Product {
    public:
        Product(){
            char* def = (char*)"default";
            name_ = new char[strlen(def) + 1];
            strcpy(name_, def);
            quantity_ = 1;
            price_ = 1.0;
        }

        Product(const char* name, int quantity, double price){
            name_ = new char[strlen(name) + 1];
            strcpy(name_, name);
            quantity_ = quantity;
            price_ = price;
        };
        
        Product(const Product& other){
            name_ = new char[strlen(other.name_) + 1];
            strcpy(name_, other.name_);
            quantity_ = other.quantity_;
            price_ = other.price_;
        }
        
        ~Product(){
            delete[] name_;
        };

        friend std::ostream& operator<<(std::ostream& os, const Product& p){
            os << p.name_ << " " << p.quantity_ << " " << p.price_  << " ";
            return os;  
        };
    private:
        char* name_;
        int quantity_;
        double price_;
    };

}  // namespace product

template<typename T>
void test_my_vector() {
    containers::my_vector<T> v;
    assert(v.capacity() == 2);
    T a = T();
    T b = T();
    T c = T();
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    assert(v.size() == 3);
    assert(v.capacity() == 4);
    containers::my_vector<T> w(v);
    assert(v.size() == w.size());
    assert(v.capacity() == w.capacity());

    v.reserve(7);
    assert(v.capacity() == 8);
    v.pop_back();
    assert(!v.empty());
    v.clear();
    assert(v.empty());
    std::cout << w << std::endl;
}

template<typename T>
void test_my_vector_default_constructible() {
    containers::my_vector<T> v;
    T a = T();
    T b = T();
 
    v.push_back(a);
    v.push_back(b);
 
    containers::my_vector<T> w(2);
    containers::my_vector<T> u(w);
    assert(w[0] == a);
    assert(w[1] == b);
    assert(u[0] == a);
    assert(u[1] == b);
    
    assert(v.size() == w.size());
    assert(v.size() == u.size());
    assert(w.size() == u.size());
    assert(v.capacity() == w.capacity());
    assert(v.capacity() == u.capacity());
    assert(u.capacity() == w.capacity());

    v.resize(5);
    assert(v.capacity() == 8);
    assert(v.size() == 5);
    
    v.reserve(10);
    assert(v.capacity() == 16);
   
    v.clear();
    assert(v.empty());
    std::cout << w << std::endl;

}

int main() {
    // containers::my_vector<product::Product> w;
    // product::Product q("kek", 3, 4.3);
//  product::Product q("kek", 3, 4.3);
    // product::Product p("asdf", 2, 3.0);

    // w.push_back(p);
    // w.push_back(q);
    test_my_vector<int>();
    test_my_vector<product::Product>();
    test_my_vector_default_constructible<int>();
    //    std::cout << w << std::endl;

    return 0;
}
