package main

import "fmt"
import "os"
import "io"
import "net/http"
import "time"
import "strings"

func main() {
    start := time.Now()
    ch := make(chan string)

    for _, url := range os.Args[1:] {
        go fetch(url, ch, "0.html")
        go fetch(url, ch, "1.html")
    }

    for range os.Args[1:] {
        fmt.Println(<-ch)
        fmt.Println(<-ch)
    }

    fmt.Printf("%.2fs elapsed\n", time.Since(start).Seconds())
}

func fetch(url string, ch chan<-string, filename string) {
    if !strings.HasPrefix(url, "http://") && !strings.HasPrefix(url, "https://") {
        url = "https://" + url
    }

    start := time.Now()

    resp, err := http.Get(url)
    if err != nil {
        ch <- fmt.Sprint(err)
        return
    }

    // f, err := os.Open(filename)
    // os.Open()和os.OpenFile()有何区别？
    f, err := os.OpenFile(filename, os.O_CREATE | os.O_WRONLY, 0666)
    if err != nil {
        ch <- fmt.Sprintf("while opening %s: %v\n", filename, err)
    }

    nbytes, err := io.Copy(f, resp.Body)
    defer resp.Body.Close()
    defer f.Close()
    if err != nil {
        ch <- fmt.Sprintf("while reading %s: %v\n", url, err)
        return
    }

    secs := time.Since(start).Seconds()
    ch <- fmt.Sprintf("%.2fs %7d %s", secs, nbytes, url)
}
