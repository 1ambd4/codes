package main

// 通过共享变量并上锁的方式解决并发问题

type Func func(key string) (interface{}, error)

type result struct {
    value   interface{}
    err     error
}

// 记忆化
type Memo struct {
    f       Func
    cache   map[string]result
    // cache   sync.Mutex
}

func New(f Func) *Memo {
    return &Memo{f: f, cache: make(map[string]result)
}

func (memo *Memo) Get(key string) (interface{}, error) {
    res, ok := memo.cache[key]
    if !ok {
        res.value, res.err = memo.f(key)
        memo.cache[key] = res   // 线程不安全
    }

    return res.value, res.err
}

// 但如果简单的上锁，又让并行变化回了串行
// func (memo *Memo) Get(key string) (interface{}, error) {
//     memo.mu.Lock()
//     res, ok := memo.cache[key]
//     if !ok {
//         res.value, res.err = memo.f(key)
//         memo.cache[key] = res   // 线程不安全
//         // 但如果简单的上锁，又让并行变化回了串行
//     }
//     memo.mu.Unlock()
// 
//     return res.value, res.err
// }

// 优化一下上锁
// func (memo *Memo) Get(key string) (interface{}, error) {
//     memo.mu.Lock()
//     res, ok := memo.cache[key]
//     memo.mu.Unlock()
//     if !ok {
//         res.value, res.err = memo.f(key)
//         memo.mu.Lock()
//         memo.cache[key] = res   // 线程不安全
//         memo.mu.Unlock()
//         // 但如果简单的上锁，又让并行变化回了串行
//     }
// 
//     return res.value, res.err
// }

// 每次调用的开销都不小，因而做记忆化
func httpGetBody(url string) (interface{}, error) {
    resp, err := http.Get(url)
    if err != nil {
        return nil, err
    }
    defer resp.Body.Close()
    return ioutil.ReadAll(resp.Body)
}

func main() {
    m := memo.New(httpGetBody)
    var n sync.WaitGroup
    for url := range incommingURLs() {
        n.Add(1)
        go func() {
            start := time.Now()
            value, err := m.Get(url)
            if err != nil {
                log.Print(err)
            }
            fmt.Prinf("%s, %s, %d bytes\n",
                url, time.Since(start), len(value.([]byte)))
            n.Done()
        }(url)
    }
}
