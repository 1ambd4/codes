#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 桶排序与计数排序
// 桶排序的思想是：
//     1.在得知数据分布范围的情况下，将数据分段到m个桶；
//     2.桶内用诸如快排之类的排序算法，使得桶内有序；
//     3.各桶按序输出即可。
// 时间复杂度：
//     均分的情况下，每个桶内元素个数k=n/m
//     桶内快排，时间复杂度为O(k*logk)
//     m个桶的时间复杂度为O(m*k*logk)，即O(m*(n/m)*log(n/m)) = O(n*log(n/m))
//     当m接近n的时候，log(n/m)的值是一个非常小的数字，因而时间复杂度接近O(n)
//     但实际情况是，很难做到
//     比如，数据聚集在其中一个桶里，立刻退化成单纯的快排，时间复杂度变为O(nlogn)
//
// 桶排序看起来就好像是特殊分块的分块排序
//
// 当数据范围更小的时候，可以使用计数排序
// 比如统计分数排名，可以开一个大小为最高分与最低分差值的数组
// 数组下标对应分数，数组内存储对应分数的数据个数
// 统计完之后，计算前缀和
// 接着开一个和待排序数据大小相同的数组
// 依照着前缀和数组将数据一一安置到新开的数组中即完成排序
// 是比较有意思且好写的排序方法了，虽然用处不怎么大

vector<int> counting_sort(vector<int> nums)
{
    // C++11
    const auto [min, max] = std::minmax_element(nums.begin(), nums.end());
    vector<int> cnts(*max + 1);

    for (const auto& num : nums) {
        ++cnts[num];
    }

    for (int i = 1; i < cnts.size(); ++i) {
        cnts[i] = cnts[i] + cnts[i-1];
    }

    vector<int> res(nums.size());
    for (const auto& num : nums) {
        res[cnts[num] - 1] = num;
        --cnts[num];
    }

    return res;
}


// 终于到了同样用处不大想法朴素的基数排序了
// 先来看这么一个实际问题，排序10w个手机号码
// 首先可以肯定的是前面的几种排序方法是可以做的，但是效率可能都不怎么好
//
// 针对手机号这种特殊的定长整型数据，用基数排序会比较好一些
// 基数排序利用了稳定性
// 首先按照最低位排序，接着按照高一位排序，直到最高位
// 因为每位的排序都是稳定的，因而最后的结果是有序的
// 时间复杂度：
//     k位进行基数排序共需要k轮
//     每轮的n个数据用桶排序或者计数排序就可以降到O(n)
//     因而总的时间复杂度是O(k*n)，即O(n)


int partition(vector<int>& nums, int l, int h)
{
    int pivot = nums[l];
    while (l <= h) {
        while (l <= h && nums[h] >= pivot) {
            --h;
        }
        swap(nums[l], nums[h]);
        while (l <= h && nums[h] >= pivot) {
            ++l;
        }
        swap(nums[l], nums[h]);
    }
    return l;
}

void quick_sort(vector<int>& nums, int l, int r)
{
    if (l >= r) return ;

    int q = partition(nums, l, r);
    quick_sort(nums, l, q-1);
    quick_sort(nums, q+1, r);
}

vector<int> quick_sort(vector<int> nums)
{
    quick_sort(nums, 0, nums.size()-1);
    return nums;
}


using pfunc = vector<int>(vector<int> );

double benchmark(pfunc func, size_t n)
{
    std::srand(0);
    double times = 0;
    for (size_t i = 0; i < n; ++i) {
        vector<int> nums;
        for (int j = 0; j < 1e4; ++j) {
            nums.push_back(std::rand() % 10);
        }
        clock_t start_time, end_time;
        start_time = clock();
        func(nums);
        end_time = clock();

        times += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    }

    return times / n;
}


// 差距好明显啊
// counting_sort: 0.000518135
// quick_sort   : 0.0432692


int main()
{
    vector<int> nums { 1, 2, 1, 3, 6, 9, 2, 8, 0, 5, 2, 6, 8, 7, 2, 5, 4, 1, 4, 2, 8 };
    vector<int> res1 = counting_sort(nums);
    for (int i = 0; i < res1.size(); ++i) {
        printf(",%d" + !i, res1[i]);
    }

    cout << '\n';
    
    cout << "counting_sort: " << benchmark(counting_sort, 10000) << endl;
    cout << "quick_sort   : " << benchmark(quick_sort, 10000) << endl;

    return 0;
}
