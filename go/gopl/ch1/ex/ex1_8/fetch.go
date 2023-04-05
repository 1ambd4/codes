package main

import "fmt"
import "io/ioutil"
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
        b, err := ioutil.ReadAll(resp.Body)
        resp.Body.Close()
        if err != nil {
            fmt.Fprintf(os.Stderr, "fetch: %s: %v\n", url, err)
            os.Exit(1)
        }
        fmt.Printf("%s", b)
    }
}
