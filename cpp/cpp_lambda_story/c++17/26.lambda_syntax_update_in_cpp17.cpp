#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <functional>

// C++17引入了新的语法可以在参数列表后加constexpr
//
// The syntax of lambda expression
// []() specifiers exception attr -> ret { /* code; */ }
// ^ ^  ^                            ^
// | |  |                            |
// | |  |                            optional: trailing return type
// | |  optional: mutable, noexcept, attributes, constexpr
// | paramter list
// |
// lambda introducer with an optional capture list


// noexcept检测
template <typename callable>
void call_with_10(callable&& fn) {
    if constexpr (std::is_nothrow_invocable_v<callable, int>) {
        std::cout << "calling fn() with optimisation" << std::endl;
        fn(10);
    } else {
        std::cout << "calling fn() normally" << std::endl;
        fn(10);
    }
}


// constexpr
template <typename Range, typename Func, typename T>
constexpr T Accumulate(Range&& range, Func func, T init) {
    for (auto && elem : range) {
        init += func(elem);
    }
    return init;
}

// capture of *this
struct Baz {
    auto foo() {
        // 捕获*this
        return [*this]() { std::cout << s << std::endl; };
    }

    std::string s;
};

int main()
{
    // c++17里异常声明进类型系统了
    // 这导致抛不抛异常构成重载
    // 主要是为了方便编译器根据异常抛出情况做优化
    int x { 10 };
    const auto lambda1 = [&x](int y) noexcept { x += y; };
    const auto lambda2 = [&x](int y) {
        std::cout << "lambda2 with x = " << x << std::endl;
        x += y;
    };
    call_with_10(lambda1);
    call_with_10(lambda2);


    constexpr std::array arr { 1, 2, 3 };
    constexpr auto sum = Accumulate(arr, [](auto i) {
                return i * i;
            }, 0);
    static_assert(sum == 14);


    // 前面递归求阶乘的例子改成constexpr
    constexpr auto factorial = [](int n) {
        constexpr auto fact_impl = [](int n, const auto& impl) -> int {
            return n > 1 ? n * impl(n-1, impl) : 1;
        };
        return fact_impl(n, fact_impl);
    };
    static_assert(factorial(5) == 120);

    const auto baz1 = Baz{"abc"}.foo();
    const auto baz2 = Baz{"xyz"}.foo();
    baz1();
    baz2();

    // Updates to IIFE
    // Immediately Invoked Functional Expression
    const auto var1 = [](){ return 0; }();  // c++17前写法，函数调用容易忘记
    const auto var2 = std::invoke([](){ return 0; }); // c++17的写法
                                                      // invoke定义于functioanl
    
    // 不定长参数的支持也更优雅了
    const auto variadic_sum = [](auto ... args) {
        std::cout << "sum of: " << sizeof...(args) << " numbers" << std::endl;
        return (args + ... + 0);
    };
    std::cout << variadic_sum(1, 2, 3, 4, 5) << std::endl;

    // c++14
    // template <typename T>
    // auto sum(T x) {
    //     return x;
    // }
    // template <typename T1, typename... T>
    // auto sum(T1 s, T... ts) {
    //     return s + sum(ts...);
    // }
    // const auto sum_lambda = [](auto ... args) {
    //     std::cout << "sum of: " << sizeof...(args) << " numbers" << std::endl;
    //     return sum(args...);
    // };
    // std::cout << sum_lambda(1, 5, 2, 7, 3, 9, 6);
    
    const auto printer = [](auto ... args) {
        (std::cout << ... << args) << std::endl;
    };
    // 输出糊到一起了，改
    printer(1, 2, 3, 4, 5, 6, 7);

    // fold expression
    const auto printer0 = [](auto ... args) {
        const auto print_elem = [](auto elem) {
            std::cout << elem << ", ";
        };
        (print_elem(args), ...);
        std::cout << std::endl;
    };
    printer0(1, 2, 3, 4, 5, 6, 7);

    // 简写如下
    const auto printer1 = [](auto ... args) {
        ((std::cout << args << ", "), ...);
        std::cout << std::endl;
    };
    printer1(1, 2, 3, 4, 5, 6, 7);

    // 不想输出最后一个逗号可以这样
    const auto printer2 = [](auto first, auto ... args) {
        std::cout << first;
        ((std::cout << ", " << args), ...);
        std::cout << std::endl;
    };
    printer2(1, 2, 3, 4, 5, 6, 7);

    return 0;
}
