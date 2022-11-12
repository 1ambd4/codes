#include <iostream>
#include <vector>

template <typename T>
auto sum(T x) {
    return x;
}

template <typename T1, typename... T>
auto sum(T1 s, T... ts) {
    return s + sum(ts...);
}

int main()
{
    const auto sum_lambda = [](auto ... args) {
        std::cout << "sum of: " << sizeof...(args) << " numbers" << std::endl;
        return sum(args...);
    };
    // 变长参数会被扩展成如下形式
    // struct __anonymous {
    //     template <typename ... T>
    //     void operator()(T ... args) const {
    //     }
    // };
    std::cout << sum_lambda(1, 5, 2, 7, 3, 9, 6);
    return 0;
}

