package main

import "os"
import "fmt"
import "bufio"

func main() {
    counts := make(map[string]int)
    files := os.Args[1:]
    dups := make(map[string]bool)

    if len(files) == 0 {
        if haveDupLines(os.Stdin, counts) {
            dups["os.Stdin"] = true
        }
    } else {
        for _, filename := range files {
            f, err := os.Open(filename)
            if err != nil {
                fmt.Fprintf(os.Stderr, "dup: %v", err)
                continue
            }
            if haveDupLines(f, counts) {
                dups[filename] = true
            }
            f.Close()
        }
    }

    for str, ok := range dups {
        if ok {
            fmt.Printf("%s\n", str)
        }
    }
}

func haveDupLines(f *os.File, counts map[string]int) bool {
    input := bufio.NewScanner(f)
    cnts := 0
    old_length := len(counts)

    for input.Scan() {
        cnts++
        counts[input.Text()]++
    }

    return len(counts) != old_length + cnts
}
