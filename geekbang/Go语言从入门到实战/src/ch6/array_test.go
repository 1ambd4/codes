package array_test

import "testing"

func TestArray(t *testing.T) {
    // 声明数组
    var a [3]int
    // 赋值
    a[0] = 1
    t.Log("a = ", a)

    // 声明的同时初始化
    b := [3]int { 1, 2, 3 }
    c := [2][2]int { {1, 2}, { 3, 4} }

    t.Log("b = ", b)
    t.Log("c = ", c)

    // 长度可以自动推导
    d := [...]int { 1, 2, 3, 4, 5, 6 }
    t.Log("d = ", d)

    // 
    for i := 0; i < len(d); i++ {
        t.Log("d[", i, "] = ", d[i])
    }

    for i, e := range d {
        t.Log(i, e)
    }

    // Go语言里如果有未使用的变量会通不过编译
    // 可以用_作为占位符
    for _, e := range d {
        t.Log(e)
    }
}

func TestArraySlice(t *testing.T) {
    // 切片，同样是左闭右开
    // 但切片不如python灵活，不支持负索引
    a := [...]int { 0, 1, 2, 3, 4, 5, 6, 7 }
    t.Log(a[0:2])
    t.Log(a[2:])
    t.Log(a[:len(a)])
}

func TestSliceInit(t *testing.T) {
    // 定义一个切片
    // 切片这种数据结构，包括了一个指向数据的指针，length和capacity
    var s0 []int
    t.Log(len(s0), cap(s0))
    s0 = append(s0, 1)
    t.Log(len(s0), cap(s0))


    // 注意len和cap的区别
    s1 := []int { 1, 2, 3, 4, 5 }
    t.Log(len(s1), cap(s1))

    // Go里经常用make来创建各种数据结构
    s2 := make([]int, 3, 5)
    t.Log(len(s2), cap(s2))
}

func TestSliceGrowing(t *testing.T) {
    // cap倍增
    s := []int {}
    
    for i := 0; i < 10; i++ {
        s = append(s, i)
        t.Log(len(s), cap(s))
    }
}

func TestSliceShareMemory(t *testing.T) {
    // 切片可以共享数据
    s0 := []string { "Mon", "Tue", "Wed", "Thu", "Fir", "Sat", "Sun" }
    t.Log(len(s0), cap(s0), s0)

    s1 := s0[0:5]
    t.Log(len(s1), cap(s1), s1)

    s0[0] = "MON"

    t.Log(len(s0), cap(s0), s0)
    t.Log(len(s1), cap(s1), s1)
}

func TestSliceCompare(t *testing.T) {
    a := []int { 1, 2, 3, 4 }
    b := []int { 1, 2, 3 ,4 }

    // if a == b {
    //     t.Log("ok")
    // }
    // 并不ok，切片只能和nil比较

    if a != nil && b != nil {
        t.Log("a and b are not nil")
    }
}
