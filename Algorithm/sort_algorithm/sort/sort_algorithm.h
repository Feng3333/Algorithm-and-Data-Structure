/* 
 * Description: 各种排序的实现方式, 以 vector<int> 为例
 * Create: 2023-12-26
 * Owner: 
 */

#ifndef SORT_ALGORITHM
#define SORT_ALGORITHM

#include <iostream>
#include <vector>

namespace SortAlgorithm {

/* 冒泡排序 */
void BubbleSort(std::vector<int>& nums)
{
    int len = nums.size();

    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - i - 1; ++j) {
            // 默认从小到大排序
            if (nums[j] > nums[j + 1]) {
                std::swap(nums[j], nums[j + 1]);
            }
        }
    }
}


/* 选择排序 */
void SelectionSort(std::vector<int>& nums) 
{
    int len = nums.size();
    for (int i = 0; i < len ; ++i) {
        int index = i;
        // 找到剩余乱序数组中的最小元素
        for (int j = i + 1; j < len; ++j) {
            if (nums[j] < nums[index]) {
                index = j;
            }
        }

        if (index != i) {
            std::swap(nums[index], nums[i]);
        }
    }

}


/* 插入排序 */
void InsertSort(std::vector<int>& nums)
{
    int len = nums.size();

    for (int i = 1; i < len; ++i) {
        int key = nums[i];
        int j = i - 1;

        // 将当前位置的元素插入前面已排好的序列中
        while (j >= 0 && nums[j] > key) {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;

        for (int k = 0; k < len; ++k) {
            std::cout << nums[k] << " ";
        }
        std::cout << std::endl;
    }
}


/* 希尔排序 时间复杂度为 O(nlogn) */
void ShellSort(std::vector<int>& nums)
{
    int len = nums.size();

    // 定义增量序列
    for (int gap = len / 2; gap > 0; gap /= 2) {
        // 对每个子序列进行排序
        for (int i = gap; i < len; ++i) {
            int temp = nums[i];
            int j;
            for (j = i; j >= gap && nums[j - gap] > temp; j -= gap) {
                nums[j] = nums[j - gap];
            }
            nums[j] = temp;
        }
    }
}


/* 快速排序 */
void QuickSort(std::vector<int>& nums, int start, int end)
{
    if (start > end) {
        return;
    }

    int i = start, j = end;
    int baseVal = nums[(start + end) / 2];  // 基准数
    while(i <= j) {
        while (nums[i] < baseVal) {
            i++;
        }
        while (nums[j] > baseVal) {
            j--;
        }

        if (i <= j) {
            std::swap(nums[i], nums[j]);
            ++i;
            --j;
        }
    }

    if (start < j) {
        QuickSort(nums, start, j);
    }
    if (i < end) {
        QuickSort(nums, i, end);
    }
}


/* 归并排序 */
// 合并两个有序数组
void Merge(std::vector<int>& nums, int left, int mid, int right)
{
    std::vector<int> tmp(right - left + 1);
    int i = left, j = mid + 1, k =0;
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            tmp[k++] = nums[i++];
        } else {
            tmp[k++] = nums[j++];
        }
    }

    while (i <= mid) {
        tmp[k++] = nums[i++];
    } 
    while (j <= right) {
        tmp[k++] = nums[j++];
    }

    for (int p = 0; p < k; ++p) {
        nums[left + p] = tmp[p];
    }
}

// 归并排序
void MergeSort(std::vector<int>& nums, int left, int right)
{
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    MergeSort(nums, left, mid);
    MergeSort(nums, mid + 1, right);
    Merge(nums, left, mid, right);
}


/* 堆排序 */
void HeapAdjust(std::vector<int>& nums, int i, int len)
{
    int max = i;
    //当前节点左右孩子节点的下标
    int lChild = i * 2 + 1;
    int rChild = i * 2 + 2;

    if (lChild < len && nums[lChild] > nums[max]) {
        max = lChild;
    }
    if (rChild < len && nums[rChild] > nums[max]) {
        max = rChild;
    }

    // 若i处的值比其左右孩子节点的值小，就将其和最大值进行交换
    if (max != i) {
        std::swap(nums[i], nums[max]);
        HeapAdjust(nums, max, len);
    }
}

void HeapSort(std::vector<int>& nums)
{
    int n = nums.size();
    // 初始化堆
    // (n-1)/2 是二叉树中最后一个非叶子节点的序号
    for (int i = (n - 1) / 2; i >= 0; --i) {
        HeapAdjust(nums, i, n);
    }

    // 交换堆顶元素和最后一个元素
    for (int i = n - 1; i >= 0; --i) {
        int temp = nums[i];
        nums[i] = nums[0];
        nums[0] = temp;
        HeapAdjust(nums, 0, i);
    }
}


/**/

} // namespace SortAlgorithm
#endif // SORT_ALGORITHM