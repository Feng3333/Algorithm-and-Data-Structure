/* 
 * Description: 睡眠排序
 * Create: 2024-02-06
 * Owner: 
 */

#ifndef SLEEP_SORT
#define SLEEP_SORT

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

namespace SortAlgorithm {

std::vector<int> tmp;
// 让线程睡眠 num 毫秒
void SetThreadSleepTime(int num)
{   
    tmp.clear();
    std::this_thread::sleep_for(std::chrono::milliseconds(num * 100));  // * 100是为了保证线程睡眠时间
    // std::cout << num << " ";
    tmp.emplace_back(num);
}

void SleepSort(std::vector<int>& nums)
{
    std::vector<std::thread> threads;
    for (int num : nums) {
        threads.emplace_back(SetThreadSleepTime, num);
    }
    for (auto& thread: threads) {
        thread.join();
    }
    nums = tmp;
}

} // namespace SortAlgorithm
#endif // SLEEP_SORT