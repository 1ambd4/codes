#include <iostream>
#include <vector>
#include <string>

struct Baz {
public:
    void foo() {
        // error: capture of non-variable ‘Baz::s’ 
        // error: ‘this’ was not captured for this lambda function
        // const auto lam = [s]() {
        //     std::cout << s;
        // };
        
        // 正确的做法是捕获this指针
        const auto lam = [this]() {
            std::cout << s;
        };
        lam();
    };

    std::string s;
};

int main()
{
    Baz b;
    b.s = "capture this pointer";
    b.foo();
    return 0;
}

