package main

import "os"
import "fmt"

func ErrExample(filenames []string) {
    for _, filename := range filenames {
        f, err := os.Open(filename)
        if err != nil {
            fmt.Println(err)
        }
        // 因为defer会延迟到retern之后执行
        // 因而此处循环里的defer都会被延迟到最后执行
        // 这就可能导致文件描述符耗尽（真有这么多文件么？
        defer f.Close()
    }
}

// 解决方法是在defer外面套一层函数
func Correct(filenames []string) {
    for _, filename := range filenames {
        if err := doFile(filename); err != nil {
            fmt.Println(err)
        }
    }
}

func doFile(filename string) error {
    f, err := os.Open(filename)
    if err != nil {
        return err
    }
    defer f.Close()
    return nil
}

func main() {
    fmt.Println("notice defer in loop")
}
