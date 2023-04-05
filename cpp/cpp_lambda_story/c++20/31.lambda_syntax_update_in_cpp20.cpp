#include <iostream>
#include <vector>

// C++20可以在参数列表后添加consteval
// 且可以在捕获列表后声明模板参数列表
// The syntax of lambda expression
// []<tparams>() specifiers exception attr -> ret { /* code; */ }
// ^    ^      ^  ^                            ^
// |    |      |  |                            |
// |    |      |  |                            optional: trailing return type
// |    |      |  optional: mutable, noexcept, attributes, constexpr, consteval
// |    |      paramter list
// |    optioanl: template parameter list
// lambda introducer with an optional capture list

using namespace std;

int main()
{
    const int x = 10;
    auto lambda1 = [](int x) consteval -> int { return x + x; };
    std::cout << lambda1(x) << std::endl;

    // template lambda
    // c++14的时候，可以用auto不太优雅的实现泛型lambda
    auto func1 = [](auto& vec) {
        std::cout << "size of vector: " << vec.size() << ", "
            << "capacity of vector: " << vec.capacity() << std::endl;
    };

    std::vector<int> nums(10);
    // 正常丢一个vector进去是没问题的
    func1(nums);
    // 但如果是其他类型呢？比如int
    // 会过不了编译，而且报错可读性一般（clang比gcc可读性好很多
    // func1(x);
    
    // 到了C++20，可以这么写
    // 别的不讲，代码的可读性就上来了啊
    auto func2 = []<typename T>(std::vector<T>const &vec) {
        std::cout << "size of vector: " << vec.size() << ", "
            << "capacity of vector: " << vec.capacity() << std::endl;
    };
    func2(nums);
    // func2(x);

    // Z4mainEUlRT_E0_
    std::cout << typeid(func1).name() << std::endl;
    // Z4mainEUlRKSt6vectorIT_SaIS0_EEE1_
    std::cout << typeid(func2).name() << std::endl;

    // C++20模板参数列表还可以方便的拿到参数类型
    auto func3 = [](auto const& x) {
        using T = std::decay_t<decltype(x)>;  // 需要显式推导
        T copy = x;
        T::static_function();
        using Iterator = typename T::itertor;
    };
    auto func4 = []<typename T>(T const& x) {
        T copy = x;
        T::static_function();
        using Iterator = typename T::iterator;
    };
    // 完美转发也方便了
    auto func5 = [](auto&& ... args) {  // c++17
        return func(std::forward<decltype(args)>(args)...);
    };
    auto func6 = []<typename ... T>(T&& args) { // c++20
        return func(std::forward<T>(args)...);
    };
    return 0;
}

