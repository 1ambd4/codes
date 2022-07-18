#include <iostream>

using namespace std;

// 链表相关
// 1、警惕指针丢失
// 2、警惕内存泄漏
// 3、巧设头节点

int find1(char *s, int n, char key)
{
    if (s == nullptr || n <= 0) {
        return -1;
    }

    int i;
    while (i < n) {
        if (s[i] == key) {
            return i;
        }
        ++i;
    }

    return -1;
}

int find2(char *s, int n, char key)
{
    if (s == nullptr || n <= 0) {
        return -1;
    }

    // 把哨兵设置在数组末尾
    // 因而需要特判并保存原数组末尾变量，以便恢复
    if (s[n-1] == key) {
        return n-1;
    }
    char tmp = s[n-1];
    s[n-1] = key;

    int i = 0;
    while (s[i] != key) {
        ++i;
    }

    s[n-1] = tmp;

    if (i == n-1) {
        return -1;
    } else {
        return i;
    }
}

// 因着末尾哨兵的存在，find2较之find1在循环里少了一次下标的比较，效率会高不少
//
// 链表常见题：
//  a.反转
//  b.合并
//  c.判环
//  d.求中间结点
//  e.删除倒数第k个结点

int main()
{
    char *s = "abcdefghijklmn";
    cout << find1(s, sizeof(s)/sizeof(char), 'a') << endl;

    return 0;
}
