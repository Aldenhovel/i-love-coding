#include "Sort.h"

int Sort::bubbleSort(vector<int> &nums, bool asc) {
	for (int i = 1; i < nums.size(); i++) {
		for (int j = 1; j < nums.size() + 1 - i; j++) {
			if (nums[j] < nums[j - 1]) swap(&nums[j], &nums[j - 1]);
		}
	}
	if (!asc) Sort::reverse(nums);
	return 0;
}