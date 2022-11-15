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

function bubbleSort(nums, asc) {
    for (var i=1; i<nums.length; i++) {
        for (var j=1; j<nums.length-i+1; j++) {
            if (nums[j] < nums[j-1]) [nums[j], nums[j-1]] = [nums[j-1], nums[j]];
        }
    }
    if (asc !== true) nums = reverse(nums);
    return nums;
}

var res = bubbleSort([2,4,1,2], false)
console.log(res)
