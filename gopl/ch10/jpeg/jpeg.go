package main

import (
    "fmt"
    "image"
    "image/jpeg"
    _ "image/png"   // 重命名 image/png 为 _，这表示空白导入
    "io"
    "os"
)

// 空白导入的应用场景
// Go不允许导入不使用的包
// 但有些时候可能并不需要调用包里的函数或者使用数据
// 仅仅是想利用导包的副作用：对包级别的变量执行初始化表达式求值
// 比如这里就是向 image.Decode 注册 png解码器

func main() {
    if err := toJPEG(os.Stdin, os.Stdout); err != nil {
        fmt.Fprintf(os.Stderr, "jpeg: %v\n", err)
        os.Exit(1)
    }
}

func toJPEG(in io.Reader, out io.Writer) error {
    img, kind, err := image.Decode(in)
    if err != nil {
        return err
    }
    fmt.Fprintln(os.Stderr, "Input format = ", kind)
    return jpeg.Encode(out, img, &jpeg.Options{ Quality: 95 })
}

// 空白导入的例子还有数据库驱动的加载
// import (
//     "database/sql"
//     _ "github.com/lib/pq"               // Postgres
//     _ "github.com/go-sql-driver/mysql"  // MySQL
// )
// db, err = sql.Open("postgres", dbname)  // ok
// db, err = sql.Open("mysql", dbname)     // ok
// db, err = sql.Open("sqlite3", dbname)   // ok
