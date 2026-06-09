from collections import defaultdict

# def freedom_trail(ring: str, key: str):
#     key_index = defaultdict(list)
#     for i, ch in enumerate(ring):
#         key_index[ch].append(i)
#     ring_len = len(ring)
#     key_len = len(key)
#     cache = {}

#     def dp(ring_position, key_position):
#         if (ring_position, key_position) in cache:
#             return cache[(ring_position, key_position)]
    
#         if key_position == key_len:
#             return 0

#         distance = float("inf")
#         for position in  key_index[key[key_position]]:
#             #compute the distance between the current position in the ring and the next position to reach
#             tmp = 1 + min((ring_position - position + ring_len) % ring_len, (position - ring_position + ring_len) % ring_len) #compare ruotating to the left or to the right
#             tmp += dp(position, key_position + 1)
#             distance = min(distance, tmp)

#         cache[(ring_position, key_position)] = distance
#         return distance
        
#     return dp(0, 0)


# def freedom_trail(ring: str, key: str):
#     "Bottom up appraoch"
#     ring_len = len(ring)
#     key_len = len(key)
#     dp = [ [float("inf")] * ring_len for _ in range(key_len+1)] #dp[i][j] store the minimum number of operations to have spelled key i-1 ending up at position j on the ring 
#     dp[0][0] = 0
    
#     #map every key to the index where it appears on the ring
#     key_index = defaultdict(list)
#     for i, ch in enumerate(ring):
#         key_index[ch].append(i)

#     for key_position in range(1, key_len+1):
#         for next_ring_position in key_index[key[key_position-1]]: #explore how to reach every next char of the key
            
#             for prev_ring_position in range(ring_len): #suppose we were previously in this position

#                 if dp[key_position-1][prev_ring_position] == float("inf"): #unreachable state
#                     continue

#                 distance = min((prev_ring_position - next_ring_position + ring_len) % ring_len, (next_ring_position - prev_ring_position + ring_len) % ring_len)
#                 dp[key_position][next_ring_position] = min(dp[key_position][next_ring_position], distance + dp[key_position-1][prev_ring_position] + 1)

#     return dp


def freedom_trail(ring: str, key: str):
    "Bottom up approach"
    ring_len = len(ring)
    key_len = len(key)
    dp = [ [float("inf")] * ring_len for _ in range(key_len+1)] #dp[i][j] store the minimum number of operations to spell key[i:] starting from position j on the ring 
    dp[key_len] = [0] * ring_len #base case

    #map every key to the index where it appears on the ring
    key_index = defaultdict(list)
    for i, ch in enumerate(ring):
        key_index[ch].append(i)

    for key_position in range(key_len-1, -1, -1):
        for ring_position in range(ring_len): #suppose we are currently at this position on the ring

            for position in key_index[key[key_position]]: #explore every possible next position
                distance = min((ring_position - position + ring_len) % ring_len, (position - ring_position + ring_len) % ring_len)
                dp[key_position][ring_position] = min(dp[key_position+1][position] + distance + 1, dp[key_position][ring_position])

    return dp




if __name__ == "__main__":
    ring = "goddling"
    ring = "godding"
    key = "gd"
    key = "godding"
    print(freedom_trail(ring, key))