#include <iostream>

class Bird{
    public:
        Bird(const std::string &name_in) : age(0), name(name_in) {

        }

        std::string get_name() const {
            return name;
        }

        int get_age() const {
            return age;
        }

        void have_birthday(){
            ++age;
        }

        void talk() const {
            std::cout << "tweet" << std::endl;
        }

    private:
        int age;
        std::string name;
};


class Chicken : public Bird {
    public:
        Chicken(const std::string &name_in) : age(0), name(name_in), roads_crossed(0){
            //Constuctor
        }

        std::string get_name() const {
            return name;
        }

        int get_age() const {
            return age;
        }

        void cross_road(){
            ++roads_crossed;
        }

        void talk() const {
            std::cout << "bawk" << std::endl;
        }

    private:
        int age;
        std::string name;
        int roads_crossed;
};

class Duck : public Bird {
    public:
        Duck(const std::string &name_in) : age(0), name(name_in), num_ducklings(0){
            //Constuctor
        }

        std::string get_name() const {
            return name;
        }

        int get_age() const {
            return age;
        }

        void have_babies(){
            ++num_ducklings;
        }

        void talk() const {
            std::cout << "quack" << std::endl;
        }

    private:
        int age;
        std::string name;
        int num_ducklings;
};


#https://eecs280staff.github.io/notes/09_Inheritance.html