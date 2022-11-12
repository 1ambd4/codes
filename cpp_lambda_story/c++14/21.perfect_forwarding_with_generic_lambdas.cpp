#include <iostream>
#include <vector>
#include <string>

void foo(const std::string& ) {
    std::cout << "foo(const string&)" << std::endl;
}

void foo(const std::string&& ) {
    std::cout << "foo(const string&&)" << std::endl;
}

int main()
{
    const auto call = [](auto&& str) {
        std::cout << "call foo() on: " << str << std::endl;
        foo(std::forward<decltype(str)>(str));
    };

    const std::string str = "Hello World!";
    call(str);
    call("Hello World!");
    return 0;
}

