#include <iostream>

#include "Events.hpp"


class A{
    void getMouse(){
        std::cout << "Hello World" << std::endl;
    }
};

int main(int argc, char* argv){
    A a;
    void* ptr = &a;
    getMouse(&A::getMouse, ptr);
}