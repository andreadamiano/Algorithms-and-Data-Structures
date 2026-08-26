import bisect

def set_intersection(intervals: list):
    result = []
    intervals.sort(key=lambda x: (x[1], -x[0])) #in order to optimize comparison between the overlapping windows sort by increasnig ends and decreasing starts
    
    for interval in intervals:
        index = bisect.bisect_left(result, interval[0]) #efficiently find the smallest index that put the value in increasing sorted order 

        if not result or index >= len(result):
            result.extend([interval[-1]-1, interval[-1]]) #greedy approach put the biggest index in the containing set

        elif index == len(result)-1:
            result.append(interval[1]) #same greedy approach

    print(result)

    return len(result)
            




if __name__ == "__main__":
    intervals = [[1,3],[1,4],[2,5],[3,5]]

    intervals = [[1,3],[3,7],[8,9]]

    # intervals = [[1,2],[2,3],[2,4],[4,5]]

    intervals = [[1,3],[4,7],[5,7],[7,8]]

    # intervals = [[4,14],[6,17],[7,14],[14,21],[4,7]]

    # intervals = [[4,14],[6,17],[7,14],[14,21],[4,7]]

    print(set_intersection(intervals))