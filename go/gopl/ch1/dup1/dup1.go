package main

import "fmt"
import "bufio"
import "os"

func main() {
    counts := make(map[string]int)
    input := bufio.NewScanner(os.Stdin)

    // Scan()读取一行，Text()获取读入的字符
    for input.Scan() {
        // 访问map中不存在的键时，其值为zero value，此时int对应为0
        counts[input.Text()]++
    }

    // Go里对键的迭代顺序是不固定的，通常是随机的
    // 这是有意设计的，以防止程序依赖于某种特定的序列
    for str, cnt := range counts {
        if (cnt > 1) {
            fmt.Printf("%d\t%s\n", cnt, str)
        }
    }
}
