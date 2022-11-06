package main

var (
    // 容量为1的缓冲通道来实现互斥锁
    // 为啥不用非缓冲通道呢？
    sema = make(chan struct{}, 1)
    balance int
)

func Deposit(amount int) {
    sema <- struct{}{}  // lock
    balance += amount
    <- sema             // unlock
}

func Balance() int {
    sema <- struct{}{}  // lock
    b := balance
    <- sema             // unlock
    return b
}
