package main

import "fmt"

func double(x int) int {
    return x + x
}

// defer在return语句之后执行，因而可以访问到函数的返回值
func double1(x int) (result int) {
    defer func() { fmt.Printf("double(%d) = %d\n", x, result) }()
    return x + x
}

func triple(x int) (result int) {
    defer func() { result += x }()  // 修改返回值
    return double(x)
}

func main() {
    // _ = double(4)
    fmt.Println("double:", double(4))
    fmt.Println("triple:", triple(4))
}
