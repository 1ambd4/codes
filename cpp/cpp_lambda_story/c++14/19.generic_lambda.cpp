#include <iostream>
#include <vector>

// generic lambda，好耶

int main()
{
    const auto lam1 = [](auto x, int y) {
        std::cout << x << ", " << y << endl;
    };
    // 用auto来dudece参数类型
    // 会被扩展成如下形式
    // 每一个auto参数都会被扩展成一个模板参数
    // struct {
    //     template <typename T>
    //     void operator() (T x, int y) {
    //         std::cout << ", " << y << endl;
    //     }
    // }some_instance;
    return 0;
}

