#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cassert>
#include <cstddef>
#include <stdint.h>

namespace lab_13 {

template<typename T, std::size_t N>
class my_array {
public:

	std::size_t size() const {
		return N;
	}

	bool empty() const {
		return size() == 0;
	}

	T& at(std::size_t index) {
		assert(index < size() && "out of bounds in my_array::at");
		return _data[index];
	}

	const T& at(std::size_t index) const {
		assert(index < N && "out of bounds in my_array::at");
		return _data[index];
	}	
	
	T& operator[](std::size_t index) {
		return _data[index];
	}

	const T& operator[](std::size_t index) const {
		return _data[index];
	}

	void fill(const T & value) {
		for (std::size_t i = 0; i < size(); i++)
			_data[i] = value;
	}

private:
	T _data[N]{};
};

}

#endif  // MY_ARRAY_H_
