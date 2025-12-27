def prep(nums, k):
    """Get best subsequence"""
    drop = len(nums) - k
    out = []  #monotonic increasing stack 
    for num in nums:
        while drop and out and out[-1] < num:
            out.pop()
            drop -= 1
        out.append(num)
    return out[:k]

def merge(a, b):
    out = []
    i = j = 0

    while i < len(a) and j < len(b):
        if a[i:] > b[j:]:  # compare subarrays lexicographically 
            out.append(a[i])
            i += 1
        else:
            out.append(b[j])
            j+=1

    out.extend(a[i:])
    out.extend(b[j:])
    return out


def max_number(nums1, nums2, k):
    print([merge(prep(nums1, i), prep(nums2, k-i))
           for i in range(k+1)
           if i <= len(nums1) and k-i <= len(nums2)])
    

    return max(merge(prep(nums1, i), prep(nums2, k-i))
           for i in range(k+1)
           if i <= len(nums1) and k-i <= len(nums2))



if __name__ == "__main__":
    nums1 = [3,4,6,5]
    nums2 = [9,1,2,5,8,3]
    k = 5

    # out = prep(nums1, 2)
    # print(out)

    result = max_number(nums1, nums2, k)
    print(result)
