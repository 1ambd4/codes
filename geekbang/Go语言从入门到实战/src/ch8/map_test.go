package map_test

import "testing"

func TestMapWithFunValue(t *testing.T) {
    // map的value不止可以是数据，也可以是方法

    m := map[int]func(op int) int { }
    m[1] = func(op int) int { return op }
    m[2] = func(op int) int { return op * op }
    m[3] = func(op int) int { return op * op * op }

    t.Log(m[1](2), m[2](2), m[3](2))
}

func TestMapForSet(t *testing.T) {
    // 用map实现set
    s := map[int]bool {}
    s[1] = true
    s[3] = true
    s[4] = true

    // 判读set中某个元素是否存在
    if s[1] {
        t.Log("1 is exist")
    } else {
        t.Log("1 is not exist")
    }

    t.Log(len(s))

    // 删除set里的元素
    delete(s, 3)
    t.Log(len(s))
}
