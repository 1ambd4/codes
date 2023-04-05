#include <iostream>
#include <vector>

int main()
{
    // 捕获静态变量和全局变量的问题差不多
    static int static_int = 23;
    std::cout << static_int << std::endl;

    auto foo1 = [=]() mutable noexcept {
        ++static_int;
    };
    foo1();
    std::cout << static_int << std::endl;

    const auto foo2 = []() noexcept {
        ++static_int;
    };
    foo2();
    std::cout << static_int << std::endl;

    const auto foo3 = [static_int]() noexcept {
        ++static_int;
    };
    foo3();
    std::cout << static_int << std::endl;

    return 0;
}

