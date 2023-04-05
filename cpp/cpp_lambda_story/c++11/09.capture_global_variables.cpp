#include <iostream>
#include <vector>

int global = 37;

int main()
{
    std::cout << global << std::endl;
    auto foo1 = [=]() mutable noexcept {
        ++global;
    };
    foo1();
    std::cout << global << std::endl;

    // 也就说全局变量并不需要捕获
    const auto foo2 = []() noexcept {
        ++global;
    };
    foo2();
    std::cout << global << std::endl;

    // clang会报错
    // error: 'global' cannot be captured
    // because it does not have automatic storage duration 
    consr auto foo3 = [global]() noexcept {
        ++global;
    };
    foo3();
    std::cout << global << std::endl;

    return 0;
}

