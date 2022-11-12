#include <algorithm>
#include <iostream>
#include <vector>

void foo(int x) { std::cout << x << std::endl; }
void foo(float f) { std::cout << f << std::endl; }

#define LIFT(foo) \
    [](auto&&... x) \
        noexcept(noexcept(foo(std::forward<decltype(x)>(x)...))) \
        -> decltype(foo(std::forward<decltype(x)>(x)...)) \
        { return foo(std::forward<decltype(x)>(x)...); }

int main()
{
    const std::vector<int> v { 1, 2, 4, 3, 5, 6, 7, 8};
    // 标准库里的算法虽然方便好用，但无法解决函数重载的问题
    // unresolved overloaded function type
    // std::for_each(v.begin(), v.end(), foo);  // 无法通过编译

    // 虽然对于短小的代码可以使用lambda
    // 但这样一来无法应付需要重载函数的场景
    std::for_each(v.begin(), v.end(), [](int ){
            });

    
    // 何必苦恼，还有完美转发！
    std::for_each(v.begin(), v.end(), [](auto&& x) {
                return foo(std::forward<decltype(x)>(x));
            });

    std::cout << std::endl;

    // 多数场景至此都可满足，如果还需要异常以及不定长参数的支持
    // 可以用宏，还少了函数调用开销
    // 为啥宏名要这么奇怪？
    std::for_each(v.begin(), v.end(), LIFT(foo));

    return 0;
}

