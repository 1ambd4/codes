#include <iostream>
#include <vector>
#include <functional>
#include <memory>

using namespace std;

// 1.Captures with an initialiser.
// 2.Generic lambdas.
// 3.Default parameters for lambdas.
// 4.Return type as auto.

// c++14之前，return type没法子auto deduce
std::function<int(int)> create_lamda1(int x) {
    return [x](int param) noexcept {
        return x * param;
    };
}
// c++14之后，统统交给auto吧
auto create_lamda2(int x) noexcept {
    return [x](int param) noexcept {
        return x * param;
    };
}

struct Baz {
    auto foo() const {
        // 捕获初始化的另一个用处是捕获成员变量
        // 之前的话，只能捕获this
        // 前一个s在外部作用域
        // 后一个s在lambda的作用域里
        return [s = s] {
            std::cout << s << std::endl;
        };
    };

    std::string s;
};

int main()
{
    // 默认参数使得lambda更像普通函数了 
    // 有趣的是，gcc和clang在c++11的时候就以及支持了
    const auto lam1 = [](int x = 10) {
        std::cout << x << std::endl;
    };
    lam1();
    lam1(20);

    const auto lam2 = create_lamda1(10);
    const auto lam3 = create_lamda2(10);

    std::cout << "use functional: " << sizeof(lam2) << std::endl;
    std::cout << "use auto: " << sizeof(lam3) << std::endl;


    // 捕获列表初始化？
    int x = 10, y = 20;
    const auto lam4 = [z = x + y]() {
        // 并不会捕获x和y
        // std::cout << "x: " << x << std::endl;
        std::cout << "z: " << z << std::endl;
    };
    lam4();

    // 为啥不直接引用捕获呢？
    // 为了重命名么？
    const auto lam5 = [&z = x]() {
        std::cout << z << std::endl;
    };
    lam5();
    x = 0;
    lam5();

    // 由于引入了捕获初始化，可以将智能指针的所有权转移到lambda里
    std::unique_ptr<int> p(new int {10});
    const auto lam6 = [ptr = std::move(p)]() {
        std::cout << "pointer in lambda: " << ptr.get() << std::endl;
    };
    std::cout << "pointer in main(): " << p.get() << std::endl;
    lam6();

    const auto lam7 = Baz{"abc"}.foo();
    const auto lam8 = Baz{"xyz"}.foo();
    lam7();
    lam8();
    return 0;
}
