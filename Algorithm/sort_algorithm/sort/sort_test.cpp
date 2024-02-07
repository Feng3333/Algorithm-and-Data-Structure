#include "sort_algorithm.h"
#include "sleep_sort.h"

int main()
{
    std::vector<int> nums = {2, 5, 3, 9, 7, 4, 1, 10};

    std::cout << "Before sort: " << std::endl;
    for (int i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;

    // SortAlgorithm::HeapSort(nums);
    SortAlgorithm::SleepSort(nums);

    std::cout << std::endl;
    std::cout << "After sort: " << std::endl;
    for (int i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << " ";
    }

    return 0;
}