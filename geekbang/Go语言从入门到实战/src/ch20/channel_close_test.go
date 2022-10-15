package channel_close

import "testing"
import "sync"
import "fmt"

func dataProducer(ch chan int, wg *sync.WaitGroup) {
    go func() {
        for i := 0; i < 10; i++ {
            ch <- i
        }

        // 不关闭通道的话，通道的另一边会陷入阻塞
        close(ch)
        wg.Done()
        fmt.Println("dataProducer have done")
    }()
}

func dataConsumer(ch chan int, wg *sync.WaitGroup) {
    go func() {
        for {
            if data, ok := <-ch; ok {
                fmt.Println(data)
            } else {
                break
            }
        }
        wg.Done()
        fmt.Println("dataConsumer have done")
    }()
}

func TestCloseChannel(t *testing.T) {
    var wg sync.WaitGroup

    ch := make(chan int)
    
    wg.Add(1)
    dataProducer(ch, &wg)

    wg.Add(1)
    dataConsumer(ch, &wg)

    wg.Wait()
}
