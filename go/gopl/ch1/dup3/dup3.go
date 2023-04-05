package main

import "os"
import "fmt"
import "io/ioutil"
import "strings"

func main() {
    counts := make(map[string]int)

    for _, filename := range os.Args[1:] {
        // dup2打开文件后一行行的读取
        // dup3直接一次性将文件内容全部读取出来
        data, err := ioutil.ReadFile(filename)
        if err != nil {
            fmt.Fprintf(os.Stderr, "dup3: %v", err)
            continue
        }
        for _, str := range strings.Split(string(data), "\n") {
            counts[str]++
        }
    }

    for str, cnt := range counts {
        if cnt > 1 {
            fmt.Printf("%d\t%s\n", cnt, str)
        }
    }
}
