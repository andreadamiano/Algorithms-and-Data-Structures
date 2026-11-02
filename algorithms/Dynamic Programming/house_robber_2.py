def _rob(houses: list[int]) -> int:
    prev_rob, prev_prev_rob = 0, 0

    for house in houses:
        if house + prev_prev_rob > prev_rob: #choose to not rob the previous house
            prev_prev_rob, prev_rob = prev_rob, prev_prev_rob + house
        
        else:  #choose not to rob the current house
            prev_prev_rob=  prev_rob 
    
    return prev_rob

def rob(houses: list[int]):
    if len(houses) == 1:
        return houses[0]

    return max(_rob(houses[:-1]), _rob(houses[1:]))


if __name__ == "__main__":
    houses = [2,3,2]
    houses = [1]
    print(rob(houses))