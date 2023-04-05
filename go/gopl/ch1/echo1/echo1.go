package main

import "fmt"
import "os"

func main() {
    var s string
    sep := ""

    // Go俺不会写啊
    for i := 1; i < len(os.Args); i++ {
        s += sep + os.Args[i]
        sep = " "
    }

    fmt.Println(s)
}
