def bubbleSort(nums, asc):
    for i in range(1, len(nums)):
        if nums[i-1] > nums[i]:
            nums[i-1], nums[i] = nums[i], nums[i-1]
    if not asc:
        nums = nums[::-1]
    return nums