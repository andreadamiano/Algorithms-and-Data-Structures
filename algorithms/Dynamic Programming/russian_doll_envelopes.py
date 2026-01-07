
# def max_envelopes(envelopes: list):
#     memo = {}

#     def dp(selected_envelope = None):

#         if selected_envelope in memo:
#             return memo[selected_envelope]
        
#         max_envelopes = 0
#         for envelop in envelopes:
        
#             if envelop == selected_envelope:
#                 continue

#             if not selected_envelope or selected_envelope[0] > envelop[0] and selected_envelope[1] > envelop[1]:
#                 max_envelopes = max(max_envelopes, 1 + dp(tuple(envelop)))
        
#         if selected_envelope:
#             memo[tuple(selected_envelope)] = max_envelopes 
#         return max_envelopes


#     return dp()


def max_envelopes(envelopes: list):
    #sort width in increasing order 
    #sort height in decreasing order 
    envelopes.sort(key=lambda x: (x[0], -x[1])) 
    print(envelopes)
    
    import bisect
    dp = []
    for _, h in envelopes:
        idx = bisect.bisect_left(dp, h)
        if idx == len(dp):
            dp.append(h)
        else:
            dp[idx] = h
    
    return len(dp)
                

if __name__ == "__main__":
    envelopes = [[2,4],[6,4],[6,7],[2,3]]
    print(max_envelopes(envelopes))