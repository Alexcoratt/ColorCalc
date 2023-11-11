#ifndef SMART_POINTER_HPP
#define SMART_POINTER_HPP

#include <algorithm>

template <typename T>
class SmartPointer {
private:
	T * _ptr;
	unsigned long * _count;

public:
	SmartPointer(T *);
	SmartPointer(T &);
	SmartPointer(SmartPointer<T> const &);
	SmartPointer<T> & operator=(SmartPointer<T> const &);
	~SmartPointer();

	void swap(SmartPointer<T> &);

	T const * operator->() const;
	T * operator->();

	T const & operator*() const;
	T & operator*();

	T const * getPointer() const;
};

template <typename T>
SmartPointer<T>::SmartPointer(T * ptr) : _ptr(ptr), _count(new unsigned long(1)) {}

template <typename T>
SmartPointer<T>::SmartPointer(T & ptr) : _ptr(&ptr), _count(new unsigned long(1)) {}

template <typename T>
SmartPointer<T>::SmartPointer(SmartPointer<T> const & other) : _ptr(other._ptr), _count(other._count) {
	++(*_count);
}

template <typename T>
SmartPointer<T> & SmartPointer<T>::operator=(SmartPointer<T> const & other) {
	if (this != &other) {
		SmartPointer<T> tmp(other);
		swap(tmp);
	}
	return *this;
}

template <typename T>
SmartPointer<T>::~SmartPointer() {
	if (--(*_count) == 0) {
		delete _ptr;
		delete _count;
	}
}

template <typename T>
void SmartPointer<T>::swap(SmartPointer<T> & other) {
	std::swap(_ptr, other._ptr);
	std::swap(_count, other._count);
}

template <typename T>
T const * SmartPointer<T>::operator->() const  { return _ptr; }

template <typename T>
T * SmartPointer<T>::operator->() { return _ptr; }

template <typename T>
T const & SmartPointer<T>::operator*() const { return *_ptr; }

template <typename T>
T & SmartPointer<T>::operator*() { return *_ptr; }

template <typename T>
T const * SmartPointer<T>::getPointer() const { return _ptr; }

#endif
