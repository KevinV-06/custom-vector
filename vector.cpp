
template<typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {

}

template<typename T>
Vector<T>::~Vector() {
	std::destroy(data_, data_ + size_);
	::operator delete(data_);
}

template<typename T>
std::size_t Vector<T>::size() const{
	return size_;
}

template<typename T>
std::size_t Vector<T>::capacity() const {
	return capacity_;
}

template<typename T>
bool Vector<T>::empty() const {
	return size_ == 0;
}