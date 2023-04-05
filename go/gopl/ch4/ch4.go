package main

import "fmt"

func main() {
    // 数组的长度固定
    var a [3]int
    for i, v := range a {
        fmt.Printf("%d: %d\n", i, v)
    }
    a[0], a[1], a[2] = 1, 2, 3
    for _, v := range a {
        fmt.Printf("%d ", v)
    }
    fmt.Println()

    b := [...]int { 1, 2, 3, 4, 5 }
    fmt.Printf("type of b is: %T\n", b)

    // 可以指定索引赋值
    // 创建一个大小为100的数组，并初始化最后一个元素为-1,其余为零值
    c := [...]int { 99: -1 }
    fmt.Println(len(c))

    // 数组作为参数时，Go语言把数组看作值传递
    // 虽然可以用传指针的方式省去副本的开销
    // 但因为数组长度也作为类型一部分的缘故，写起来并不舒服
    // 因而非必要不用数组
    // slice要好用得多


    // sclice是一种轻量级的数据结构
    // 可以访问数组部分或全部的元素，这个数组即slice的底层数组
    // slice有三个属性，指针、长度和容量
    // slice操作符 s[i:j] 创建了一个slice
    // 引用s中从i到j-1索引位置的所有元素，共j-i个
    // len(s[i:j]) = j-i
    // cap(s[i:j]) = len(s) - i
    // 当访问slice中的元素，若超过j但未超过len(s)则slice会增长
    // 但若超过cap(s)则程序出错

    d := c[10:20]
    fmt.Println(len(d), cap(d))  // len = 20-10 =10, cap = 100-10 = 90

    e := d[:30]                  // 虽然超过了len(d)，的没有超过cap(d)
    fmt.Println(len(e), cap(e))  // len = 30, cap = 90
    // f := d[:200]              // error
    // fmt.Println(len(f), cap(f)) 
    // slice的初始化和数组很像，但不需要指定长度
    f := []int{ 1, 2, 3, 4, 5 }
    fmt.Printf("type of f is: %T, type of b is: %T\n", f, b)
    fmt.Println(len(f), cap(f))

    // 使用append向slice里添加元素
    // 因为slice的增长可能涉及到扩容
    // 无从得知append后得到的slice是否还指向原来的底层数组
    // 也无从得知旧slice上对元素的操作是否会影响到新slice的元素
    // 因而通常将append的调用结果再次赋值给传入append函数的slice
    // 如：g = append(g, 1)   // slice中追加数字1
    // 只要有可能改变slice的长度、容量以及所指向的底层数组，都需要更新slice
    //
    // 有点iterator的样子了，改动容器后需要进行更新操作
    var g []rune
    for _, r := range "Hello 世界" {
        g = append(g, r)
    }
    fmt.Printf("%q\n", g)

    k := []int { 1, 2, 3, 4, 5 }
    k = remove(k, 2)
    fmt.Println(k)
    k = remove2(k, 1)
    fmt.Println(k)

    // Go里数据结构给人的感觉是容错性很高
    // var l map[string]int // = map[string]int {}
    // map使用之前需要先进行初始化以分配内存之类，否则会出错
    l := map[string]int {}
    l["a"] = 1
    // map的键必须要是可比较而类型，像slice就不能直接做为键
    // 这时候可以将slice序列化后作为键来使用

    // 结构体一般比较大，多使用指针传递，因而常写作
    m := &Point{1, 2}
    // m := new(Point)    上面的初始化形式等价于此处两句
    // *m = Point{1, 2}
    fmt.Println(m)
    // 如果结构体的所有数据成员都是可比较的，那么结构体可比较
    // 可比较的结构体可以作为map的键

    n := Wheel{Circle{Point{1, 2}, 3}, 4}
    fmt.Printf("%#v\n", n)
    fmt.Printf("%d %d %d %d\n", n.X, n.Y, n.Raidus, n.Spokes)
    // 好耶，啥时候初始化也方便就好了
    // 目前猜测只是语法糖罢了
    fmt.Printf("%d %d %d %d\n", n.Circle.Point.X, n.Circle.Point.Y,
                n.Circle.Raidus, n.Spokes)


    // JSON
    // JSON的对象是一个字符串到值的映射
}

type Point struct {
    X, Y int
}

// 匿名成员使得访问嵌套结构体里的成员变得优雅许多
// 这也使得组合用起来像继承一样方便
type Circle struct {
    Point
    Raidus int
}

type Wheel struct {
    Circle
    Spokes int
}


// 删除slice中索引为i的元素
func remove(slice []int, i int) []int {
    copy(slice[i:], slice[i+1:])
    return slice[:len(slice)-1]
}

// 无需保持顺序性的话，很好
func remove2(slice []int, i int) []int {
    slice[i] = slice[len(slice)-1]
    return slice[:len(slice)-1]
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


// 只能接受长度为32的byte数组，通用性差
func zero(ptr *[32]byte) {
    for i := range ptr {
        ptr[i] = 0
    }
}

// 标准库只提供了高度优化的bytes.Equal
// 用来比较两个字节slice([]byte)是否相等
func equal(x, y []string) bool {
    if len(x) != len(y) {
        return false
    }

    for i := range x {
        if x[i] != y[i] {
            return false
        }
    }

    return true
}
