package main

import "fmt"

func basename(s string) string {
    // 丢弃最后一个'/'及之前的字符
    for i := len(s) - 1; i >= 0; i-- {
        if s[i] == '/' {
            s = s[i+1:]
            break
        }
    }

    // 保留最后一个'.'及之前的字符
    for i := len(s) - 1; i >= 0; i-- {
        if s[i] == '.' {
            s = s[:i]
            break
        }
    }

    return s
}

func main() {
    s := "a/b/c/d.go"
    fmt.Println(basename(s))
}
