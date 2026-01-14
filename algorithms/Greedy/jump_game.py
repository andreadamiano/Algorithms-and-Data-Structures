def jump(nums):
    n = len(nums)
    end = farthest = n_jumps = 0
    i = 0
    while end +1 < n:
        n_jumps += 1 
        while i <= end and i <= n:
            farthest = max(farthest, i + nums[i])
            i += 1
        if farthest <= end:
            return -1
        
        end = farthest
    
    return n_jumps



if __name__ == "__main__":
    # nums = [2,3,1,1,4]
    # nums = [2,3,0,1,4]
    # nums = [0]
    nums = [3,4,3,2,5,4,3]
    print(jump(nums))