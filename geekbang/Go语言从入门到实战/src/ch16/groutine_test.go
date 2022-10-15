package groutine_test

import "testing"
import "time"

func TestGroutine(t *testing.T) {
    for i := 0; i < 10; i++ {
        // 协程，匿名方法前面加上关键字go即可
        go func(v int) {
            t.Log(v)
        }(i)
    }
    time.Sleep(time.Millisecond * 10)
}
