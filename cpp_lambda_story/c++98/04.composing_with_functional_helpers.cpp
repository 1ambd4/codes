#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

// 最初想到的解决方式是提供一系列常用的算法
// 通过组合的方式实现需求
// std::plus<T>()
// std::minus<T>()
// std::less<T>()
// std::greater<T>()
// std::bind1st
// std::bind2nd
// and many more

int main()
{
    std::vector<int> v;
    v.push_back(3), v.push_back(7), v.push_back(1);
    const size_t smaller5 = 
        std::count_if(v.begin(), v.end(), std::bind2nd(std::less<int>(), 5));
    printf("there are %ld numbers smaller than 5\n", smaller5);

    // std::bind1st和std::bind2nd已经被标记为deprecated了
    // 取而代之的是原先boost::bind，好耶
    
    // 组合辅助函数的缺点是复杂和难用
    // 这就好像是又在c的语法之上定义了一种新的语言
    using std::placeholders::_1;
    const size_t res =
        std::count_if(v.begin(), v.end(),
                std::bind(std::logical_and<bool>(),
                    std::bind(std::greater<int>(), _1, 3),
                    std::bind(std::less_equal<int>(), _1, 7)));
    printf("there are %ld numbers greater than 3 and smaller than or equal 7\n", res);
    return 0;
}

