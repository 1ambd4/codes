package main

import "fmt"
import "net/http"
import "os"
import "io"

func main() {
    // for _, url := range os.Args[1:] {
    //     resp, err := http.Get(url)
    //     if err != nil {
    //         fmt.Fprintf(os.Stderr, "fetch: %v\n", err)
    //         os.Exit(1)
    //     }
    //     b, err := ioutil.ReadAll(resp.Body)
    //     resp.Body.Close()
    //     if err != nil {
    //         fmt.Fprintf(os.Stderr, "fetch: %s: %v\n", url, err)
    //         os.Exit(1)
    //     }
    //     fmt.Printf("%s", b)
    // }

    for _, url := range os.Args[1:] {
        resp, err := http.Get(url)
        if err != nil {
            fmt.Fprintf(os.Stderr, "fetch: %v\n", err)
            os.Exit(1)
        }
        _, err = io.Copy(os.Stdout, resp.Body)
        resp.Body.Close()
        // 这儿的错误检查怪怪的啊
        if err != nil {
            fmt.Fprintf(os.Stderr, "fetch: %s: %v\n", url, err)
            os.Exit(1)
        }
    }
}
