package main

import "fmt"
import "net/http"
import "time"

func main() {
    http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
        fmt.Fprintf(w, "Hello HTTP!\n");
    })

    // URL以‘/’结尾则可以匹配所有的子路径
    // 且采用最长匹配规则
    http.HandleFunc("/time/", func(w http.ResponseWriter, r *http.Request) {
        t := time.Now()
        timeStr := fmt.Sprintf("{\"time\": \"%s\"}", t)
        w.Write([]byte(timeStr))
    })

    http.ListenAndServe(":8080", nil)
}
