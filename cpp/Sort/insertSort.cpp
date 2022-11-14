#include "Sort.h"

int Sort::insertSort(vector<int> &nums, bool asc) {
	for (int i = 0; i < nums.size(); i++) {
		int tmp = nums[i];
		int j = i - 1;
		for (; j >= 0 && tmp < nums[j]; j--) nums[j + 1] = nums[j];
		nums[j + 1] = tmp;
	}
	if (!asc) Sort::reverse(nums);
	return 0;
}