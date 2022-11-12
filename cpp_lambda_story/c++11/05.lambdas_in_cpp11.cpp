#include <iostream>
#include <vector>

// 十年之后的C++11终于支持用局部类型初始化模板了
// 当然，更棒的是，C++11新增了lambda expression
//
// C++11引入了新的语法
// 使得编译器可以将lambda expression扩展为匿名且透明的仿函数对象
//
// The syntax of lambda expression
// []() specifiers exception attr -> ret { /* code; */ }
// ^ ^  ^                            ^
// | |  |                            |
// | |  |                            optional: trailing return type
// | |  optional: mutable, exception specification or noexcept, attributes
// | paramter list
// |
// lambda introducer with an optional capture list
//
//
// Core definitons:
//
// 1.The evaluation of a lambda-expression result in a prvalue temporary.
// This temporary is called the closure object.
// lambda表达式的计算结果是一个纯右值，被称作闭包对象
//
// 2.The type of the lambda-expression(which is also the type of
// the closure object) is a unique, unnamed non-union class type,
// called the closure type.
// 每一个lambda表达式的类型都是匿名且独一无二的

int main()
{
    auto simplest_lambda1 = []{};
    auto simplest_lambda2 = []{};
    std::cout << typeid(simplest_lambda1).name() << std::endl;
    std::cout << typeid(simplest_lambda2).name() << std::endl;

    int x = 37;
    // []() mutable noexcept {}: ok
    // []() noexcept mutable {}: not ok
    [x](int a,int b) mutable noexcept -> bool {
        ++x;
        return a < b;
    }(1, 2);
    std::cout << x << std::endl;

    auto labda1 = []() [[nodiscard]] { return 0; };
    return 0;
}

