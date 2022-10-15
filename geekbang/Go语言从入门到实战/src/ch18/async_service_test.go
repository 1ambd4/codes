package async_service_test

import "testing"
import "time"
import "fmt"

func service() string {
    time.Sleep(time.Millisecond * 50)
    return "service have done"
}

func otherTask() {
    fmt.Println("working on other task")
    time.Sleep(time.Millisecond * 50)
    fmt.Println("other task have done")
}

func TestService(t *testing.T) {
    fmt.Println(service())
    otherTask()
}

func AsyncService() chan string {
    // 创建通道
    retCh := make(chan string)

    go func() {
        ret := service()
        fmt.Println("return result.")
        // 往通道里写数据
        retCh <- ret
        fmt.Println("service exited.")
    }()

    return retCh
}

func TestAsyncService(t *testing.T) {
    retCh := AsyncService()
    otherTask()
    // 这里取数据
    fmt.Println(<-retCh)
    time.Sleep(time.Millisecond * 50)
}
