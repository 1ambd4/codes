package anyone_test

import "testing"
import "fmt"
import "runtime"
import "time"

func runTask(id int) string {
    time.Sleep(time.Millisecond * 10)
    return fmt.Sprintf("The result is from %d", id)
}

func AnyoneResponse() string {
    numberOfRunner := 10

    // 用channel的阻塞和唤醒机制来实现同步机制

    // 使用普通通道的话，有些协程无法被取消
    // ch := make(chan string)

    // 应当使用buffer channel
    ch := make(chan string, numberOfRunner)

    for i := 0; i < numberOfRunner; i++ {
        go func(i int) {
            ret := runTask(i)
            ch <- ret
        }(i)
    }

    // 当有协程向管道里写数据的时候被唤醒，否则一直阻塞住
    return <-ch
}

func TestAnyoneResponse(t *testing.T) {
    t.Log("before:", runtime.NumGoroutine())
    t.Log(AnyoneResponse())
    time.Sleep(time.Second * 1)
    t.Log("after:", runtime.NumGoroutine())
}
