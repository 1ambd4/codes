package main

import "fmt"

// 改成数组指针的方式就失去通用性了啊
func reverse(ptr *[6]int) {
    for i, j := 0, len(ptr)-1; i < j; i, j = i+1, j-1 {
        ptr[i], ptr[j] = ptr[j], ptr[i]
    }
    // 那是不是可以直接
    // a[0], a[1], a[2], ... = a[5], a[4], a[3] ...
}

func main() {
    a := [6]int{ 1, 2, 3, 4, 5, 6 }
    reverse(&a)
    fmt.Println(a)
}
