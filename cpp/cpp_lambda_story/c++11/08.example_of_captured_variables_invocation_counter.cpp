#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec { 1, 4, 2, 6, 3, 9, 8 };

    // 变量捕获可以做许多有意思的事情
    size_t cnt = 0;
    std::sort(vec.begin(), vec.end(), [&cnt](int a, int b) {
                ++cnt;
                return a < b;
            });
    std::cout << "times of comparisons: " << cnt << std::endl;

    for (const auto& v : vec) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;
    return 0;
}

