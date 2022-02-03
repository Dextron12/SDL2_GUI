#include <overloading.hpp>

void Number::add(int x, int y){
    std::cout << (x + y);
}

void Number::add(float x, float y){
    std::cout << (x + y) << std::endl;
}

void Number::sub(int x, int y){
    std::cout << (x - y) << std::endl;
}

int main(int argc, char* argv[]){
    Number::add(0.98f, 2.04f);
    Number::add(10, 50);
}