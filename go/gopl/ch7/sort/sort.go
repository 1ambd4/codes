package main

import "sort"
import "fmt"
import "syscall"

// sort.Interface需要实现如下三个方法
// type Interface interface {
//     Len() int
//     Less(i, j int) bool
//     Swap(i, j int)
// }

// 以字符串切片为例
type StringSlice []string
func (p StringSlice) Len() int {
    return len(p)
}
func (p StringSlice) Less(i, j int) bool {
    return p[i] < p[j]
}
func (p StringSlice) Swap(i, j int) {
    p[i], p[j] = p[j], p[i]
}

func main() {
    fruits := []string{ "banana", "apple", "organge", "watermelon"}
    fmt.Println(fruits)
    sort.Sort(StringSlice(fruits))
    fmt.Println(fruits)
    // 当然，string排序的需求很常见，因而内置了sort.String()

    // error接口
    // 同样的也有errno啊
    var err error= syscall.Errno(1)
    // fmt.Println(err.Error())
    fmt.Println(err)
}
