// complex_class.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "clComplex.h"

int main()
{   
    //Complex z1(1, 1), z2(1, 2), z3(2, 4);
    //Complex arr[3] = {z2, z1, z3};

    //z1.print();
    //std::cout << "\n";
    //z1.add(z2).add(z3);
    //z1.print();
    //std::cout << "\n";
    //sum(z1, z2).print();
    //std::cout << "\n\n";

    //sort(arr, 3, comp_cplx_mod);
    //for (int i = 0; i < 3; ++i, std::cout << "\n")
    //    arr[i].print();

    Complex c1(2), c2;
    //c2.assign(c1);
    c2 = c1;
    c2.print();
    return 0;
}
