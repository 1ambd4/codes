package main

import "fmt"

// 给数字字符串添加上分隔符
// 递归太简洁了
func comma(s string) string {
    n := len(s)
    if (n <= 3) {
        return s
    }
    return comma(s[:n-3]) + "," + s[n-3:]
}

func main() {
    s := "12345678"
    fmt.Println(comma(s))
}
