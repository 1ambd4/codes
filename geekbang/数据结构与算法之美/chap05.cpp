#include <iostream>

using namespace std;

void func1()
{
    int i { 0 };
    int arr[3] { };

    cout << &i << endl;
    cout << &arr[0] << " " << &arr[1] << " " << &arr[2] << " " << &arr[3] << endl;
    // 0x7ffeec4e984c
    // 0x7ffeec4e9840 0x7ffeec4e9844 0x7ffeec4e9848 0x7ffeec4e984c
    //
    // C/C++的局部变量依次存放在栈里，且栈地址由高向低生长
    // 其指针使用的极度自由性使得时常会出现一些意料之外的情况
    // 如此处，明明是越界了，却刚好访问到先入栈的前一个变量i
    // 于是陷入死循环

    for (i = 0; i <= 3; ++i) {
        arr[i] = 0;
        cout << "Hi, how do you do?" << endl;
    }
}

void func2()
{
    int arr[3] { };
    int i { 0 };

    cout << &i << endl;
    cout << &arr[0] << " " << &arr[1] << " " << &arr[2] << " " << &arr[3] << endl;
    // 0x7ffee2c1d840
    // 0x7ffee2c1d844 0x7ffee2c1d848 0x7ffee2c1d84c 0x7ffee2c1d850
    //
    // 此处调整变量的定义顺序，虽然非法写入了栈上未分配的内存
    // 但问题不大，输出符合预期
    // 虽然绝对不该这么写就是了，因为数组越界是未定义行为

    for (i = 0; i <= 3; ++i) {
        arr[i] = 0;
        cout << "Hi, how do you do?" << endl;
    }
}

int main()
{
    func1();
    // func2();
    return 0;
}
