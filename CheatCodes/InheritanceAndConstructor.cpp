#include <iostream>
/*
** Code to demonstrate inheritance and constructor calling sequence
**
** Compilation command :  g++ -o InheritanceAndConstructor InheritanceAndConstructor.cpp
*/
class Base {
public:
    Base() { std::cout << "Base Constructor\n"; }
    ~Base() { std::cout << "Base Destructor\n"; }
};

class Derived : public Base {
public:
    Derived() { std::cout << "Derived Constructor\n"; }
    ~Derived() { std::cout << "Derived Destructor\n"; }
};

int main() {
    Derived obj;
}

