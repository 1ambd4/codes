package function_test

import "testing"

func Square(n int) int {
    return n * n
}

func TestSquare(t *testing.T) {
    inputs := [...]int { 1, 2, 3, 4 }
    expected := [...]int { 1, 4, 9, 16 }

    for i := 0; i < len(inputs); i++ {
        ret := Square(inputs[i])
        if ret != expected[i] {
            t.Errorf("input is %d, expected %d but has %d",
                inputs[i], expected[i], ret)
        }
    }
}
