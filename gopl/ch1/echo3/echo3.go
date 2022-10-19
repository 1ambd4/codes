package main

import "os"
import "fmt"
import "strings"

func main() {
    fmt.Println(strings.Join(os.Args[1:], " "))
    // fmt.Println(os.Args[1:])
}
