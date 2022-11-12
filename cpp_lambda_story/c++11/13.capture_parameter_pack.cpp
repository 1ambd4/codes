#include <iostream>
#include <vector>
#include <tuple>

template <class... Args>
void capture(Args... args) {
    const auto lambda = [args...] {
        const auto tup = std::make_tuple(args...);
        std::cout << "tuple size: " <<
            std::tuple_size<decltype(tup)>::value << std::endl;
        std::cout << "tuple 1st: " << std::get<0>(tup) << std::endl;
    };
    lambda();
};

int main()
{
    capture(1, 4, 2, 5, 3);
    capture("tuple test", 1.2f, 34);
    return 0;
}

