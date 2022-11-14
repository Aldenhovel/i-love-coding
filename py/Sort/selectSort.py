def selectSort(nums, asc):
    for i in range(len(nums)):
        for j in range(i+1, len(nums)):
            if nums[i] > nums[j]:
                nums[i], nums[j] = nums[j], nums[i]
    if not asc:
        nums = nums[::-1]
    return nums