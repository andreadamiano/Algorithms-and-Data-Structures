# def lis(array):
#     n = len(array)
#     dp = [1 for _ in range(n)]

#     for i in range (1, n):
#         for j in range(i):
#             if (array[i] > array[j]):
#                 dp[i] = max(dp[i], dp[j] +1)  # check if the ith element can extend the subsequence ending at j 

#     return dp[-1]


def lis_array(dp, array):
    lp = len(dp)
    la = len(array)
    dp_index = 0
    array_index = 0

    while (dp_index < lp-1 and array_index <la):
        if array[array_index] < dp[dp_index+1] and array[array_index] >= dp[dp_index]:
            dp[dp_index] = array[array_index]
            dp_index += 1
        array_index += 1
        

    return dp


import bisect
def lis(array):
    """binary search lis"""
    dp = []
    for num in array:
        index = bisect.bisect_left(dp, num)  
        if index == len(dp):
            dp.append(num)   # we can safely extend the lis 

        else:
            dp[index] = num  #replace to give the possibility to extend 
        print(dp)

    # return len(dp)
    return lis_array(dp, array)   #dp is maintaining the smallest possible end elements for increasing subsequences of various lengths

if __name__ == "__main__":
    array = [10, 22, 9, 33, 21, 50, 41, 60, 80]
    # array = [10, 22, 7, 8, 11]
    print(lis(array))