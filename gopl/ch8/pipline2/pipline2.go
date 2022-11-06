package main

import "fmt"

func main() {
    // 这里用的通道都是双向的
    // 单向通道见pipeline3
    naturals := make(chan int)
    squares := make(chan int)

    done := make(chan struct {})

    // counter
    go func() {
        for x := 0; x < 100; x++ {
            naturals <- x
        }
        close(naturals)
    }()

    // squarer
    go func() {
        // range迭代pipeline就舒服多了
        for x := range naturals {
            squares <- x * x
        }
        close(squares)
    }()

    // printer
    go func() {
        for x := range squares {
            fmt.Println(x)
        }
        done <- struct{}{}
    }()

    <- done
}
