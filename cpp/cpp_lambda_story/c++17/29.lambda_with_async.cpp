#include <iostream>
#include <vector>

#include <future>   // for async and future
#include <numeric>

// 另一种利用多线程的方式是std::async

int main()
{
    const auto print_thread_id = [](const char* str) {
        // std::cout << str << ": " 
        //     << std::this_thread::get_id() << " thread id\n";  
    };

    std::vector<int> numbers(100);

    std::future<void> iota_future = std::async(std::launch::async,
            [&numbers, start_arg = 10, &print_thread_id]() {
                std::iota(numbers.begin(), numbers.end(), start_arg);
                print_thread_id("iota in");
            }
    );

    iota_future.get();
    print_thread_id("printing numbers in");
    for (const auto& num : numbers) {
        std::cout << num << ", ";
    }
    std::cout << std::endl;
    return 0;
}
