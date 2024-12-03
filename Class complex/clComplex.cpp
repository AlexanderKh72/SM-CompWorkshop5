#include "clComplex.h"
#include <iostream>

void Complex::print() const {
	std::cout << Re << " + " << Im << "i\n";
}

Complex& Complex::add(const Complex& z) {
	Re += z.getRe();
	Im += z.getIm();
	return (*this);
}

Complex& Complex::assign(const Complex& z) {
	set(z.getRe(), z.getIm());
	return (*this);
}

Complex sum(const Complex& z1, const Complex& z2) {
	Complex res(z1);
	return res.add(z2);
}

Complex sum_test(Complex z1, const Complex& z2) {
	return z1.add(z2);
}

double Complex::mod2() const {
	return Re * Re + Im * Im;
}

int comp_cplx_mod(const Complex& z1, const Complex& z2) {
	return z1.mod2() > z2.mod2() ? 1 : -1;
}

void sort(Complex* arr, size_t n, std::function<int(const Complex&, const Complex&)> comp) {
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n - i - 1; ++j)
			if (comp(arr[j], arr[j + 1]) > 0) {
				Complex temp(arr[j]);
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
}


