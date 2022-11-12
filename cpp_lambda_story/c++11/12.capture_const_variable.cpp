#include <iostream>
#include <vector>

int main()
{
    // if you captured a const variable
    // then the constness is preserved

    const int x = 10;
    auto foo = [x]() mutable {
        std::cout << std::is_const<decltype(x)>::value << std::endl;
    };
    foo();
    return 0;
}

