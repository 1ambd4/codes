package main

import "fmt"

// GOMAXPROCS=1 go run maxprocs.go
// GOMAXPROCS=2 go run maxprocs.go
func main() {
    for {
        go fmt.Print(0)
        fmt.Print(1)
    }
}
