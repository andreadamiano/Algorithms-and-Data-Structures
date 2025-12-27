
def max_envelopes(envelopes: list):
    memo = {}
    n = len(envelopes)

    def dp(selected_envelope = None):

        if selected_envelope in memo:
            return memo[selected_envelope]
        
        smaller_envelops = 0
        for envelop in envelopes:
        
            if envelop == selected_envelope:
                continue

            if not selected_envelope or selected_envelope[0] > envelop[0] and selected_envelope[1] > envelop[1]:
                smaller_envelops = 1 + max(smaller_envelops, dp(tuple(envelop)))
        
        if selected_envelope:
            memo[tuple(selected_envelope)] = smaller_envelops 
        return smaller_envelops


    return dp()
                

if __name__ == "__main__":
    envelopes = [[5,4],[6,4],[6,7],[2,3]]
    print(max_envelopes(envelopes))