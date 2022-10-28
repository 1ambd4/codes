package main

import "fmt"
import "log"
import "encoding/json"

// JSON标签
// omitempty的意思是如果这个字段是零值或空值，则省略
type Movie struct {
    Title string
    Year  int `json:"released"`
    Color bool `json:"color,omitempty"`
    Actors []string
}

func main() {
    var movies = []Movie{
        {Title: "Casablanca", Year: 1942, Color: false, Actors: []string { "Mike", "Nancy", "Jobs" }},
        {Title: "iCool Hand Luke", Year: 1967, Color: true, Actors: []string { "Mike", "Nancy", "Jobs" }},
        {Title: "Bullitt", Year: 1968, Color: true, Actors: []string { "Mike", "Nancy", "Jobs" }},
    }

    fmt.Printf("%#v\n", movies)

    // marshal生成的结果是一个字节slice
    data, err := json.Marshal(movies)
    if err != nil {
        log.Fatalf("JSON marshaling failed: %s", err)
    }
    fmt.Printf("%s\n", data)

    // 格式化打印，最后一个参数是定义缩进的字符串
    indentData, err := json.MarshalIndent(movies, "", "    ")
    if err != nil {
        log.Fatalf("JSON marshaling failed: %s", err)
    }
    fmt.Printf("%s\n", indentData)

    // marshal的逆向操作是unmarshal

    // 定义取出JSON中的哪些字段
    var titles []struct { Title string }
    if err := json.Unmarshal(data, &titles); err != nil {
        log.Fatalf("JSON unmarshaling failed: %s", err)
    }
    fmt.Println(titles)
}
