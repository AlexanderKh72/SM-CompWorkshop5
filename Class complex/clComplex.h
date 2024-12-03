#pragma once
#include <functional>
#include <iostream>

class Complex {
private:
	double Re;
	double Im;

public:
	Complex(double re = 0, double im = 0) : Re(re), Im(im) { std::cout << "c\n"; }
	Complex(const Complex& z) : Re(z.getRe()), Im(z.getIm()) { std::cout << "cc\n"; }
	
	~Complex() { std::cout << "~c\n"; }
	
	void set(double a, double b) { Re = a; Im = b; }
	double getRe() const { return Re; }
	double getIm() const { return Im; }

	void print() const;

	Complex& add(const Complex& z);
	Complex& assign(const Complex& z);

	Complex& operator=(const Complex& z) { std::cout << "=\n";  return assign(z); }

	double mod2() const;
};

Complex sum(const Complex& z1, const Complex& z2);
Complex sum_test(Complex z1, const Complex& z2);

int comp_cplx_mod(const Complex& z1, const Complex& z2);
void sort(Complex* arr, size_t n, std::function<int(const Complex&, const Complex&)> comp);
