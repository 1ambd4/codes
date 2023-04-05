package main

import "fmt"

// counter -> squarer -> printer

// 无限循环并打印出来
func func1() {
    naturals := make(chan int)
    squares := make(chan int)

    // Counter
    go func() {
        for x := 0; ; x++ {
            naturals <- x
        }
    }()

    // Squarer
    go func() {
        for {
            x := <-naturals
            squares <- x * x
        }
    }()

    // Printer
    for {
        fmt.Println(<-squares)
    }
}

// 那么如果想打印有限的数字怎么做呢？

func func2(done chan struct{}) {
    naturals := make(chan int)
    squares := make(chan int)

    doee := make(chan struct{})

    go func() {
        for x := 0; x < 10; x++ {
            naturals <- x
        }
        close(naturals)
    }()

    go func() {
        for {
            // 每次都要来这么一次实在过于繁琐
            // 且这个需求很常见，因而Go语言提供了range以在通道上迭代
            // 写法见pipeline2
            x, ok := <-naturals
            if !ok {
                break
            }
            squares <- x * x
        }
        close(squares)
    }()

    go func() {
        for {
            x, ok := <-squares
            if !ok {
                break
            }
            fmt.Println(x)
        }

        doee <- struct{}{}
    }()

    <- doee
    done <- struct{}{}
}

func main() {
    // func1()
    done := make(chan struct{})
    go func2(done)

    <-done
}
