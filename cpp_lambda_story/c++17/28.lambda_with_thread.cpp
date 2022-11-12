#include <iostream>
#include <thread>
#include <vector>
#include <numeric> // for std::iota
#include <atomic>

int main() {
    const auto print_thread_id = [](const char* str) {
        std::cout << str << ": " 
            << std::this_thread::get_id() << " thread id\n";  
    };

    std::vector<int> numbers(100);

    std::thread iota_thread([&numbers, &print_thread_id](int start_arg) {
            std::iota(numbers.begin(), numbers.end(), start_arg);
            print_thread_id("iota in");
        }, 10);

    iota_thread.join();
    print_thread_id("printing numbers in");

    for (auto& num : numbers)
        std::cout << num << ", ";
    std::cout << std::endl;


    // int cnt = 0;
    std::atomic<int> cnt = 0;

    const auto max_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    threads.reserve(max_threads);

    for (size_t i = 0; i < max_threads; ++i) {
        threads.push_back(std::thread([&cnt]() noexcept {
                    for (int j = 0; j < 1000; ++j) {
                        // ++cnt;
                        // --cnt;
                        // ++cnt;
                        // --cnt;
                        cnt.fetch_add(1);
                        cnt.fetch_sub(1);
                        cnt.fetch_add(1);
                        cnt.fetch_sub(1);
                    }
                }));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "max_threads: " << max_threads << std::endl;
    std::cout << "cnt: " << cnt << std::endl;
    return 0;
}
