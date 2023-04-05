#include <iostream>
#include <vector>
#include <numeric>

#include <execution>

// std::execution::par
// std::execution::seq
// std::execution::par_unseq

using namespace std;

#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <climits>

// eq: 74.1482
void seq_func(vector<int> nums) {
    clock_t start = clock();
    std::sort(std::execution::seq, nums.begin(), nums.end());
    clock_t finish = clock();
    std::cout << "seq: " << (double)(finish - start) / CLOCKS_PER_SEC << "\n";
}

// par: 73.8114
void par_func(vector<int> nums) {
    clock_t start = clock();
    std::sort(std::execution::par, nums.begin(), nums.end());
    clock_t finish = clock();
    std::cout << "par: " << (double)(finish - start) / CLOCKS_PER_SEC << "\n";
}

int main()
{
    std::vector<int> vec(1000);
    std::iota(vec.begin(), vec.end(), 0);
    std::vector<int> output;
    std::for_each(std::execution::par, vec.begin(), vec.end(),
            [&output](int& elem) {
                if (elem % 2 == 0) {
                    output.push_back(elem);
                }
            });

    for (const auto & elem : output) {
        std::cout << elem << ", ";
    }
    std::cout << std::endl;


    srand(time(NULL));
    vector<int> nums(100000000);
    for (int i = 0; i < nums.size(); ++i) {
        nums[i] = rand() % INT_MAX;
    }
    seq_func(nums);
    par_func(nums);
    return 0;
}

