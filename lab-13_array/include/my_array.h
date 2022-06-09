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

bool get_bit(uint8_t value, std::size_t index) {
	return (value >> index) & 1;
}

void set_bit(uint8_t& value, std::size_t index, bool new_bit) {
	if (get_bit(value, index) != new_bit)
		value ^= 1 << index;
}

template<std::size_t N>
class my_array<bool, N> {
public:

	std::size_t size() const {
		return N; 
	}

	bool empty() const {
		return size() == 0;
	}

	class bool_reference {
	public:
		bool_reference(uint8_t& block_value, std::size_t position_in_block) : 
			block_value(block_value), 
			position_in_block(position_in_block) {}

		operator bool() const {
			return get_bit(block_value, position_in_block);
		}

		bool_reference& operator=(bool new_bit) {
			set_bit(block_value, position_in_block, new_bit);
			return *this;
		}

		bool_reference& operator=(bool_reference& source) {
			return *this = (bool)source;
		}

	private:
		uint8_t& block_value;
		std::size_t position_in_block; 
	};

	bool_reference operator[](std::size_t index) {
		return bool_reference(_data[get_block_id(index)], get_position_in_block(index));
	}

	bool operator[](std::size_t index) const {
		return get_bit(_data[get_block_id(index)], get_position_in_block(index));
	}

	bool_reference at(std::size_t index) {
		return bool_reference(_data.at(get_block_id(index)), get_position_in_block(index));
	}

	bool at(std::size_t index) const {
		return get_bit(_data.at(get_block_id(index)), get_position_in_block(index)); 
	}

	void fill(bool value) {
		if (value)
			_data.fill((1 << BITS_IN_BLOCK) - 1);
		else
			_data.fill(0);
	}

private:
	static const std::size_t BITS_IN_BLOCK = 8;

	static std::size_t get_block_id(std::size_t index) {
		return index / BITS_IN_BLOCK;
	}

	static std::size_t get_position_in_block(std::size_t index) {
		return index % BITS_IN_BLOCK;
	}

	//size of _data is the minimum x such that BITS_IN_BLOCK * x >= N
	my_array<uint8_t, (N + BITS_IN_BLOCK - 1) / BITS_IN_BLOCK> _data;  	
};

}

#endif  // MY_ARRAY_H_
