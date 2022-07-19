#include <iostream>
#include <vector>

using namespace std;

// 归并排序
// 递推公式：
//     merge_sort[l,r) = merge(merge_sort[l,m), merge_sort[m,r))
// 时间复杂度：
//     T(n) = 2 * T(n/2) + n
//     T(1) = C
// 归并排序的特点是算法的执行效率与原始数据的有序程度无关
// 因而不会出现效率特别差的情况（当然也不会出现效率特别好的情况
// 当然喽，尽管时间效率较之快排可能好些，但其缺点是并非原地算法，需要O(n)的额外空间

// [l, m) [m,r)
vector<int> merge(vector<int>& nums, int l, int m, int r)
{
    vector<int> res;

    int i1 = l, i2 = m;
    while (i1 < m && i2 < r) {
        if (nums[i1] <= nums[i2]) {
            res.push_back(nums[i1++]);
        } else {
            res.push_back(nums[i2++]);
        }
    }

    while (i1 < m) {
        res.push_back(nums[i1++]);
    }
    while (i2 < r) {
        res.push_back(nums[i2++]);
    }

    // 这个步骤不要忘记
    for (int i = 0; i < res.size(); ++i) {
        nums[l+i] = res[i];
    }

    return res;
}

// [l, m) [m,r)
void merge_sort(vector<int>& nums, int l, int r)
{
    if (l == r-1) return ;

    int m = l + (r - l) / 2;

    merge_sort(nums, l, m);
    merge_sort(nums, m, r);
    merge(nums, l, m, r);
}

vector<int> merge_sort(vector<int> nums)
{
    merge_sort(nums, 0, nums.size());
    return nums;
}


// 快速排序
// 递推公式：
//     quick_sort[l,r] = quick_sort[l,m-1] + quick_sort[m+1,r]

// 分区这一步的操作有很多的实现方法
// 如类似插入排序的方法实现分区，简洁高效
// 总之无论怎样，最终实现pivot将区间分隔开即可
// int partition(vector<int>& nums, int l, int h)
// {
//     int pivot = nums[h];
//     int id = l;
//     for (int i = l; i < h; ++i) {
//         if (nums[i] < pivot) {
//             swap(nums[id++], nums[i]);
//         }
//     }
//     swap(nums[id], nums[h]);
//     return id;
// }

int partition(vector<int>& nums, int l, int h)
{
    int pivot = nums[l];
    while (l <= h) {
        while (l <= h && nums[h] >= pivot) {
            --h;
        }
        swap(nums[l], nums[h]);
        while (l <= h && nums[l] <= pivot) {
            ++l;
        }
        swap(nums[l], nums[h]);
    }
    return l;
}

// [l,r]
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


// 归并排序和快速排序很是相似
// 根本的区别在于归并排序是自底向上的，即先处理子问题
// 而快速排序是自顶向下的，后处理子问题


// O(n)的求无序数组中的第K大元素
// 类似快排partition的操作，无需整体有序
// 只要pivot左边均小于pivot，pivot右边均大于pivot即可
// 之后在pivot的左右两边区间继续找即可
// 理想的时间复杂度为: n + n/2 + n/4 + ... + 1 = 2n-1


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

// merge_sort: 0.0135835
// quick_sort: 0.00224164
// 快排，赢


int main()
{
    vector<int> nums { 5, 3, 1, 4, 6, 2, 0, 8, 9 };
    vector<int> res1 = merge_sort(nums);
    for (int i = 0; i < res1.size(); ++i) {
        printf(",%d" + !i, res1[i]);
    }

    cout << '\n';

    vector<int> res2 = quick_sort(nums);
    for (int i = 0; i < res2.size(); ++i) {
        printf(",%d" + !i, res2[i]);
    }

    cout << '\n';


    cout << "merge_sort: " << benchmark(merge_sort, 10000) << endl;
    cout << "quick_sort: " << benchmark(quick_sort, 10000) << endl;

    return 0;
}
