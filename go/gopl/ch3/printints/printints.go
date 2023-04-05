package main

import "fmt"
import "bytes"

// buffer
func Int2String(values []int) string {
    var buf bytes.Buffer
    buf.WriteByte('[')

    for i, v := range values {
        if i > 0 {
            buf.WriteString(", ")
        }
        fmt.Fprintf(&buf, "%d", v)
    }

    buf.WriteByte(']')
    return buf.String()
}

func main() {
    s := []int { 1, 2, 3, 4 }
    fmt.Println(Int2String(s))
}
