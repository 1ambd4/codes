package shared_mem_test

import "testing"
import "time"
import "sync"

func TestCounter(t *testing.T) {
    counter := 0

    for i := 0; i < 5000; i++ {
        // 多个协程访问变量是线程不安全的
        go func() {
            counter++
        }()
    }

    time.Sleep(time.Millisecond * 50)
    t.Logf("counter = %d", counter)
}

func TestCounterThreadSafe(t *testing.T) {
    // 声明互斥锁
    var mut sync.Mutex
    
    counter := 0

    for i := 0; i < 5000; i++ {
        go func() {
            // 对互斥锁的释放放到defer里
            defer func() {
                mut.Unlock()
            }()
            // 访问共享数据之前先加锁
            mut.Lock()
            counter++
        }()
    }

    // sleep的方式并不优雅，更好的方式见下面的WaitGroup
    time.Sleep(time.Millisecond * 50)
    t.Logf("counter = %d", counter)
}

func TestWaitGroup(t *testing.T) {
    // 声明WaitGroup
    var wg sync.WaitGroup

    var mut sync.Mutex

    counter := 0

    for i := 0; i < 5000; i++ {
        // 增加
        wg.Add(1)
        go func() {
            defer func() {
                mut.Unlock()
            }()

            mut.Lock()
            counter++
            // 完成一个
            wg.Done()
        }()
    }

    // 等待所有的都完成
    wg.Wait()
    t.Logf("counter = %d", counter)
}
