def median(array1, array2):
    """
    This solution exploit partition bianry search. The main idea is to find the left partition of the 2 array in order to find the median.
    """

    #ensure that array1 is the smallest array to minimize the binary search time complexity
    if len(array1) > len(array2):
        array1, array2 = array2, array1

    l1 = len(array1)
    l2 = len(array2)
    ltot = l1 + l2 
    lmedian = (ltot + 1) // 2

    left = 0
    right = l1
    while True:
        #perform binary search on the smallest array (compute the size of the partition, not the index)
        p1 = (right + left) // 2 
        p2 = lmedian - p1 

        max1_left = float('-inf') if p1 == 0 else array1[p1 - 1]
        max2_left = float('-inf') if p2 == 0 else array2[p2 - 1]
        min1_right = float('inf') if p1 == l1 else array1[p1]
        min2_right = float('inf') if p2 == l2 else array2[p2]


        if max1_left > min2_right:
            right = p1 - 1
        
        elif max2_left > min1_right:
            left = p1 + 1

        else:
            if ltot & 1:
                return max(max1_left, max2_left)
            else:
                return (max(max1_left, max2_left) + min(min1_right, min2_right)) / 2.0






    

    



if __name__ == "__main__":
    array1 = [1,3]
    array2 = [2]

    array1 = [1,2,3,4,5,6,7,8]
    array2 = [1,2,3,4,5]

    array1 = [1,2]
    array2 = [3,4]

    array1 = []
    array2 = [1]
    print(median(array1, array2))