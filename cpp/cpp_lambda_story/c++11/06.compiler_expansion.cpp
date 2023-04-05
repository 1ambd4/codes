#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>
#include <type_traits>

int main()
{
    struct {
        void operator() (int x) const {
            std::cout << x << std::endl;
        }
    } functor_instance;

    const std::vector<int> v { 1, 4, 2, 3 };
    std::for_each(v.begin(), v.end(), functor_instance);

    // 可以在C++ Insights中看到编译器对lambda表达式扩展后的结果
    std::for_each(v.begin(), v.end(), [](int x) {
            std::cout << x << std::endl;
            });

    const auto lambda1 = [](){};
    const auto lambda2 = [](){};
    static_assert(!std::is_same<decltype(lambda1), decltype(lambda2)>::value,
            "must be different!");
    static_assert(std::is_same_v<double, decltype(1.2)>);

    std::function<double(int)> func1 = [](int a) -> double { return 2.0 * a; };
    const auto lambd = [](int a) -> double { return 2.0 * a; };
    printf("sizeof function is %ld, sizeof lambda is %ld\n",
            sizeof(func1), sizeof(lambd));

    // 值捕获捕获到的值是定义时的值
    // 引用捕获捕获到值是使用时的值
    int val = 37;
    const auto lambd1 = [val]() {
        std::cout << "by value: " << val << std::endl;
    };
    const auto lambd2 = [&val]() {
        std::cout << "by ref: " << val << std::endl;
    };
    val = 73;
    lambd1();
    lambd2();
    return 0;
}

