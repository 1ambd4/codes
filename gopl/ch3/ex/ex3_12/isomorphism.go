package main

import "fmt"

// map存一下？
// 还是说就当只有ASCII？
func IsOmorphism(s1, s2 string) bool {
    n1, n2 := len(s1), len(s2)
    if n1 != n2 {
        return false
    }

    a1, a2 := []rune(s1), []rune(s2)

    for _, v := range a1 {
        fmt.Println(v)
    }

    for _, v := range a2 {
        fmt.Println(v)
    }

    return true
}

func main() {
}
