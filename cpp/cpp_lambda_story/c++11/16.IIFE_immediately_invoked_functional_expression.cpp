#include <iostream>
#include <vector>

int main()
{
    int x = 1, y = 1;
    // 即用即抛
    // IIFE: Immediately Invoked Functional Expression
    [&]() noexcept {
        ++x, ++y;
    }();
    std::cout << x << ", " << y << std::endl;
    return 0;
}

