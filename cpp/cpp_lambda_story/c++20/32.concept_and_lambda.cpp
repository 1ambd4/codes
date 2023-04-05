#include <iostream>
#include <vector>

// concept感觉就像是tempalte约束性太松了
// 然后人为的加以限制
template <typename T>
concept signed_integral =
    std::is_integral_v<T> && std::is_signed_v<T>;

template <signed_integral T>
void printer(T val) { }


// concept不止可以约束类型
// 也可以对函数返回值做约束
template <typename T>
concept renderable = requires(T v) {
    { v.render() } -> std::same_as<void>;
    { v.get_vect_count() } -> std::convertible_to<size_t>;
};

struct circle {
    void render() {
        std::cout << "drawing circle\n";
    }

    size_t get_vect_count() const {
        return 10;
    }
};

struct square {
    void render() {
        std::cout << "drawing square\n";
    }

    int get_vect_count() const {
        return 4;
    }
};

int main()
{
    int val = 22;
    // unsigned int val = 233;
    printer(val);

    // lambda with concept
    auto lambda1 = [](signed_integral auto val) { };

    // 那么是不是还可以这么用？
    signed_integral auto a = 233;
    // 真可以啊
    std::cout << a << std::endl;
    std::cout << typeid(a).name() << std::endl;
    std::cout << typeid(1).name() << std::endl;


    // 就像是定义了一个接口？ 
    // 有点儿意思啊
    const auto render_caller = [](renderable auto& obj) {
        obj.render();
    };

    circle c;
    render_caller(c);
    square s;
    render_caller(s);
    return 0;
}
