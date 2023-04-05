package main

import "fmt"
import "os"
import "bufio"

func main() {
    counts := make(map[string]int)
    files := os.Args[1:]

    if len(files) == 0 {
        countLines(os.Stdin, counts)
    } else {
        for _, arg := range files {
            f, err := os.Open(arg)
            if err != nil {
                fmt.Fprintf(os.Stderr, "dup2: %v\n", err)
                continue
            }
            countLines(f, counts)
            f.Close()
        }
    }

    for str, cnt := range counts {
        if cnt > 1 {
            fmt.Printf("%d\t%s\n", cnt, str)
        }
    }
}

func countLines(f *os.File, counts map[string]int) {
    input := bufio.NewScanner(f)
    
    for input.Scan() {
        counts[input.Text()]++
    }
}
