package main

import "fmt"
import "net/http"
import "sync"
import "log"

var mu sync.Mutex
var cnt int

func main() {
    http.HandleFunc("/", handler)
    http.HandleFunc("/count/", count)
    log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func handler(w http.ResponseWriter, r *http.Request) {
    mu.Lock()
    cnt++
    mu.Unlock()
    fmt.Fprintf(w, "URL.PATH = %q\n", r.URL.Path)
}

func count(w http.ResponseWriter, r *http.Request) {
    mu.Lock()
    fmt.Fprintf(w, "counter: %d\n", cnt)
    mu.Unlock()
}
