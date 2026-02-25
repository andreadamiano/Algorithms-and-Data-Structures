import heapq

def smallest_range(nums):
    heap = []
    cur_max = float("-inf")
    _smallest_range = [float("-inf"), float("inf")] 
    
    #initialize heap 
    for i in range(len(nums)):
        heapq.heappush(heap, (nums[i][0], i, 0)) 
        cur_max = max(cur_max, nums[i][0])

    while heap:
        #we maintain a windows of one lement for each list , and for each compute the smallest and biggest element  
        cur_small, list_index, pos = heapq.heappop(heap)
        print(f"{(cur_small, list_index, pos)}")

        if cur_max - cur_small < _smallest_range[1] - _smallest_range[0]: 
            _smallest_range = [cur_small, cur_max] #update smallest range

        if pos+1 < len(nums[list_index]): #we advance the smallest element of the sliding window
            next_num = nums[list_index][pos+1]
            heapq.heappush(heap, (next_num, list_index, pos+1))
            cur_max = max(cur_max, next_num)

        else:
            break


    print(_smallest_range)


if __name__ == "__main__":
    nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
    print(smallest_range(nums))