package func_test

import "math/rand"
import "testing"
import "time"
import "fmt"

func returnMultiValues() (int, int) {
    // 函数可以返回多个返回值
    return rand.Intn(10), rand.Intn(20)
}

func timeSpent(inner func(op int) int) func(op int) int {
    // 函数作为一等公民的情况下，就可以做很多有趣的事情
    // 也就是所谓的函数式编程
    // 这里实现的是类似装饰器模式
    return func(n int) int {
        start := time.Now()
        ret := inner(n)
        fmt.Println("time spent: ", time.Since(start).Seconds())
        return ret
    }
}

func slowFunc(op int) int {
    time.Sleep(time.Second * 1)
    return op
}

func TestFunc(t *testing.T) {
    a, _ := returnMultiValues()
    t.Log(a)

    tsSF := timeSpent(slowFunc)
    t.Log(tsSF(10))
}

func Sum(ops ...int) int {
    // 不定长参数
    ret := 0
    for _, op := range ops {
        ret += op
    }
    return ret
}


func TestVarParam(t *testing.T) {
    t.Log(Sum(1, 2, 3, 4))
    t.Log(Sum(1, 3, 4, 5, 6))
}

func Clear() {
    fmt.Println("clear resources.")
}

func TestDefer(t *testing.T) {
    // defer延迟执行，类似finally？
    // 延迟到函数返回前
    defer Clear()
    fmt.Println("Start")
    panic("err")
}
