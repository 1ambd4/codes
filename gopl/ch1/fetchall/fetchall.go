package main

import "fmt"
import "os"
import "io"
import "io/ioutil"
import "time"
import "net/http"
import "strings"

func main() {
    start := time.Now()
    ch := make(chan string)
    for _, url := range os.Args[1:] {
        go fetch(url, ch)
    }
    for range os.Args[1:] {
        fmt.Println(<-ch)
    }
    fmt.Printf("%.2fs elapsed\n", time.Since(start).Seconds())
}

func fetch(url string, ch chan<-string) {
    if !strings.HasPrefix(url, "http://") && !strings.HasPrefix(url, "https://") {
        url = "https://" + url
    }
    start := time.Now()

    resp, err := http.Get(url)
    if err != nil {
        // channel当成字符流用么
        ch <- fmt.Sprint(err)
        return
    }

    // iotuil.Discard
    nbytes, err := io.Copy(ioutil.Discard, resp.Body)
    resp.Body.Close()
    if err != nil {
        ch <- fmt.Sprintf("while reading %s: %v", url, err)
        return
    }

    secs := time.Since(start).Seconds()
    ch <- fmt.Sprintf("%.2fs %7d %s", secs, nbytes, url)
}
