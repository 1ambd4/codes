package empty_interface_test

import "fmt"
import "testing"

// 类似void*
func doSomething(p interface{}) {
    if i, ok := p.(int); ok {
        fmt.Println("Integer", i)
        return
    }

    if s, ok := p.(string); ok {
        fmt.Println("String", s)
        return
    }

    fmt.Println("Unknow Type")

    // switch写法
    switch v := p.(type) {
    case int:
        fmt.Println("Integer", v)
    case string:
        fmt.Println("String", v)
    default:
        fmt.Println("Unknow Type")
    }
}

func TestDoSomething(t *testing.T) {
    doSomething(10)
    doSomething("10")
}
