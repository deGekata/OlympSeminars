#include <iostream>
#include <algorithm>


struct A {
    int x;
    A(int x) : x(x) { std::cout << "int ctor\n"; }
    A() : x(0) { std::cout << "default ctor\n"; }
    A(const A& other) : x(other.x) { std::cout << "copy ctor\n"; }
};

int main() {

    size_t cnt = 10;
    char test[sizeof(A) * cnt];

    for (size_t it = 0; it < 10; ++it) {
        new (test + sizeof(A) * it) A(23);
    }

    
    // data(new char[5 * 4]);
    // for_each(data, data + 5 * 4, [] (A* ptr) {
    //     new (ptr) A(t)
    // });

    // for (unsigned i = 0; i < 2; ++i)
    //     std::cout << p[i].x << std::endl;
}