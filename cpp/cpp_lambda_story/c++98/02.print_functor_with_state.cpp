#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

// 仿函数不止可以保有状态
// 还可以通过构造函数的方式实现变量捕获
struct print_functor {
    print_functor() : cnt(0) { }
    print_functor(const std::string& str) : cnt(0), str(str) { }

    void operator() (int x) const {
        std::cout << x << std::endl;
        ++cnt;
    }

    // 保有状态
    mutable int cnt;
    // 捕获变量
    std::string str;
};

int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(4);

    const print_functor vistor1 = 
        std::for_each(v.begin(), v.end(), print_functor());
    printf("print_functor had been called %d times\n", vistor1.cnt);

    // 将欲捕获变量通过构造函数传递给仿函数
    // 还要注意值捕获和引用捕获的区别
    std::string str { "captured" };
    const print_functor vistor2 =
        std::for_each(v.begin(), v.end(), print_functor(str));
    printf("print_functor had been called %d times\n", vistor2.cnt);
    printf("variable: %s\n", vistor2.str);
    std::cout << "variable: " << vistor2.str << std::endl;
    return 0;
}

