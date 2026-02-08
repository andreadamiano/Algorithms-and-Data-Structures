from typing import List


def minPatches(nums: List[int], n: int) -> int:
    miss = 1   #unmatched number 
    result = 0
    i = 0

    while miss <= n:
        if i < len(nums) and nums[i] <= miss:
            miss += nums[i]
            i += 1
        else:
            miss += miss
            result += 1

    return result


if __name__ == "__main__":
    nums = [1,3]
    n = 6
    print(minPatches(nums, n))