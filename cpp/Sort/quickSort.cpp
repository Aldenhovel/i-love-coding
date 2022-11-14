#include "Sort.h"

int Sort::quickSort(vector<int> &nums, bool asc) {
	Sort::_quickSort(nums, 0, nums.size() - 1);
	if (!asc) Sort::reverse(nums);
	return 0;
}

int Sort::_quickSort(vector<int> &nums, int low, int high) {
	if (low < high) {
		int div_pos = Sort::_quickSortPartition(nums, low, high);
		Sort::_quickSort(nums, low, div_pos - 1);
		Sort::_quickSort(nums, div_pos + 1, high);
	}
	return 0;
}

int Sort::_quickSortPartition(vector<int> &nums, int low, int high) {
	int tmp = nums[low];
	while (low < high) {
		while (low < high && nums[high] >= tmp) high--;
		nums[low] = nums[high];
		while (low < high && nums[low] <= tmp) low++;
		nums[high] = nums[low];
	}
	nums[low] = tmp;
	return low;
}
