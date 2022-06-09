#include "my_array.h"
#include <cstddef>

using lab_13::my_array;

template<typename T, std::size_t N>
void test_core() {
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.empty();
  ca.empty();
  a.size();
  ca.size();

  a.at(0);
  ca.at(0);
  a[0];
  ca[0];
  (void)static_cast<const T &>(a[0]);
  (void)static_cast<const T &>(ca[0]);
}

template<typename T, std::size_t N>
void test_assign() {
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.fill(T());

  a[0] = T();
  a[0] = a[0];
  a[0] = ca[0];
}

class NonCopyable {
 public:
  NonCopyable() {}
 private:
  NonCopyable(const NonCopyable&);
  NonCopyable& operator=(const NonCopyable);
};

template<std::size_t N>
void test_bitset() {
    my_array<bool, N> a;
    assert(a.size() == N);
    assert(sizeof(a) == N / 8 + (N % 8 != 0));
    assert(a.empty() == (N == 0));
    
    a.fill(true);
    
    my_array<bool, N> b;
    for (std::size_t i = 0; i < N; i++)
    	b[i] = true;
    
    for (std::size_t i = 0; i < N; i++) 
      assert(a.at(i) == b.at(i)); 
	  
    for (std::size_t i = 0; i < N; i++)
    	a[i] = i % 2;

    for (std::size_t i = 0; i < N; i += 2)
    	assert(!a[i]);
    
    for (std::size_t i = 1; i < N; i += 2)
    	assert(a[i]);
    
    my_array<bool, N> c(a);
    
    c[0] = a[0] = true;
    c.fill(1);
    for (std::size_t i = 0; i < N; i++)
    	assert(c.at(i));
    
    c.fill(0);
    c.at(N/2) = true;
    
    for (std::size_t i = 0; i < N; i++)
    	assert(c[i] == (i == N/2));
    
}

int main() {
  test_core<int, 10>();
  test_core<bool, 10>();
  test_core<NonCopyable, 10>();

  test_assign<int, 10>();
  test_assign<bool, 10>();

  test_bitset<1>();
  test_bitset<239>();
  test_bitset<100000>();
}
