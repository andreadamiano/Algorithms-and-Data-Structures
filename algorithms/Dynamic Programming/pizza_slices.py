def _pick(slices: list[int]):
    slices_len = len(slices)
    picks = (slices_len + 2) // 3
    dp = [[0] * (slices_len + 1) for _ in range(picks+1)]  #dp[i][j] represent the max pizza slice choosing i non adjacent slices from j slices

    for pick in range(1, picks+1):
        for i in range(1, slices_len+1):
            if i < 2:
                dp[pick][i] = max(dp[pick][i], dp[pick][i-1] + slices[i-1])
            else:
                dp[pick][i] = max(dp[pick][i-1], max((dp[pick-1][i-2] + slices[i-1]), dp[pick][i]))

    return dp[picks][slices_len]

def pick_slices(slices: list[int]):
    return max(_pick(slices[1:]), _pick(slices[:-1]))


if __name__ == "__main__":
    slices = [1,2,3,4,5,6]
    slices = [8,9,8,6,1,1]
    slices = [4,1,2,5,8,3,1,9,7]
    slices = [9,5,1,7,8,4,4,5,5,8,7,7]
    print(pick_slices(slices))