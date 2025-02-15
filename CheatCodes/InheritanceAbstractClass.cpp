#include <iostream>

/*
** Abstract base class as it contains on pure virtual function
** 
** Its object CAN'T be instantiate
**
** Compilation command :  g++ -o InheritanceAbstractClass InheritanceAbstractClass.cpp 
*/
class Shape {
public:
   
    virtual void Area() = 0;  // Pure virtual function
   
};

/*
** Concrete class
**
** Since it is inheriting the Abstract class
** It is mandatory to implment Area() function
** other this class itself become Abstract
*/
class Square : public Shape {
double side;
public:
    Square(double s){
    	side = s;
    }
    void Draw() { std::cout << "Drawing Circle\n"; }
    void Area() {
	std::cout << "Area : " << (side*side) << std::endl;
    }
};



int main(){
   //Shape s ; //Not allowed as it is a abstract class
   Square s(4);
   s.Area();
   return 0;
}
