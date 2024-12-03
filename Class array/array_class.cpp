// array_class.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "clArray.h"

int main()
{
    Array arr0(5, 1);
    arr0.print();
    std::cout << "\n";

    int p1[5] = { 1,2,3,4,5 };
    int p2[5] = { 5,4,3,2,1 };
    Array arr1(p1, 5);
    Array arr2(p2, 5);
    arr1.print();
    std::cout << "\n";
    arr2.print();
    std::cout << "\n";

    sum(arr1, arr2).print();
    std::cout << "\n";
    
    arr1.add(arr2).add(arr2);
    arr1.print();
    std::cout << "\n";
    
    arr1 = arr2;
    arr1.print();
    std::cout << "\n";
    
    arr1 = arr1;
    arr1.print();
    std::cout << "\n";

    return 0;
}
