#include <iostream>

using namespace std;

// 空间复杂度：除了原本的数据存储空间外，算法运行所需要的额外存储空间

// 栈是先进后出特性的操作受限的线性表
template <typename T>
class Stack
{
public:
    Stack(int cap) : capacity(cap), size(0)
    {
        items = new T[capacity];
    }
    ~Stack()
    {
        delete[] items;
    }
    bool push(T x);
    T pop();
private:
    T *items;
    unsigned int size;
    unsigned int capacity;
};

template <typename T>
bool Stack<T>::push(T x)
{
    if (size == capacity) {
        return false;
    }

    items[size++] = x;
    return true;
}

template <typename T>
T Stack<T>::pop()
{
    if (size == 0) {
        cout << "error: stack is empty!" << endl;
    }

    T tmp = items[--size];
    return tmp;
}


// 两个栈倒腾来倒腾去挺有意思的

int main()
{
    Stack<int> stack(5);
    stack.push(3);
    stack.push(7);
    cout << stack.pop() << ", " << stack.pop() << endl;
    return 0;
}
