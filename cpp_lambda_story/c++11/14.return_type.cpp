#include <iostream>
#include <vector>
#include <type_traits>

int main()
{
    // two return statement
    // but they all point to double so the compiler can deduce the type
    const auto baz = [](int x) noexcept {
        if (x < 20) {
            return x * 1.1;
        } else {
            return x * 2.1;
        }
    };
    static_assert(std::is_same<double, decltype(baz(10))>::value,
            "has to be the same!");
    return 0;
}

