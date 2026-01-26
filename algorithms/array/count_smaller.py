import bisect
from sortedcontainers import SortedList

def count_smaller(nums):
    sorted_list = SortedList()
    result = []
    for num in reversed(nums):
        idx = bisect.bisect_left(sorted_list, num)
        result.append(idx)
        sorted_list.add(num)

    return result[::-1] 


if __name__ == "__main__":
    nums = [5,2,6,1]
    print(count_smaller(nums))