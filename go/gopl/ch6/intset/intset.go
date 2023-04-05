package main

import "fmt"
import "bytes"

// 简单位集合
type IntSet struct{
    words []uint64
}

func (s *IntSet) Has(x int) bool {
    // word表示在哪个words里，bit表示这个word的第几位来表示这个数字
    word, bit := x / 64, x % 64
    return word < len(s.words) && s.words[word]&(1<<bit) != 0
}

func (s *IntSet) Add(x int) {
    word, bit := x / 64, x % 64
    // 要先判断这个集合是否足够容纳下待添加
    for word > len(s.words) {
        s.words = append(s.words, 0)
    }
    s.words[word] |= (1<<bit)
}

func (s *IntSet) UnionWith(t *IntSet) {
    for i, tword := range t.words {
        if i < len(s.words) {
            s.words[i] |= tword
        } else {
            s.words = append(s.words, tword)
        }
    }
}

func (s *IntSet) Len() int {
    var cnt int = 0
    for i, word := range s.words {
        for j := 0; j < 64; ++j {
            if word & (1<<uint(j)) != 0 {
                cnt++
            }
        }
    }
    return cnt
}

func (s *IntSet) String() string {
    var buf bytes.Buffer
    buf.WriteByte('{')
    for i, word := range s.words {
        if word == 0 {
            continue
        }
        for j := 0; j < 64; j++ {
            if word & (1<<uint(j)) != 0 {
                // 这个if当真是简单粗暴呢
                if buf.len() > len("{") {
                    buf.WriteByte(' ')
                }
                fmt.Fprintf(&buf, "%d", 64 * i + j)
            }
        }
    }
    buf.WriteByte('}')
    return buf.String()
}

func main() {
    fmt.Println("intset")
}
