def insertSort(nums, asc):
    for i in range(len(nums)):
        tmp = nums[i]
        j = i - 1
        while (j>=0 and nums[j]>=tmp):
            nums[j+1] = nums[j]
            j -= 1
        nums[j+1] = tmp
    if not asc:
        nums = nums[::-1]
    return nums