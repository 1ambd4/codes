#include <algorithm>
#include <iostream>
#include <vector>

// 单纯的函数指针的缺点是无状态
struct print_functor {
    void operator() (int x) const {
        std::cout << x << std::endl;
    }
};

int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(4);
    std::for_each(v.begin(), v.end(), print_functor());
    return 0;
}

