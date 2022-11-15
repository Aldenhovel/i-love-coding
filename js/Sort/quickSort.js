function swap(arr, i, j) {
    var tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    return arr
}

function reverse(nums) {
    for (var i=0; i<parseInt(nums.length / 2); i++) nums = swap(nums, i, nums.length-1-i);
    return nums;
}

function quickSort(nums, asc) {
    nums = _quickSort(nums, 0, nums.length-1);
    if (!asc) nums = reverse(nums);
    return nums;
}

function _quickSort(nums, low, high) {
	// 记得要在条件 low < high 下递归，不然会栈溢出
    if (low < high) {
        var div_pos = _quickSortPartition(nums, low, high);
        nums = _quickSort(nums, low, div_pos-1);
        nums = _quickSort(nums, div_pos+1, high);
    }
    return nums;
}

function _quickSortPartition(nums, low, high) {
    var tmp = nums[low];
    while (low < high) {
        while (low < high && nums[high] >= tmp) high--;
        nums[low] = nums[high];
        while (low < high && nums[low] <= tmp) low++;
        nums[high] = nums[low];
    }
    nums[low] = tmp;
    return low;
}

var res = quickSort([2,4,1,2], true);
console.log(res);