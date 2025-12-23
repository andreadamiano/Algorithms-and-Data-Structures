def isMatch(s: str, p: str) -> bool:
        ls = len(s)
        lp = len(p)
        dp = [[False] * (lp+1) for _ in range(ls+1)]
        dp[0][0] = True 

        #empty string match only *
        for i in range(1, lp+1):
            if(p[i-1] == "*"):
                dp[0][i] = dp[0][i-1]

        for i in range(1, ls+1):
            for j in range(1, lp+1):
                if p[j-1] == "*":
                    dp[i][j] = dp[i-1][j] or dp[i][j-1]
                elif p[j-1] == "?" or s[i-1] == p[j-1]:
                    dp[i][j] = dp[i-1][j-1]

        #print result
        print(dp)

        
        return dp[ls][lp]

if __name__ == "__main__":
    s = "abcd"
    p = "?*"
    print(isMatch(s, p))

