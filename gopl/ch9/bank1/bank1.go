package main

var deposits = make(chan int)
var balances = make(chan int)

func Desposit(amount int) {
    deposits <- amount
}

func Balance() int {
    return <- balances
}

// 不要通过共享内存来通信
// 而应使用通信来共享内存
func teller() {
    var balance int
    for {
        select {
        case amount := <- deposits:
            balance += amount
        case balances <- balance:
        }
    }
}

// 解决数据竞争的方法
// 1、不修改变量
// 2、避免从多个goroutine访问同一个变量
// 3、允许多个goroutine访问同一个变量
//    但同一时间只能有一个goroutine访问变量，即互斥访问

func main() {
    go teller()
}
