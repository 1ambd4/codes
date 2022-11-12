#include <algorithm>
#include <iostream>
#include <vector>

// 古早时期的c++98中可调用对象只有函数指针和仿函数
void print_func(int x)
{
    std::cout << x << std::endl;
}
// 函数指针的写法很容易写成仿函数

int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(4);
    std::for_each(v.begin(), v.end(), print_func);
    return 0;
}

