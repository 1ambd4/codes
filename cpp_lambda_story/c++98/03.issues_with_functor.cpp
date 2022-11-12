#include <algorithm>
#include <iostream>
#include <vector>

// 仿函数虽然能用，但不优雅
// 因为这使得调用处和定义处相隔万里
//
// 尝试将结构体定义于函数内部呢？

int main()
{
    struct print_functor {
        void operator() (int x) const {
            std::cout << x << std::endl;
        }
    };

    std::vector<int> v(10, 1);
    // 但在c++98/03的时候，不支持使用局部类型来初始化模板
    std::for_each(v.begin(), v.end(), print_functor());
    // 好消息是，之后支持了
    return 0;
}

