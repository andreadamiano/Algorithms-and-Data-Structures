
def max_sliding_window(nums, k):
    result = []
    for i in range(len(nums)-k +1):
        result.append(max(nums[i:i+k]))

    return result


if __name__ == "__main__":
    nums = [1,2,1,0,4,2,6]
    k = 3
    
    print(max_sliding_window(nums, k))