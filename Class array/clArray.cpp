#include "clArray.h"
#include <iostream>
#include <cassert>

Array::Array(size_t n = 0, int val = 0) : length(n), p(nullptr) {
	if (length == 0) return;
	p = new int[length];
	for (size_t i = 0; i < length; ++i)
		p[i] = val;
}

Array::Array(const int* arr, size_t n) : length(n), p(nullptr) {
	if (!length) return;
	p = new int[length];
	const int* from{ arr };
	for (size_t i = 0; i < n; ++i)
		p[i] = arr[i];
}

Array::Array(const Array& a) : length(a.getLength()), p(nullptr) {
	if (length == 0) return;
	const int* from{ a.getP() };
	p = new int[length];
	for (size_t i = 0; i < length; ++i)
		p[i] = from[i];
}

Array::~Array() {
	delete[] p;
}

void Array::print() const {
	for (size_t i = 0; i < length; ++i)
		std::cout << p[i] << " ";
}

Array& Array::operator=(const Array& arr) {
	if (this == &arr) return (*this);
	delete[] p;
	length = arr.getLength();
	p = new int[length];
	const int* from = arr.getP();
	for (size_t i = 0; i < length; ++i) {
		p[i] = from[i];
	}
	return (*this);
}

Array& Array::add(const Array& arr) {
	assert(length == arr.getLength());
	const int* from{ arr.getP() };
	for (size_t i = 0; i < length; ++i)
		p[i] += from[i];
	return (*this);
}

Array sum(const Array& a, const Array& b) {
	Array res(a);
	return res.add(b);
}
