package cancel_test

import "testing"
import "fmt"
import "time"

func isCancelled(cancelChan chan struct{}) bool {
    select {
    case <- cancelChan:
        return true
    default:
        return false
    }
}

func cancel_1(cancelChan chan struct{}) {
    cancelChan <- struct{}{}
}

func cancel_2(cancelChan chan struct{}) {
    close(cancelChan)
}

func TestCancel(t *testing.T) {
    cancelChan := make(chan struct{}, 0)

    for i := 0; i < 5; i++ {
        go func(i int, cancelChan chan struct{}) {
            for {
                if isCancelled(cancelChan) {
                    break
                }
                time.Sleep(time.Millisecond * 50)
            }
            fmt.Println(i, "cancelled")
        }(i, cancelChan)
    }

    // cancel_1只向通道发了一次消息，因而只有一个协程受到了消息
    // cancel_1(cancelChan)

    // 而通道的关闭是一个广播消息，所有的协程都能收到
    cancel_2(cancelChan)

    time.Sleep(time.Second * 1)
}
