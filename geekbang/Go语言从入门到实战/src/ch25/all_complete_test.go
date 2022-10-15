package all_complete_test

import "testing"
import "fmt"
import "runtime"
import "time"

func runTask(id int) string {
    return fmt.Sprintf("the result is from %d", id)
}

func AllResponse() string {
    numOfRunner := 10
    ch := make(chan string, numOfRunner)

    for i := 0; i < numOfRunner; i++ {
        go func(i int) {
            ret := runTask(i)
            ch <- ret
        }(i)
    }

    // 等待所有的通道返回消息
    finalRet := ""
    for j := 0; j < numOfRunner; j++ {
        finalRet += <- ch + "\n"
    }

    return finalRet
}

func TestAllResponse(t *testing.T) {
    t.Log("before: ", runtime.NumGoroutine())
    t.Log(AllResponse())
    time.Sleep(time.Second * 1)
    t.Log("after: ", runtime.NumGoroutine())
}
