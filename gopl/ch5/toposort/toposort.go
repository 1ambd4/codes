package main

import "fmt"
import "sort"

var preresq = map[string][]string {
    "algo": {"data structures"},
    "calc": {"linear algebra"},
    "compilers": {"data structures",
                  "formal languages",
                  "computer organization"},
    "data structures": {"discrete math"},
    "databases": {"data structures"},
    "discrete math": {"intro to programming"},
    "formal languages": {"discrete math"},
    "networks": {"operating system"},
    "operating system": {"data structures", "computer organization"},
    "programming languages": {"data structures", "computer organization"},
}

func topoSort(m map[string][]string) []string {
    var order []string
    seen := make(map[string]bool)
    // 匿名函数来玩儿递归
    // 太他妈神奇辣
    // 但是需要注意的是
    // 需要先声明一个变量然后再把匿名函数赋值给这个变量
    // 如果用海象表达式合并成一条语句的话，无法通过编译
    // 因为那样的话
    // 函数字面量visitAll并没有在visitALl变量的作用域中
    // 因而也就无法实现递归的调用自己了
    var visitAll func(items []string)
    visitAll = func(items []string) {
        for _, item := range items {
            if !seen[item] {
                seen[item] = true
                visitAll(m[item])
                order = append(order, item)
            }
        }
    }

    var keys []string
    for key := range m {
        keys = append(keys, key)
    }

    sort.Strings(keys)
    visitAll(keys)
    return order
}

func main() {
    for i, course := range topoSort(preresq) {
        fmt.Printf("%d:\t%s\n", i+1, course)
    }
}
