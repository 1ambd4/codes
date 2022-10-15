package benchmark_test

import "bytes"
import "testing"

// go test -bench=.

func BenchmarkConcatStringByAdd(b *testing.B) {
    elems := []string { "1", "2", "3", "4", "5" }
    
    b.ResetTimer()
    for i := 0; i < b.N; i++ {
        ret := ""
        for _, elem := range elems {
            ret += elem
        }
    }
    b.StopTimer()
}

func BenchmarkConcatStringByByteBuffer(b *testing.B) {
    elems := []string { "1", "2", "3", "4", "5" }

    b.ResetTimer()
    for i := 0; i < b.N; i++ {
        var buf bytes.Buffer

        for _, elem := range elems {
            buf.WriteString(elem)
        }
    }
    b.StopTimer()
}
