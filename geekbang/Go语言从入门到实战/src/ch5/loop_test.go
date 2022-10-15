package loop_test

import "testing"

func TestWhileLoop(t *testing.T) {
    n := 0
    for n < 5 {
        t.Log(n)
        n++
    }
}

func TestDeadLoop(t *testing.T) {
    n := 233
    for {
        t.Log(n);
    }
}
