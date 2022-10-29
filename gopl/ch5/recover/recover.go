package main

import "fmt"

// 宕机应当被妥善处理
// 但考虑到工作过于复杂，会存在一些只在特殊情况下才会出现的bug
// 那完全可以不宕机，而是将一些有用的附加信息提供出去

// recover如果被defer里的函数调用，并且包含这个defer的函数发生宕机
// 那么，ercovr会中止当前的宕机状态并且返回宕机的值
// 函数不会才之前的宕机处继续执行而是正常返回
// recover在其他任何情况下运行都没有任何效果且返回nil
func f(x int) (err error){
    fmt.Printf("f(%d) is %d\n", x, x + 0/x)
    defer func() {
        if p := recover(); p != nil {
            // 好像说是错误信息不要加换行
            err = fmt.Errorf("fatal error: %v", p)
        }
    }()
    return err
}

func main() {
    fmt.Println("recover")
}
