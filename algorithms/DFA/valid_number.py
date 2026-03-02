class Number:
    sign = 0
    num = 1
    dot = 2 
    exponent = 3

def valid_number(s: str):
    #define finite state machine 
    state = [
        {}, #dead state (trap state, once entered cannot leave it )
        {'blank': 1, 'sign': 2, 'digit':3, '.':4}, #initial state (blank node)
        {'digit':3, '.':4}, # After sign
        {'digit':3, '.':5, 'e':6, 'blank':9}, # After digits (integer part)
        {'digit':5}, # After dot with no digits yet
        {'digit':5, 'e':6, 'blank':9}, # After dot with digits
        {'sign':7, 'digit':8}, # After 'e'
        {'digit':8},  # After exponent sign
        {'digit':8, 'blank':9}, # After exponent digits
        {'blank':9}]  # Trailing blanks (accepting)
    
    current_state = 1

    for c in s:
        if c >= '0' and c <= '9':
            c = 'digit'
        if c == ' ':
            c = 'blank'
        if c in ['+', '-']:
            c = 'sign'
        if c not in state[current_state].keys():
            return False
        
        #update state
        current_state = state[current_state][c]

    if current_state not in [3,5,8,9]:
          return False
    return True


if __name__ == "__main__":
    s = "+3.14"
    s = "-90E3"
    s = ".1"
    print(valid_number(s))