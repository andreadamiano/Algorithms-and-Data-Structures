def min_taps(n, ranges):
    # areas = []
    # remaining_area = {i for i in range(n+1)}
    # result = 0
    # for index, _range in enumerate(ranges):
    #     areas.append((max(index - _range, 0), min(index + _range, n)))
    
    # areas.sort(key= lambda x: x[0] - x[1])
    # print(areas)


    # for area in areas:
    #     if not remaining_area:
    #         return result
        
    #     if area[0] >= min(remaining_area):
    #         result += 1
    #         for i in range(area[0], area[1]+1):
    #             if i in remaining_area:
    #                 remaining_area.remove(i)
    
    # return -1

    coverage = [0] * (n + 1)
    
    for i, r in enumerate(ranges):
        if r:
            left = max(0, i - r)
            coverage[left] = max(coverage[left], min(n, i + r))

    print(coverage)


    taps = end = farthest = 0
    i = 0
    # the idea is that you can jump only startig from prev position you have already reached 
    while end < n:
        taps += 1
        # Explore all positions within current reach
        while i <= end and i <= n:
            farthest = max(farthest, coverage[i])
            i += 1
        
        if farthest <= end:  # Can't progress
            return -1
        
        end = farthest
    
    return taps


if __name__ == "__main__":
    # n = 5
    # ranges = [3,4,1,1,0,0]
    ranges = [1,2,1,0,2,1,0,1]
    n = 7
    # ranges = [0,5,0,3,3,3,1,4,0,4]
    # n= 9
    print(min_taps(n, ranges))