from collections import defaultdict

def atoi(s: str):
    out = 0
    sign = 1
    current_state = 1
    token = ""
    states = [
        {},
        {"" : 0, "blank" : 1, "num" : 2, "sign" : 3},
        {"" : 0, "num" : 2},
        {"" : 0, "num" : 2},
    ]

    #scan every char of the provided string
    for c in s: 
        if c in "0123456789":
            token = "num"
        elif c == " ":
            token = "blank"
        elif c in "+-":
            token = "sign"
        else:
            token = ""

        #transition to next state 
        try:
            current_state = states[current_state][token]
        except Exception:
            break

        #take action based on the current state
        if current_state == 2:
            out = out * 10 + int(c)
        elif current_state == 3:
            sign = -1 if c == "-" else 1
        elif current_state == 0:
            break

    result = sign * out
    return max(-(1 << 31), min(result, (1 << 31) - 1))
    # return max(-2**31, min(result, 2**31 - 1))
        
            


if __name__ == "__main__":
    s = "42"
    s = "1337c0d3"
    s = "   -042"
    s ="0-1"
    print(atoi(s))