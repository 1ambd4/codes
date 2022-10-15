package main

import "fmt"
import "os"

func main() {
    // 命令行参数也得os.Args的方式获取
    if len(os.Args) > 1 {
        fmt.Println(os.Args)
    }
    fmt.Println("Hello World\n")
    // Go中main函数不支持返回值
    // 如果想要返回运行状态的话，可以使用os.Exit()
    // os.Exit(-1)
}
