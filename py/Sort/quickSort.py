def _quickSortPartition(nums, low, high):
    tmp = nums[low]
    while low < high:
        while low < high and nums[high] >= tmp:
            high -= 1
        nums[low] = nums[high]
        while low < high and nums[low] <= tmp:
            low += 1
        nums[high] = nums[low]
    nums[low] = tmp
    return low

def _quickSort(nums, low, high):
    if low < high:
        div_pos = _quickSortPartition(nums, low, high)
        nums = _quickSort(nums, low, div_pos-1)
        nums = _quickSort(nums, div_pos+1, high)
    return nums

def quickSort(nums, asc):
    nums = _quickSort(nums, 0, len(nums)-1)
    if not asc:
        nums = nums[::-1]
    return nums