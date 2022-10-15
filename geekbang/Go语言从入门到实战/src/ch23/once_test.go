package once_test

import "testing"
import "sync"
import "unsafe"
import "fmt"

type Singleton struct {
    data string
}

var singleInstance *Singleton
var once sync.Once

func GetSingletonObj() *Singleton {
    once.Do(func() {
        fmt.Println("create obj")
        singleInstance = new(Singleton)
    })
    return singleInstance
}

func TestGetSingletonObj(t *testing.T) {
    var wg sync.WaitGroup

    for i := 0; i < 10; i++ {
        wg.Add(1)
        go func() {
            obj := GetSingletonObj()
            fmt.Printf("%x\n", unsafe.Pointer(obj))
            wg.Done()
        }()
    }
    wg.Wait()
}
