package main

import "fmt"

// 感觉不如append
func remove(slice []string) []string {
    n := len(slice)
    if n <= 1 {
        return slice
    }

    j := 0
    for i := 1; i < n; i++ {
        if slice[i] != slice[j] {
            j++
            slice[j] = slice[i]
        }
    }

    return slice[:j+1]
}

func main() {
    slice := []string { "apple", "apple", "banana", "applee" }
    slice = remove(slice)
    fmt.Println(slice)
}
