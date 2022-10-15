package context_test

import "context"
import "fmt"
import "testing"
import "time"

func isCancelled(ctx context.Context) bool {
    select {
    case <- ctx.Done():
        return true
    default:
        return false
    }
}

func TestContext(t *testing.T) {
    ctx, cancel := context.WithCancel(context.Background())

    for i := 0; i < 5; i++ {
        go func(i int, ctx context.Context) {
            for {
                if isCancelled(ctx) {
                    break
                }
                time.Sleep(time.Millisecond * 10)
            }
            fmt.Println(i, "cancelled")
        }(i, ctx)
    }

    cancel()
    time.Sleep(time.Second * 1)
}
