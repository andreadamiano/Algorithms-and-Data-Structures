def remove_overlapping_interval(intervals: list):
    n = len(intervals)
    result = 0
    if n < 2:
        return result
    
    intervals.sort(key=lambda x: ( x[1]))  #prioritize intervals that ends as early as possible
    print(intervals)
    current_index = 1
    prev_index = 0

    while current_index < n:
        if intervals[prev_index][1] > intervals[current_index][0]:
            result += 1

        else:
            prev_index = current_index

        current_index += 1

    return result


def remove_overlapping_interval_dp(intervals: list):
    n = len(intervals)
    if n < 2:
        return 0
    
    intervals.sort(key=lambda x: x[0]) #sort by START time for DP
    print(intervals)
    dp = [1] * n #dp[i] stores the max non-overlapping intervals ending at index i

    for i in range(1, n):
        for j in range(i):
            # If interval j ends before or at the time interval i starts
            if intervals[j][1] <= intervals[i][0]:
                dp[i] = max(dp[i], dp[j] + 1)
    
    print(dp)
    max_keepable = max(dp)
    return n - max_keepable


if __name__ == "__main__":
    intervals = [[1,2],[2,3],[3,4],[1,3]]
    intervals = [[-52,31],[-73,-26],[82,97],[-65,-11],[-62,-49],[95,99],[58,95],[-31,49],[66,98],[-63,2],[30,47],[-40,-26]]
    # print(remove_overlapping_interval(intervals))
    print(remove_overlapping_interval_dp(intervals))