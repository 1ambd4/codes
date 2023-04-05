#include <iostream>
#include <vector>

int main()
{
    // 闭包类型重载的operator()运算符默认是const修饰的
    // 如果想要修改捕获的变量，应当用mutable修饰
    // 当然喽，这时候auto前也不要加const了
    int val = 233;
    auto lambda1 = [val]() mutable {
        ++val;
    };

    // 引用捕获就不考虑这么多了
    const auto lambda2 = [&val]() {
        ++val;
    };

    lambda1();
    lambda2();

    std::cout << val << std::endl;

    return 0;
}

