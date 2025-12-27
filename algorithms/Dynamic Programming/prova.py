def max_envelopes(envelopes: list):
    memo = {}
    n = len(envelopes)
    
    # Convert envelopes to tuples for memoization
    envelope_tuples = [tuple(env) for env in envelopes]
    
    def dp(selected_envelope=None):
        if selected_envelope in memo:
            return memo[selected_envelope]
        
        max_chain = 0
        
        for envelope in envelope_tuples:
            if envelope == selected_envelope:
                continue
                
            if not selected_envelope or (selected_envelope[0] > envelope[0] and selected_envelope[1] > envelope[1]):
                chain_length = 1 + dp(envelope)
                max_chain = max(max_chain, chain_length)
        
        memo[selected_envelope] = max_chain
        return max_chain
    
    return dp()


if __name__ == "__main__":
    envelopes = [[5,4],[6,4],[6,7],[2,3]]
    print(max_envelopes(envelopes))  # Output: 3