package err_test

import "fmt"
import "testing"
import "errors"

var LessThanZeroError error = errors.New("n should not smaller than 0")

func foo(n int) (int, error) {
    if n < 0 {
        return -1, LessThanZeroError
    } else if n > 100 {
        return -1, errors.New("n should not lager than 10")
    }

    ret := 233

    return ret, nil
}

func TestError(t *testing.T) {
    if v, err := foo(-10); err == nil {
        t.Log(v)
    } else {
        if (err == LessThanZeroError) {
            t.Log("less than 0")
        } else {
            t.Log("Error")
        }
    }
}

func TestRecover(t *testing.T) {
    defer func() {
        // recover的功能类似捕获所有的error
        if err := recover(); err != nil {
            fmt.Println("recovered from ", err)
        }
    }()

    fmt.Println("start")

    panic(errors.New("something wrong!"))
}
