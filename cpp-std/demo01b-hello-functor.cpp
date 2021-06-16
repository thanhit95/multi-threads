#include <iostream>
#include <string>
#include <thread>

using namespace std;



class Foo {
public:
    void operator()(string message) {
        cout << message << endl;
    }
};



int main() {
    Foo foo;

    thread th1(foo, "ham");
    thread th2(foo, "eggs");

    th1.join();
    th2.join();

    return 0;
}