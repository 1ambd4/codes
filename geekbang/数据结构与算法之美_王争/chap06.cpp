#include <iostream>

using namespace std;

// 链表天然的支持动态扩容
// 而数组能更好的利用CPU的cache
// 当然喽，内存敏感的数组更合适，省去链表中指针的开销
// 具体项目具体权衡吧
//
// 基础的LRU算法实现
// 1) 如果数据已缓存在链表中，删除原来位置上的数据后，插到链表头部
// 2) 如果数据未缓存在链表中
//    a.缓存未满，直接将新数据插入到链表头部
//    b.缓存已满，删除链表最后一个结点后，将新数据插入到链表头部
//
// 如此一来，缓存访问的时间复杂度为O(n)
// 可以引入散列表，将之优化到O(1)


template <typename T>
class Node {
public:
    // 委托构造如何处理此种情况呢？
    Node() = default;
    Node(T d) : data(d), next(nullptr) { }
    Node(T d, Node *n) : data(d), next(n) { }
public:
    T data;
    Node *next;
};

template <typename T>
class List {
public:
    List();
    List(int cap);
    ~List();
    void push_front(T x);
    void pop_back();
    Node<T>* find(T x);
    bool remove(T x);
    bool empty();
    bool full();
    void show();

private:
    int size;
    int capacity;
    Node<T> *head;
};


template <typename T>
List<T>::List() : List(10) { }

template <typename T>
List<T>::List(int cap) : capacity(cap), size(0)
{
    head = new Node<T>();
    head->next = nullptr;
}

template <typename T>
List<T>::~List()
{
    Node<T> *cur = head;
    while (cur != nullptr) {
        head = head->next;
        delete cur;
        cur = head;
    }
    size = capacity = 0;
}

template <typename T>
void List<T>::push_front(T x)
{
    if (full()) {
        pop_back();
    }
    Node<T> *tmp = new Node<T>(x, head->next);
    head->next = tmp;
    ++size;
}

template <typename T>
void List<T>::pop_back()
{
    Node<T> *pre = head, *cur = head->next;
    while (cur->next != nullptr) {
        pre = pre->next;
        cur = cur->next;
    }
    delete cur;
    pre->next = nullptr;
    --size;
}

template <typename T>
Node<T>* List<T>::find(T x)
{
    Node<T> *cur = head->next;
    while (cur != nullptr && cur->data != x) {
        cur = cur->next;
    }
    return cur;
}

template <typename T>
bool List<T>::remove(T x)
{
    Node<T> *pre = head, *cur;
    while (pre->next != nullptr) {
        if (pre->next->data == x) {
            cur = pre->next;
            pre->next = cur->next;
            delete cur;
            cur = nullptr;
            --size;
            return true;
        }
        pre = pre->next;
    }
    return false;
}

template <typename T>
bool List<T>::empty()
{
    return size == 0;
}

template <typename T>
bool List<T>::full()
{
    return size == capacity;
}

template <typename T>
void List<T>::show()
{
    Node<T> *cur = head->next;
    while (cur != nullptr) {
        cout << cur->data << ", ";
        cur = cur->next;
    }
    cout << "\n";
}

template <typename T>
class LRU_Cache
{
public:
    LRU_Cache() : LRU_Cache(10) { }
    LRU_Cache(int capacity)
    {
        cache = new List<T>(capacity);
    }
    ~LRU_Cache()
    {
        delete cache;
    }

    // 两个看起来很傻的接口
    void put(T x);
    void get(T x);
    void show();
private:
    List<T> *cache;
};

template <typename T>
void LRU_Cache<T>::put(T x)
{
    cache->push_front(x);
}

template <typename T>
void LRU_Cache<T>::get(T x)
{
    if (auto ptr = cache->find(x); ptr != nullptr) {
        cache->push_front(x);
    } else {
    }
}

template <typename T>
void LRU_Cache<T>::show()
{
    cache->show();
}

int main()
{
    LRU_Cache<int> cache;
    cache.put(2);
    cache.get(3);
    cache.put(3);
    cache.show();
    return 0;
}
