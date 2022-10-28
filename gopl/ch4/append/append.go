package main

import "fmt"

func appendInt(x []int, y int) []int {
    var z []int
    zlen := len(x) + 1
    // 原slice的底层数组仍有空间
    if zlen <= cap(x) {
        z = x[:zlen]
    } else {
        zcap := zlen
        if zcap < 2 * len(x) {
            zcap = 2 * len(x)
        }
        z = make([]int, zlen, zcap)
        copy(z, x)
    }
    z[len(x)] = y
    return z
}

// 不定参数扩展后，可支持一次插入多个元素
func appendIntEx(x[] int, y ...int) []int {
    var z []int
    zlen := len(x) + len(y)

    if zlen <= cap(x) {
        z = x[:zlen]
    } else {
        zcap := zlen
        if zcap < 2 * len(x) {
            zcap = 2 * len(x)
        }
        z = make([]int, zlen, zcap)
        copy(z, x)
    }
    copy(z[len(x):], y)
    return z
}

func main() {
    var a []int
    fmt.Println(a)
    a = appendInt(a, 2)
    fmt.Println(a)
    a = appendInt(a, 5)
    fmt.Println(a)
    a = appendIntEx(a, 1, 4, 3)
    fmt.Println(a)
}
