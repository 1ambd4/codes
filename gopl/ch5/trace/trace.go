package main

import "time"
import "log"

func BigOperation() {
    // defer延迟函数好好玩儿
    // 函数和参数表达式会在语句执行时求值
    // 但实际的调用推迟到包含defer语句的函数执行结束后
    // defer语句没有限制使用次数
    // 执行的时候以调用defer语言顺序的逆序执行
    // 但defer a.b().c()...n()的形式中，只有最后的n()会被延迟调用
    // 这就使得可以在某时刻同时拿到了当前时间点和函数返回前两个时间点的context
    defer timeTrace("BigOperation")()
    // operation
    time.Sleep(time.Second * 3)
}

func timeTrace(msg string) func() {
    start := time.Now()
    log.Printf("enter %s", msg)

    return func() { log.Printf("exit %s (%s)", msg, time.Since(start)) }
}

func main() {
    BigOperation()
}
