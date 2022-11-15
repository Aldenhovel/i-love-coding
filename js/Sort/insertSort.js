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

function insertSort(nums, asc) {
    for (var i=1; i<nums.length; i++) {
        var tmp = nums[i];
        for (var j=i-1; j>=0 && nums[j] > tmp; j--) {
            nums = swap(nums, j, j+1);
        }
        nums[j+1] = tmp;
    }
    if (!asc) nums = reverse(nums);
    return nums;
}

var res = insertSort([2,4,1,2], false);
console.log(res);