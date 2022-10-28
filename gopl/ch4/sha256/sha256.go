package main

import "fmt"
import "crypto/sha256"

func main() {
    c1 := sha256.Sum256([]byte("x"))
    c2 := sha256.Sum256([]byte("X"))
    // sum256可用于快速的比较字符串是否相等
    fmt.Printf("sum256(\"x\") = %x\nsum256(\"X\") = %x\n%t %T", c1, c2, c1 == c2, c1)
}
