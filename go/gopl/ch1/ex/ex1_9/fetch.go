package main

import "fmt"
import "net/http"
import "os"
import "strings"

func main() {
    for _, url := range os.Args[1:] {
        if !strings.HasPrefix(url, "https://") && !strings.HasPrefix(url, "http://") {
            url = "https://" + url
        }
        resp, err := http.Get(url)
        if err != nil {
            fmt.Fprintf(os.Stderr, "fetch: %v\n", err)
            os.Exit(1)
        }
        fmt.Printf("HTTP Status: %s\n", resp.Status)
        resp.Body.Close()
    }
}
