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

def count_smaller_merge(nums):
    def merge_sort(enum):
        half = len(enum) // 2
        if half:
            left, right = merge_sort(enum[:half]), merge_sort(enum[half:])
            for i in range(len(enum)-1, -1, -1):
                if not right or left and left[-1][1] > right[-1][1]:
                    smaller[left[-1][0]] += len(right)
                    enum[i] = left.pop()
                else:
                    enum[i] = right.pop()
        return enum
    
    smaller = [0] * len(nums)
    merge_sort(list(enumerate(nums)))
    return smaller


if __name__ == "__main__":
    nums = [5,2,6,1]
    print(count_smaller(nums))
    print(count_smaller_merge(nums))