package struct_test

import "testing"
import "fmt"

// 自定义数据结构
type Employee struct {
    Id string
    Name string
    Age int
}

// 将方法绑定到结构上
func (e *Employee) String() string {
    return fmt.Sprintf("ID:%s - Name:%s - Age:%d", e.Id, e.Name, e.Age)
}

// 这样写的话，会有数据的复制开销
// func (e Employee) String() string {
//     return fmt.Sprintf("ID:%s - Name:%s - Age:%d", e.Id, e.Name, e.Age)
// }

func TestCreateObj(t *testing.T) {
    e0 := Employee{ "0", "Bob", 22 }

    e1 := Employee { Name: "Andy", Age: 30 }

    e2 := new(Employee)
    e2.Id = "2"
    e2.Name = "Rose"
    e2.Age = 32

    // 居然也会自动调用String()方法
    t.Log(e0)
    t.Log(e1)
    t.Log(e2)

    t.Logf("e0 is %T", e0)
    t.Logf("&e0 is %T", &e0)
    t.Logf("e1 is %T", e1)
    t.Logf("e2 is %T", e2)
}
