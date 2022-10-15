package condition_test

import "testing"

func TestConditon(t *testing.T) {
    // Go的if支持定义变量，好耶（C++17也开始支持了

    if a := 1 == 1; a {
        t.Log("1 == 1")
    }
}

func TestMultiSelect(t *testing.T) {
    if v, err := foo(); err == nil {
        // failue
    } else {
        // ok
    }
}
