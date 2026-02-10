def three_sum(nums: list):
    res = []
    nums.sort() 

    for i in range(len(nums)):
    #fix one of the 3 pointers 

        #skips duplicates 
        if i > 0 and nums[i] == nums[i-1]:
            continue

        j = i +1
        k = len(nums) - 1

        while j < k:
            total = nums[i] + nums[j] + nums[k]

            if total > 0:
                k = k -1

            elif total < 0:
                j = j+1

            else:
                res.append([nums[i], nums[j], nums[k]])
                j = j +1

                #avoid duplicates 
                while nums[j] == nums[j-1] and j < k:
                    j += 1

    return res




if __name__ == "__main__":
    nums = [-1,0,1,2,-1,-4]
    nums = [1,2,0,1,0,0,0,0]
    print(three_sum(nums))