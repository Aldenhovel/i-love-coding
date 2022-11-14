#include "Sort.h"

int Sort::selectSort(vector<int> &nums, bool asc) {
	for (int i = 0; i < nums.size()-1; i++) {
		for (int j = i + 1; j < nums.size(); j++) {
			if (nums[j] < nums[i]) Sort::swap(&nums[i], &nums[j]);
		}
	}
	if (!asc) Sort::reverse(nums);
	return 0;
}