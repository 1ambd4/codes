#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main()
{
    // bind1st and bind2nd
    const auto plus_one1 = std::bind2nd(std::plus<int>(), 1);
    const auto one_minus1 = std::bind1st(std::minus<int>(), 1);
    std::cout << plus_one1(10) << ", " << one_minus1(10) << std::endl;

    // bind + placeholders
    // d对比之下，bind的优点在于支持多参数，且可以重新排序
    using std::placeholders:: _1;
    const auto plus_one2 = std::bind(std::plus<int>(), _1, 1);
    const auto one_minus2 = std::bind(std::minus<int>(), 1, _1);
    std::cout << plus_one2(10) << ", " << one_minus2(10) << std::endl;

    // 当然，写起来没有lambda自然
    auto plus_one3 = [](int b) { return b + 1; };
    auto one_minus3 = [](int b) { return 1 - b; };
    std::cout << plus_one3(10) << ", " << one_minus3(10) << std::endl;

    // c++14有了捕获初始化后可以这么写
    auto plus_one4 = [a = 1](int b) { return b + a; };
    auto one_minus4 = [a = 1](int b) { return a - b; };
    std::cout << plus_one4(10) << ", " << one_minus4(10) << std::endl;


    // 特别是一堆函数组合起来，可读性并不好
    // 而lambda就很是简洁

    const std::vector<int> v { 1, 4, 3, 2, 6, 7, 5, 9 };
    const auto val1 = std::count_if(v.begin(), v.end(),
            std::bind(std::logical_and<bool>(),
                std::bind(std::greater<int>(), _1, 2),
                std::bind(std::less<int>(), _1, 6)));  // _1错写成-1也不报错的啊
    std::cout << val1 << std::endl;

    const auto val2 = std::count_if(v.begin(), v.end(),
            [](int x) { return x > 2 && x < 6; });
    std::cout << val2 << std::endl;

    return 0;
}

