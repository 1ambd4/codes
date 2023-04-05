package main

import "sync"

// 互斥锁的使用场景很广泛
// 因而sync包里定义了单独的Mutex类型来满足此类需求

// var (
//     mu sync.Mutex   // 互斥锁
//     balance int     // 一般把锁和其保护的变量定义在一起
// )

// 多读单写锁
// 但因为要维护读互斥量进程的信息，相对而言性能略微下降
// 一直只在频繁获取读锁，且锁竞争比较激烈的时候才使用
var (
    mu sync.RWMutex
    balance int
)

func Desposit(amount int) {
    mu.Lock()
    balance += amount
    mu.Unlock()
}

func Balance() int {
    // mu.Lock()
    mu.RLock()
    b := balance
    // mu.Unlock()
    mu.RUnlock()
    return b
}

func main() {
}
