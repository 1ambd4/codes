#include <iostream>
#include <vector>
#include <type_traits>

int main()
{
    auto func_ptr = +[]{};
    std::cout << typeid(func_ptr).name() << std::endl;
    static_assert(std::is_same<decltype(func_ptr), void(*)()>::value);
    return 0;
}

