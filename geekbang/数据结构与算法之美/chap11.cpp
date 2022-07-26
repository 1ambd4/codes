#include <iostream>
#include <vector>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;

// 严格的概率论定量分析复杂度本身就很复杂，因而引入如下概念：
//
// 逆序度：a[i] > a[j]，如果i < j
// 有序度：a[i] <= a[j]，如果i < j
// 满有序度 = 逆序度 + 有序度
// 排序的过程就是增加有序度，减少逆序度，最终达到满有序度的状态。


// 冒泡排序有比较换交换两个操作
// 交换发生在相邻两元素间，看作一个整体的话，显然每次交换使得有序度增加1
// 那么，一共需要的交换次数在待排序数据给出的情况下是确定的
// 即有 交换次数 = 满有序度 - 逆序度
// 基于此，考虑冒泡排序的时间复杂度
// 满有序度为定值，n个数字两两组合，可用组合数公式求得：C(n,m) = n * (n-1) / 2
// 而逆有序度是数据相关的，取值范围是 [0, C(n,m)]
// 因而最好的情况下无需交换，最差的情况下需要交换C(n,m)次数
// 平均情况下的时间复杂度为C(n,m) / 2，即O(n^2)
vector<int> bubble_sort(vector<int> nums)
{
    int n = nums.size();

    if (n <= 1) return nums;

    for (int i = 0; i < n; ++i) {
        bool flag = false;

        for (int j = 0; j < n - i - 1; ++j) {
            if (nums[j] > nums[j+1]) {
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
                flag = true;
            }
        }

        // 当不再发生交换的时候，说明已经有序，可以提前退出
        if (!flag) break;
    }

    return nums;
}

vector<int> insertion_sort(vector<int> nums)
{
    int n = nums.size();

    if (n <= 1) return nums;

    for (int i = 1; i < n; ++i) {
        int temp = nums[i];

        int j = i - 1;

        for ( ; j >= 0; --j) {
            if (nums[j] > temp) {
                nums[j+1] = nums[j];
            } else {
                break;
            }
        }

        nums[j+1] = temp;
    }

    return nums;
}

// 选择排序是不稳定的
// 考虑比较典型的情况，如，当“大小”相同的元素中的一个在数组最开始的位置
// 那么第一次从其后选择了最小的一个元素交换位置
// 就打乱了这一堆相同元素的初始顺序，因而不稳定
vector<int> selection_sort(vector<int> nums)
{
    int n = nums.size();

    if (n <= 1) return nums;

    for (int i = 0; i < n; ++i) {
        int id = i;

        for (int j = i; j < n; ++j) {
            if (nums[j] < nums[id]) {
                id = j;
            }
        }
        int temp = nums[i];
        nums[i] = nums[id];
        nums[id] = temp;
    }

    return nums;
}

// 至于冒泡和插入选一个的话，冒泡好写，但好像插入更优
// 两者的交换次数都等于逆序度
// 但是冒泡排序交换借助临时变量，O(3n) > O(n)，因而会比插入排序慢一些
//
// bubble_sort   : 0.634699
// insertion_sort: 0.160893
// selection_sort: 0.226737

using pfunc = vector<int>(vector<int> );

double benchmark(pfunc func, size_t n)
{
    std::srand(0);
    double times = 0;
    for (size_t i = 0; i < n; ++i) {
        vector<int> nums;
        for (int j = 0; j < 1e4; ++j) {
            nums.push_back(std::rand());
        }
        clock_t start_time, end_time;
        start_time = clock();
        func(nums);
        end_time = clock();

        times += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    }

    return times / n;
}


int main()
{
    vector<int> nums { 5, 3, 1, 4, 6, 2, 0, 8, 9 };
    vector<int> res1 { bubble_sort(nums) };
    for (int i = 0; i < res1.size(); ++i) {
        printf(",%d" + !i, res1[i]);
    }

    cout << '\n';

    vector<int> res2 { insertion_sort(nums) };
    for (int i = 0; i < res2.size(); ++i) {
        printf(",%d" + !i, res2[i]);
    }

    cout << '\n';

    vector<int> res3 { selection_sort(nums) };
    for (int i = 0; i < res3.size(); ++i) {
        printf(",%d" + !i, res3[i]);
    }

    cout << '\n';

    cout << "bubble_sort: " << benchmark(bubble_sort, 1000) << endl;
    cout << "insertion_sort: " << benchmark(insertion_sort, 1000) << endl;
    cout << "selection_sort: " << benchmark(selection_sort, 1000) << endl;
    return 0;
}
