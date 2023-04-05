#include <iostream>
#include <vector>
#include <variant>

template <typename ... Ts>
struct overloaded: Ts ... {
    using Ts::operator()...;
};

template <typename ... Ts>
overloaded(Ts ...) -> overloaded<Ts ... >;

int main()
{
    const auto print_vistor = [](const auto& t) {
        std::cout << t << std::endl;
    };

    std::variant<int, float, std::string> int_float_string { "Hello" };

    std::visit(print_vistor, int_float_string);

    std::visit(overloaded{
            [](int& i) { i *= 2; },
            [](float& f) { f *= 2.0f; },
            [](std::string& s) { s += s; },
    }, int_float_string);

    std::visit(print_vistor, int_float_string);

    return 0;
}

