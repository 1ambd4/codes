package main

import "fmt"
import "math"
import "strconv"

func HasPrefix(s, prefix string) bool {
    return len(s) >= len(prefix) && s[:len(prefix)] == prefix
}

func HasSuffix(s, suffix string) bool {
    return len(s) >= len(suffix) && s[len(s) - len(suffix):] == suffix
}

func Contains(s, substr string) bool {
    for i := 0; i < len(s); i++ {
        if HasPrefix(s[i:], substr) {
            return true
        }
    }
    return false
}

// 定义编译器常量，好耶
// 当省略右侧表达式时，会复用前一个常量的类型和值
// 故而此处：a = 1, b = a = 1, c = 2, d = c = 2
const (
    a = 1
    b
    c = 2
    d
)


// 常量生成器iota
// iota从0开始，每次增加1
type Weekday int
const (
    Sunday Weekday = iota // 0
    Monday                // 1
    Tuesday               // 2
    Wednesday             // 3
    Thursday              // 4
    Firday                // 5
    Saturday              // 6
)


// 甚至也可以搞点儿好玩的位运算
type Flags uint
const (
    FlagUp Flags = 1 << iota
    FlagBrouacast
    FlagLoopback
    FlagPointToPoint
    FlagMulticast
)

// 借助延迟确定从属类型，无类型常量可以暂时维持高精度，如math.Pi
// 且在多数表达式中无需进行类型转换
// 无类型常量的精度有类型值要高的多，至少有256位
//   无类型布尔、无类型整数、无类型文字符号
//   无类型浮点数、无类型复数、无类型字符串
const (
    _ = 1 << (10 * iota)
    KiB
    MiB
    GiB
    TiB
    PiB
    EiB
    ZiB
    YiB
)

func main() {
    var x uint8 = 1 << 1 | 1 << 5
    var y uint8 = 1 << 1 | 1 << 2

    // bitset
    fmt.Printf("%08b\n", x)      // "00100010": {1,5}
    fmt.Printf("%08b\n", y)      // "00000110": {1,2}

    fmt.Printf("%08b\n", x & y)  // "00000010": {1}      交集
    fmt.Printf("%08b\n", x | y)  // "00100110": {1,2,5}  并集
    fmt.Printf("%08b\n", x ^ y)  // "00100100": {2,5}    对称差
    fmt.Printf("%08b\n", x &^ y) // "00100000": {5}      差合

    for i := uint(0); i < 8; i++ {
        if x & (1<<i) != 0 {     // 元算判定
            fmt.Println(i)       // 1 5
        }
    }

    o := 0666
    fmt.Printf("%d %[1]o %#[1]o\n", o) // 438  666  0666
    // %[1]o: [1]表示复用第一个操作数，此处即变量o
    // %#[1]o: #表示输出对应格式的前缀，此处及八进制的前缀0


    // float32有效数字大约为6位，float64有效数字大约有15位
    var f float32 = 1 << 24
    fmt.Println(f == f + 1)      // true，溢出了

    // NaN: not a number
    // 诸如0/0、sqrt(-1)
    nan := math.NaN()
    fmt.Println(nan == nan, nan < nan, nan > nan)

    // 布尔逻辑运算符中，逻辑与的优先级大于逻辑或

    // 字符串和数字互转
    m := 123
    n := fmt.Sprintf("%d", m)
    fmt.Println(n, strconv.Itoa(m))
    // Sprintf更灵活些
    n = fmt.Sprintf("%b", m)
    fmt.Println(n, strconv.FormatInt(int64(m), 2))

    fmt.Println(a, b, c, d)
}

