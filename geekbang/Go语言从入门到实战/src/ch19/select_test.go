package select_test

import "testing"
import "time"
import "fmt"

func service() string {
    time.Sleep(time.Millisecond * 500)
    return "done"
}

func AsyncService() chan string {
    retCh := make(chan string, 1)
    
    go func() {
        ret := service()
        fmt.Println("returned result.")
        retCh <- ret
        fmt.Println("service exited.")
    }()

    return retCh
}

func TestSelect(t *testing.T) {
    // 通道的选择
    select {
    case ret := <- AsyncService():
        t.Log(ret)
    case <-time.After(time.Millisecond * 100):
        t.Error("time out")
    }
}
