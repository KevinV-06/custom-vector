#pragma once

#include <cstddef>
#include <memory>
#include <utility>

template <typename T, typename Alloc = std::allocator<T>>
class Vector {
public:
	using traits = std::allocator_traits<Alloc>;
	using iterator = T*;
	using const_iterator = const T*;

	Vector();
	// Lets user pass a specific allocator instance to the vector.
	explicit Vector(const Alloc& alloc);
	~Vector();
	
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);

	Vector(Vector&& other) noexcept;
	Vector& operator=(Vector&& other) noexcept;

	std::size_t size() const;
	std::size_t capacity() const;
	bool empty() const;

	void reserve(std::size_t new_cap);
	void push_back(const T& value);
	void push_back(T&& value);
	T& operator[](std::size_t index);
	const T& operator[](std::size_t index) const;

	iterator begin() noexcept;
	iterator end() noexcept;
	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;
	const_iterator cbegin() const noexcept;
	const_iterator cend() const noexcept;

private:
	Alloc alloc_;
	// Start of the allocated block of memory.
	T* data_;
	// Number of elements currently in the vector.
	std::size_t size_;
	// Number of elements that can be stored in the currently allocated memory block.
	std::size_t capacity_;
};

#include "vector.cpp"    