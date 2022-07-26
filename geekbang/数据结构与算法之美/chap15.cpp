#include <iostream>
#include <vector>

using namespace std;

// 这一章主要讲了二分查找
// 目前看来，没有labuladong讲解得深刻

int binary_search(const vector<int>& nums, int value)
{
    int left = 0, right = nums.size();

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == value) {
            return mid;
        } else if (nums[mid] > value) {
            right = mid;
        } else if (nums[mid] < value) {
            left = mid;
        }
    }

    return -1;
}


// 递归实现

int binary_search_recursion(const vector<int>& nums, int left, int right, int value)
{
    if (left >= right) return -1;

    int mid = left + (right - left) / 2;

    if (nums[mid] == value) {
        return mid;
    } else if (nums[mid] > value) {
        return binary_search_recursion(nums, left, mid, value);
    } else if (nums[mid] < value) {
        return binary_search_recursion(nums, mid, right, value);
    }
}

int binary_search_recursion(const vector<int>& nums, int value)
{
    return binary_search_recursion(nums, 0, nums.size(), value);
}


int lower_bound(const vector<int>& nums, int value)
{
    int left = 0, right = nums.size();

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] >= value) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    if (left < nums.size() && nums[left] == value) {
        return left;
    } else {
        return -1;
    }
}

int upper_bound(const vector<int>& nums, int value)
{
    int left = 0, right = nums.size();

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] <= value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if (right <= nums.size() && nums[right-1] == value) {
        return right-1;
    } else {
        return -1;
    }
}


// 在精确查找方面，二分较之散列表或者二叉查找树的优势并不太明显
// 但当如下的近似查找，二分法就显得很优雅
int first_greater_or_equal_than(const vector<int>& nums, int value)
{
    int left = 0, right = nums.size();

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] >= value) {
            if (mid == 0 || nums[mid-1] < value) {
                return mid;
            } else {
                right = mid;
            }
        } else {
            left = mid;
        }
    }

    return -1;
}


int last_less_or_equal_than(const vector<int>& nums, int value)
{
    int left = 0, right = nums.size();

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] <= value) {
            if (mid == nums.size()-1 || nums[mid+1] > value) {
                return mid;
            } else {
                left = mid;
            }
        } else {
            right = mid;
        }
    }
}


int main()
{
    vector<int> nums1 { 1, 2, 4, 5, 7, 8, 9 };
    cout << "binary_search of 5: " << binary_search(nums1, 5) << endl;
    cout << "binary_search_recursion of 5: " << binary_search_recursion(nums1, 5) << endl;

    vector<int> nums2 { 1, 1, 2, 2, 3, 4, 5, 5, 5, 6, 8, 8, 9 };
    cout << "lower_bound of 5: " << lower_bound(nums2, 5) << endl;
    cout << "upper_bound of 5: " <<  upper_bound(nums2, 5) << endl;
    cout << "first_greater_or_equal_than 5: " << first_greater_or_equal_than(nums2, 5) << endl;
    cout << "last_less_or_equal_than 5: " << last_less_or_equal_than(nums2, 5) << endl;

    cout << "first_greater_or_equal_than 7: " << first_greater_or_equal_than(nums2, 7) << endl;
    cout << "last_less_or_equal_than 7: " << last_less_or_equal_than(nums2, 7) << endl;

    return 0;
}
