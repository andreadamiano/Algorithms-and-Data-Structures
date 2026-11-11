import heapq

def smallest_range(nums):
    heap = []
    cur_max = float("-inf")
    smallest_range = [float("-inf"), float("inf")] #infinite range
    
    #initialize min heap by storing the min value from each list 
    for i in range(len(nums)):
        heapq.heappush(heap, (nums[i][0], i, 0)) 
        cur_max = max(cur_max, nums[i][0])

    while heap:
        #pop the current smallest element of all lists in order to attempt to update the smallest range
        cur_min, list_index, pos = heapq.heappop(heap)

        if cur_max - cur_min < smallest_range[1] - smallest_range[0]: 
            smallest_range = [cur_min, cur_max] #update smallest range

        if pos+1 < len(nums[list_index]): #advance the smallest element of the sliding window
            next_num = nums[list_index][pos+1]
            heapq.heappush(heap, (next_num, list_index, pos+1)) #push the next bigger item of the current list
            cur_max = max(cur_max, next_num) #update the current max

        else:
            break


    # print(smallest_range)
    return smallest_range


if __name__ == "__main__":
    nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
    print(smallest_range(nums))