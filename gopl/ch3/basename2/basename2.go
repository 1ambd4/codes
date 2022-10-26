package main

import "fmt"
import "strings"

func basename(s string) string {
    slash := strings.LastIndex(s, "/")
    s = s[slash+1:]
    if dot := strings.LastIndex(s, "."); dot > 0 {
        s = s[:dot]
    }
    return s
}

func main() {
    s := "a/b/c/d.go"
    fmt.Println(basename(s))
}
