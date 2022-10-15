package switch_test

import "runtime"
import "testing"

func TestSwitch(t *testing.T) {
    // 条件表达式不限制为常量或者整形
    // 单个case中，可以出现多个结果用逗号分隔的结果选项
    // Go不需要显示的添加break，默认就有了
    // 还有就是可以不设定switch之后的选择表达式，此时等价于多个if...else...
    switch os := runtime.GOOS; os {
    case "darwin":
        t.Log("macOS")
    case "linux":
        t.Log("Linux")
    default:
        t.Log("other os")
    }

    num := 2
    switch {
    case 0 <= num && num <= 3:
        t.Log("0 ~ 3")
    case 4 <= num && num <= 6:
        t.Log("4 ~ 6")
    case 7 <= num && num <= 9:
        t.Log("7 ~ 9")
    default:
        t.Log("9 ~ ...")
    }
}
