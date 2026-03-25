def search(nums: list, target: int):
   
    def bin_search(nums, target, start, end):
        if end < start:
            return -1
        
        mid = (start + end) // 2

        if nums[mid] == target:
            return mid

        #one of the 2 side will always be sorted, check which one is it 
        if nums[start] <= nums[mid]: #left-side is sorted
            if nums[start] <= target <= nums[mid]:
                return bin_search(nums, target, start, mid-1)
            else:
                return bin_search(nums, target, mid+1, end) 
            
        else:
            if nums[mid] <= target <= nums[end]:
                return bin_search(nums, target, mid+1, end)
            else:
                return bin_search(nums, target, start, mid-1) 
        
    return bin_search(nums, target, 0, len(nums)-1)


if __name__ == "__main__":
    nums = [4,5,6,7,0,1,2]
    nums = [6,7,0,1,2,4,5]
    # nums = [0,1,2,4,5,6,7]
    target = 0
    print(search(nums, target))