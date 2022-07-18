#include <iostream>

using namespace std;

// 队列是具有先进先出特性的操作受限的线性表
// 在偏底层系统、架构、中间件中应用颇多，如循环队列、阻塞队列、并发队列等

// 栈用数组实现方便，而队列用链表方便些

template <typename T>
class Node
{
public:
    Node(T d) : data(d), next(nullptr) { };
    T data;
    Node *next;
};

template <typename T>
class Queue
{
public:
    Queue()
    {
        queue = new Node<T>(static_cast<T>(0));
    }
    ~Queue()
    {
        Node<T> *cur = queue;
        while (cur != nullptr) {
            queue = queue->next;
            delete cur;
            cur = queue;
        }
    }
    bool enqueue(T x);
    bool dequeue();
    void show();
private:
    Node<T> *queue;
};

template <typename T>
bool Queue<T>::enqueue(T x)
{
    // 加个尾指针会好处理得多
    Node<T> *tmp = new Node<T>(x), *cur = queue;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = tmp;
}

template <typename T>
bool Queue<T>::dequeue()
{
    if (queue->next == nullptr) {
        return false;
    }
    Node<T> *cur = queue->next;
    queue->next = queue->next->next;
    delete cur;
    return true;
}

template <typename T>
void Queue<T>::show()
{
    Node<T> *cur = queue->next;
    while (cur != nullptr) {
        cout << cur->data << ",";
        cur = cur->next;
    }
}

// 对于资源优先的多数场景，都可以用队列来实现请求排队这一过程
//  衍生出的阻塞队列就是入队、出队操作可一阻塞，并发队列就是考虑队列操作的多线程安全

int main()
{
    // Queue<int> p();
    // Uniform Initialization不是没有道理的
    Queue<int> q { };
    q.enqueue(3);
    q.enqueue(2);
    q.enqueue(7);
    q.enqueue(9);
    q.enqueue(1);
    q.dequeue();
    q.show();
    return 0;
}
