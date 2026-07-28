from collections import defaultdict

def dfa(input_dict: str, n_states, states_info, transitions, absorption_function, input_len):
    """
    This is a dfa with non absorbing edges, meaning that a state transition will happen when the character matches the rule, but the character itself won't be consumed
    The problem require to compure how many input of input_len can be accepted by the DFA
    In this solution, DP and FSM are paired together:
        - FSM defines the topology and the state transition rules
        - DP accumulate the best solution travelling across the graph
    Every DP problem must satisfy the Markov Property (memoryless state rule):
        - The future state depends ONLY on the current state, NOT on the exact path taken to reach it.
        - FSMs are naturally Markovian: a state (e.g., State u at step i) encapsulates all relevant past history.
        - Because of this, DP can efficiently count or optimize over the FSM graph without needing to re-evaluate exponential path combinations.
    """
    def follow_edge(start_state, ch):
        visited = set()
        current_state = start_state

        while True:
            if current_state in visited:
                return None

            visited.add(current_state)
            next_state, absorption =  adjency_list[current_state][ch]

            if absorption == 0: 
                return next_state

            current_state =  next_state



    initial_state = int(states_info[0])
    terminal_states = set([int(state) for state in states_info[2:int(states_info[1]) + 2]])

    #build adjency list
    adjency_list = defaultdict(lambda : defaultdict())
    for i in range(1, n_states+1):
        for j in range(len(input_dict)):
            ch = input_dict[j]
            adjency_list[i][ch] = (int(transitions[i-1][j]), int(absorption_function[i-1][j]))

    print(adjency_list)

    #perform edge compression (compress non absorbing edges, by following them until they reach an absorbing edge)
    compressed_adj_list = defaultdict(lambda : defaultdict())
    for i in range(1, n_states+1):
        for ch in input_dict:
            compressed_adj_list[i][ch] = follow_edge(i, ch)


    #perform dp to compute the number of strings of lenght input_len that the DFA accept
    dp = [{state: 0 for state in range(1, n_states + 1)} for _ in range(input_len + 1)]  #dp[input_len][state] represent the number of valid string of len input_len ending at state
    dp[0][initial_state] = 1 #initiazile dp (there is one valid string of lenght 0 at the initial state)

    for lenght in range(1, input_len+1): #consume a token 
        for prev_state in range(1, n_states+1): #test for every previous state

            if dp[lenght-1][prev_state]: #check if the previous state is reacheable

                for ch in input_dict: #make an ipothesis on the consumed token
                    next_state = compressed_adj_list[prev_state][ch] #find the reachable state 
                    if next_state:
                        dp[lenght][next_state] += dp[lenght - 1][prev_state] #all strings that have reached the previous state can now rech the next state consuming ch

    return sum(dp[input_len][state] for state in terminal_states)


if __name__ == "__main__":
    input_dict = "ab"
    n_states = 2
    states_info = "112"
    transitions = ["21", "12"]
    absorption_function = ["01", "00"]
    input_len = 3
    print(dfa(input_dict, n_states, states_info, transitions, absorption_function, input_len))

