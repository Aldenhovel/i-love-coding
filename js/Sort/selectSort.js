function swap(arr, i, j) {
    var tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    return arr;
}

function reverse(nums) {
    for (var i=0; i<parseInt(nums.length / 2); i++) nums = swap(nums, i, nums.length-1-i);
    return nums;
}

function selectSort(nums, asc) {
    for (var i=0; i<nums.length; i++) {
        for (var j=i+1; j<nums.length; j++) {
            if (nums[i] > nums[j]) nums = swap(nums, i, j);
        }
    }
    if (!asc) nums = reverse(nums);
    return nums;
}

var res = selectSort([2,4,1,2], false);
console.log(res);