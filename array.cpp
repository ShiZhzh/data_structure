#include<iostream>
#include<array>
#include<tuple>

void test1();
void test2();
void test3();

int main(){
    test1();
    test2();
    test3();
    return 0;
}

void test1(){
    std::array<int, 5> arr;
 
    arr.fill(5);  // fill
 
    std::cout << "array values: ";
    for (auto i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
 
    std::array<int, 3> first = {1, 2, 3};
    std::array<int, 3> second = {6, 5, 4};
 
    std::cout << "first  array values: ";
    for (auto it = first.begin(); it != first.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
 
    std::cout << "second array values: ";
    for (auto it = second.begin(); it != second.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
 
    first.swap(second);  // swap
 
    std::cout << "swap array success!" << std::endl;
 
    std::cout << "first  array values: ";
    for (auto it = first.begin(); it != first.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
 
    std::cout << "second array values: ";
    for (auto it = second.begin(); it != second.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

}

void test2(){
    std::array<int,5> a = {10, 20, 30, 40, 50};
    std::array<int,5> b = {10, 20, 30, 40, 50};
    std::array<int,5> c = {50, 40, 30, 20, 10};
 
    if (a == b) {
        std::cout << "a == b" << std::endl;
    } else {
        std::cout << "a != b" << std::endl;
    }
 
    if (a == c) {
        std::cout << "a == c" << std::endl;
    } else {
        std::cout << "a != c" << std::endl;
    }
 
    if (a < c) {
        std::cout << "a < c" << std::endl;
    } else {
        std::cout << "a >= c" << std::endl;
    }

}

void test3(){
    std::array<int,3> myarray = {10, 20, 30};
    std::tuple<int, int, int>mytuple(10, 20, 30);
 
    std::tuple_element<0, decltype(myarray)>::type myelement;  // int myelement
 
    myelement = std::get<2>(myarray);
    std::get<2>(myarray) = std::get<0>(myarray);
    std::get<0>(myarray) = myelement;
 
    std::cout << "first element in myarray: " << std::get<0>(myarray) << std::endl;
    std::cout << "first element in mytuple: " << std::get<0>(mytuple) << std::endl;

}