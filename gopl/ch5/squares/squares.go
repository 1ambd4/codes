package main

import "fmt"

// 匿名函数
// 上一次我看到这么奇怪的写法还是lisp
func square() func() int {
    var x int
    return func() int {
        x++
        return x * x
    }
}

func main() {
    f := square()
    fmt.Println(f())
    fmt.Println(f())
    fmt.Println(f())
    fmt.Println(f())
}
