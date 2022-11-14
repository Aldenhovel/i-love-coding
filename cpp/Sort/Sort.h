#pragma once
#include <vector>

using namespace std;

namespace Sort {

	template<typename T>
	int swap(T *a, T *b);

	template<typename T> 
	int swap(T *a, T *b);

	template<typename T>
	int reverse(vector<T> &nums);

	int bubbleSort(vector<int> &nums, bool asc);

	int insertSort(vector<int> &nums, bool asc);
	
	int quickSort(vector<int> &nums, bool asc);
	int _quickSort(vector<int> &subnums, int low, int high);
	int _quickSortPartition(vector<int> &subnums, int low, int high);

	int selectSort(vector<int> &nums, bool asc);

}

template<typename T>
int Sort::swap(T *a, T*b) {
	T tmp = *a;
	*a = *b;
	*b = tmp;
	return 0;
}

template<typename T>
int Sort::reverse(vector<T> &nums) {
	for (int i = 0; i < nums.size() / 2; i++) swap(&nums[i], &nums[nums.size() - 1 - i]);
	return 0;
}