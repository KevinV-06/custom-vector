#pragma once

#include <cstddef>

template <typename T>
class Vector {
public:
	Vector();
	~Vector();

	std::size_t size() const;
	std::size_t capacity() const;
	bool empty() const;

private:
	T* data_;
	std::size_t size_;
	std::size_t capacity_;
};

#include "vector.cpp"    