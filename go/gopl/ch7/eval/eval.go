package main

import "fmt"
import "math"

// type Expr interface{} // 表达式
type Var string       // 变量
type literal float64  // 数字常量
type Env map[Var]float64

// 一元操作符
type unary struct {
    op rune
    x Expr
}

// 二元操作符
type binary struct {
    op rune
    x, y Expr
}

// 函数调用
type call struct {
    fn string
    args []Expr
}

// 将Eval方法增加到Expr接口里
type Expr interface {
    Eval(env Env) float64
}

// 变量直接去上下文里找，找不到就返回零值
func (v Var) Eval(env Env) float64 {
    return env[v]
}

// 常量直接返回自身
func (l literal) Eval(_ Env) float64 {
    return float64(l)
}

func (u unary) Eval(env Env) float64 {
    switch u.op {
    case '+':
        return +u.x.Eval(env)
    case '-':
        return -u.x.Eval(env)
    default:
        panic(fmt.Sprintf("unsupported unary operator: %q", u.op))
    }
}

func (b binary) Eval(env Env) float64 {
    switch b.op {
    case '+':
        return b.x.Eval(env) + b.y.Eval(env)
    case '-':
        return b.x.Eval(env) - b.y.Eval(env)
    case '*':
        return b.x.Eval(env) * b.y.Eval(env)
    case '/':
        return b.x.Eval(env) / b.y.Eval(env)
    default:
        panic(fmt.Sprintf("unsupported binary operator: %q", b.op))
    }
}

func (c call) Eval(env Env) float64 {
    switch c.fn {
    case "pow":
        return math.Pow(c.args[0].Eval(env), c.args[1].Eval(env))
    case "sin":
        return math.Sin(c.args[0].Eval(env))
    case "cos":
        return math.Cos(c.args[0].Eval(env))
    case "tan":
        return math.Tan(c.args[0].Eval(env))
    default:
        panic(fmt.Sprintf("unsupported function call: %q", c.fn))
    }
}

func main() {
    fmt.Println("eval")
}
