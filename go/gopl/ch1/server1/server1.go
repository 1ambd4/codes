package main

import "fmt"
import "net/http"
import "log"

func main() {
    http.HandleFunc("/", handler)
    log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

func handler(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintf(w, "URL.PATH = %p\n", r.URL.Path)
}
