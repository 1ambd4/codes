package main

import "fmt"

func nonempty(strings []string) []string {
    i := 0
    for _, s := range strings {
        if (s != "") {
            strings[i] = s
            i++
        }
    }
    return strings[:i]
}

func nonempty2(strings []string) []string {
    out := strings[:0]
    for _, s := range strings {
        if s != "" {
            out = append(out, s)
        }
    }
    return out
}

func main() {
    s := []string { "hhaha", "lalala", "" };
    fmt.Println(nonempty(s))
    // 原slice是没变动的
    fmt.Println(s)
    s = nonempty2(s)
    fmt.Println(s)
}
