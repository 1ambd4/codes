#include <iostream>
#include <vector>
#include <map>

using namespace std;

// recursion
//   1、可以转化为小规模同问题
//   2、有种植条件

// 经典的上楼梯问题（虽然一般会举成动规例子
// f(n) = f(n-1) + f(n-2),  f(1) = 1,  f(2) = 2;
int func1(int n)
{
    if (n == 1) return 1;
    if (n == 2) return 2;

    return func1(n-1) + func1(n-2);
}

// 然后就喜提MLE/TLE了
// TLE是因为函数调用开销，MLE也是因为函数调用开销
// 初用递归时经常会遇到不知道怎么定义局部变量的问题，然后只能无脑塞进参数列表里
// 也就是说这些变量并非不需定义，只是存在了毋需操心的栈帧里了
// 想到这，就可以着手优化空间开销了
// 添加中间层，做记忆化之类的

map<int, int> m;

int func2(int n)
{
    if (n == 1) return 1;
    if (n == 2) return 2;

    if (m.count(n)) {
        return m[n];
    }

    int ret = func2(n-1) + func2(n-2);
    m[n] = ret;

    return ret;
}

// 再继续优化的话，就是接管对于变量的控制了
int func3(int n)
{
    if (n == 1) return 1;
    if (n == 2) return 2;

    int ret = 0;
    for (int i = 3, pre1 = 1, pre2 = 2; i <= n; ++i) {
        ret = pre1 + pre2;
        pre1 = pre2;
        pre2 = ret;
    }

    return ret;
}

int main()
{
    cout << func1(37) << endl;
    cout << func2(37) << endl;
    cout << func3(37) << endl;
    return 0;
}
