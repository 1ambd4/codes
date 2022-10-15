package map_test

import "testing"

func TestMap(t *testing.T) {
    // map是没有capacity的
    m0 := map[string]int { "one": 1, "two": 2, "three": 3 }
    t.Log("len(m0) = ", len(m0), m0)

    // 创建一个空的map
    m1 := map[string] int {}
    m1["one"] = 1

    m2 := make(map[string]int, 10)
    m2["one"] = 1
    // Go和其他语言中map不同的是，访问不存在的元素返回0，而不是空或者直接出错
    t.Log(m2["two"])
    t.Log(m2)
    // 因而不确定是不是存在，可以用if判断
    if v, ok := m2["two"]; ok {
        t.Log(v)
    } else {
        t.Log("not exist")
    }

    for k, v := range m0 {
        t.Log(k, v)
    }
}
