package interface_test

import "testing"

// 定义接口
type Programmer interface {
    WriteHelloWorld() string
}

type GoProgrammer struct {
}

func (goer *GoProgrammer) WriteHelloWorld() string {
    return "fmt.Println(\"Hello Wrold!\")"
}

func TestClient(t *testing.T) {
    // duck type
    var p Programmer
    p = new(GoProgrammer)
    t.Log(p.WriteHelloWorld())
}
