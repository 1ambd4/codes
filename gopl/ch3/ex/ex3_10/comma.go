package main

import "fmt"
import "bytes"

func reverse(s string) string {
    a := []rune(s)
    n := len(s)
    for i := 0; i < n/2; i++ {
        a[i], a[n-1-i] = a[n-1-i], a[i]
    }
    return string(a)
}

func comma(s string) string {
    var buf bytes.Buffer

    for i := len(s)-1; i >= 0; i-- {
        fmt.Fprintf(&buf, "%c", s[i])
        if ((i+1) % 3 == 0) {
            buf.WriteByte(',')
        }
    }

    return reverse(buf.String())
}

func main() {
    s := "12345678"
    fmt.Println(comma(s))
}
