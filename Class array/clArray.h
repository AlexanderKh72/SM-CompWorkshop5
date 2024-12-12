#pragma once

class Array {
private:
	int* p;
	size_t length;

public:
	explicit Array(size_t n, int val);
	Array(const int* arr, size_t n);
	Array(const Array& a);
	~Array();

	void print() const;

	Array& operator=(const Array& arr);

	Array& add(const Array& arr);

	size_t getLength() const { return length; }
	const int* getP() const { return p; }
};

Array sum(const Array& a, const Array& b);
