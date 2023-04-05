package main

import "fmt"

func counter(out chan<- int) {
    for x := 0; x < 100; x++ {
        out <- x
    }
    close(out)
}

func squarer(out chan<- int, in <-chan int) {
    for x := range in {
        out <- x * x
    }
    close(out)
}

func printer(in <-chan int) {
    for x := range in {
        fmt.Println(x)
    }
}

func main() {
    naturals := make(chan int)
    squares := make(chan int)

    go counter(naturals)
    go squarer(squares, naturals)

    // 最后一个不需要用协程么？
    // 妙啊，这样就不用做协程同步了。
    printer(squares)
}
