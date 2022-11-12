#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main()
{
    // 递归调用lambda
    //
    // 最经典的递归例子，阶乘
    // error: use of ‘factorial’ before deduction of ‘auto’ 
    // auto factorial = [&factorial](int n) {
    //     return n > 1 ? n * factorial(n - 1) : 1;
    // };
    //
    //
    // 报错原因把lambda展开就很明显了
    // factorial类型推导需要等到lambda定义完
    // 但lambda里面又调用了factorial
    // struct fact {
    //     int operator()(int n) const {
    //         return n > 1 ? n * factorial(n-1) : 1;
    //     }
    // };
    //
    // auto factorial = fact {};
    

    // 如果非要实现递归调用lambda,有两个小trick
    // 1.with std::function and capturing it
    // 2.with internal lambda and passing it as a generic parameter
    //
    // 先来看方法1，手动写出factorial的类型，省去自动类型推导
    const std::function<int(int)> factorial1 = [&factorial1](int n) {
        return n > 1 ? n * factorial1(n-1) : 1;
    };
    std::cout << factorial1(3) << std::endl;


    // 方法2是在闭包里再定义一个泛型闭包
    // 有lisp的感觉了
    const auto factorial2 = [](int n) noexcept {
        const auto fact_impl = [](int n, const auto& impl) noexcept -> int {
            return n > 1 ? n * impl(n-1, impl) : 1;
        };
        return fact_impl(n, fact_impl);
    };
    std::cout << factorial2(3) << std::endl;

    return 0;
}

