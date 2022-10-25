package main

import "fmt"

func main() {
    // 变量声明
    // 因Go是静态类型语言，type和expression可省略其一，但不能全部省略
    // var name type = expression

    // var i, j, k int     // 其他语言里经常差不多的声明方式

    // 这个就比较有意思，差点以为在写python
    var a, b, f, s = 23, true, 2.3, "four"
    fmt.Printf("a = %d, b = %t, f = %f, s = %s\n", a, b, f, s);

    // 海象表达式（其实是短变量声明啦
    // 开始说了变量声明可以省略type或者expression其一
    // 大多数的情况下，是会给出expression而省略type的
    // 这也就是海象表达式出现的原因
    // 上面的var可以改成如下海象表达式
    // a, b, f, s := 23, true, 2.3, "four"
    fmt.Printf("fib(5) = %d\n", fib(5))

    // Go的类型声明，不同于C++里的typedef（typedef只是类型别名）
    // 即使底层用了相同的类型，也不是相同的类型
}

func fib(n int) int {
    x, y := 0, 1
    for i := 0; i < n; i++ {
        x, y = y, x + y     // 多重赋值
    }
    return x
}
