#include <iostream>

#include "my_vector.hpp"

namespace product {

class Product {
public:
    Product(const char* name, int quantity, double price);

private:
    char *name_;
    int quantity_;
    double price_;
};

}  // namespace product

int main() {
	containers::my_vector<int> v;
	v.push_back(2);
	const int n{3};
	v.push_back(n);
    v.push_back(2);
    v.push_back(2);
    v.resize(5);
    std::cout << v << std::endl;
    std::cout << v.capacity() << " " << v.size() << std::endl;
    v.resize(10);
    std::cout << v << std::endl;
    std::cout << v.capacity() << " " << v.size() << std::endl;
    v.resize(3);
    std::cout << v << std::endl;
    std::cout << v.capacity() << " " << v.size() << std::endl;
    containers::my_vector<int> w;
    w = v;
	// std::cout << v[0] << " "  << v[1] << v[2] << " " << v[3] << " "  <<std::endl;
    std::cout << v << std::endl;
    std::cout << w << std::endl;
    v.clear();
    std::cout << v.empty() << std::endl;
    //test_my_vector<int>(5, 10);
    //test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));

    return 0;
}
