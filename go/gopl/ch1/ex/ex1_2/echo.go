package main

import "os"
import "fmt"

func main() {
    for i, arg := range os.Args[1:] {
        fmt.Printf("%d: %s\n", i, arg)
    }
}
