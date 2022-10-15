package extension_test

import "fmt"
import "testing"

type Pet struct {
}

func (p *Pet) Speak() {
    fmt.Print("...")
}

func (p *Pet) SpeakTo(master string) {
    p.Speak()
    fmt.Println(" ", master)
}


type Dog struct {
    // p *Pet
    Pet   // 结构体嵌套和匿名成员
}

// func (d *Dog) Speak() {
//     fmt.Print("Wang!")
// }


func TestDog(t *testing.T) {
    dog := new(Dog)
    dog.SpeakTo("hahaha")
}
