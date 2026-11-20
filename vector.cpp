#include "vector.h"

template <typename T, typename Alloc>
Vector<T, Alloc>::Vector() : alloc_(), data_(nullptr), size_(0), capacity_(0) {
}

template <typename T, typename Alloc>
Vector<T, Alloc>::Vector(const Alloc& alloc) : alloc_(alloc), data_(nullptr), size_(0), capacity_(0) {
}

template <typename T, typename Alloc>
Vector<T, Alloc>::~Vector() {
	// Destroys all elements, no elements were constructed past size_
	for (std::size_t i = 0; i < size_; ++i) {
		traits::destroy(alloc_, data_ + i);
	}
	// Frees entire block of memory
	if (data_ != nullptr) {
		traits::deallocate(alloc_, data_, capacity_);
	}
}


template <typename T, typename Alloc>
Vector<T, Alloc>::Vector(const Vector& other) : Vector(traits::select_on_container_copy_construction(other.alloc_)) {
	if (other.size_ == 0) {
		return;
	}
	reserve(other.size_);
	for (std::size_t i = 0; i < other.size_; ++i) {
		traits::construct(alloc_, data_ + i, other.data_[i]);
		++size_;
	}
}

template <typename T, typename Alloc>
Vector<T, Alloc>& Vector<T, Alloc>::operator=(const Vector& other) {
	if (this == &other) {
		return *this;
	}
	Vector temp(other);
	std::swap(this->data_, temp.data_);
	std::swap(this->capacity_, temp.capacity_);
	std::swap(this->size_, temp.size_);
	return *this;
}

template <typename T, typename Alloc>
Vector<T, Alloc>::Vector(Vector&& other) noexcept : alloc_(std::move(other.alloc_)), data_(other.data_), size_(other.size_), capacity_(other.capacity_){
	other.data_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
}

template <typename T, typename Alloc>
Vector<T, Alloc>& Vector<T, Alloc>::operator=(Vector&& other) noexcept {
	if (this == &other) {
		return *this;
	}
	Vector temp(std::move(other));
	std::swap(this->alloc_, temp.alloc_);
	std::swap(this->data_, temp.data_);
	std::swap(this->size_, temp.size_);
	std::swap(this->capacity_, temp.capacity_);
	return *this;
}
template <typename T, typename Alloc>
std::size_t Vector<T, Alloc>::size() const{
	return size_;
}

template <typename T, typename Alloc>
std::size_t Vector<T, Alloc>::capacity() const {
	return capacity_;
}

template <typename T, typename Alloc>
bool Vector<T, Alloc>::empty() const {
	return size_ == 0;
}

template <typename T, typename Alloc>
void Vector<T, Alloc>::reserve(std::size_t new_cap) {
	// New block should only be allocated if the new capacity is greater than the current capacity
	if (capacity_ >= new_cap) {
		return;
	}
	T* new_data = traits::allocate(alloc_, new_cap);
	// Moves if the move constructor is noexcept, copies otherwise, so a throw doesn't lose the original state
	std::size_t i = 0;
	try {
		for (; i < size_; ++i) {
			traits::construct(alloc_, new_data + i, std::move_if_noexcept(data_[i]));
		}
	}
	catch (...) {
		// If an exception is thrown, destroy all elements that were constructed in the new block and free the memory
		for (std::size_t j = 0; j < i; ++j) {
			traits::destroy(alloc_, new_data + j);
		}
		traits::deallocate(alloc_, new_data, new_cap);
		throw;
	}
	for (std::size_t n = 0; n < size_; ++n) {
		traits::destroy(alloc_, data_ + n);
	}
	if (data_ != nullptr) {
		traits::deallocate(alloc_, data_, capacity_);
	}
	data_ = new_data;
	capacity_ = new_cap;
}

template <typename T, typename Alloc>
void Vector<T, Alloc>::push_back(const T& value) {
	// Reserve must be called if there's no capacity left
	if (size_ == capacity_) {
		// Saved to temp in case value is an element of the current vector, as reserve frees the old block of memory
		T temp = value;
		// Grow by a factor of 2, other than when starting empty
		if (capacity_ == 0) {
			reserve(1);
		}
		else {
			reserve(capacity_ * 2);
		}
		// Since temp is going to be destroyed, use move for faster speed.
		traits::construct(alloc_, data_ + size_, std::move(temp));
	}
	else {
		traits::construct(alloc_, data_ + size_, value);
	}
	++size_;
}

template <typename T, typename Alloc>
void Vector<T, Alloc>::push_back(T&& value) {
	if (size_ == capacity_) {
		// Same as const T& version.
		T temp = std::move(value);
		if (capacity_ == 0) {
			reserve(1);
		}
		else {
			reserve(capacity_ * 2);
		}
		traits::construct(alloc_, data_ + size_, std::move(temp));
	}
	else {
		// Since value has a name it's treated as an lvalue, so move makes it an rvalue so the move constructor runs
		traits::construct(alloc_, data_ + size_, std::move(value));
	}
	++size_;
}

template <typename T, typename Alloc>
T& Vector<T, Alloc>::operator[](std::size_t index) {
	return data_[index];
}

template <typename T, typename Alloc>
const T& Vector<T, Alloc>::operator[](std::size_t index) const {
	return data_[index];
}

