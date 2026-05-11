from typing import Optional
from collections import defaultdict

class State:
    START = "START"
    END = "END"
    DEAD = "DEAD"

class Rule:
    
    def __init__(self, source, destination, matcher: Optional[str] = None):
        self.source = source
        self.destination = destination
        self.matcher = matcher

    def _transition(self, input) -> bool:
        return self.destination if not self.matcher or input == self.matcher else State.DEAD

class NFA:
    
    def __init__(self):
        self.adjency_dict: dict[State, list[Rule]] = defaultdict(list)

    def add_rule(self, rule: Rule):
        self.adjency_dict[rule.source].append(rule)

    def _get_epsilon_closure(self, current_states: set[State]):
        """Use DFS to get the set of all reacheable states"""
        stack: list[State] = list(current_states)

        while stack:
            current_state = stack.pop()
            
            if current_state in self.adjency_dict:
                for rule in self.adjency_dict[current_state]:
                    if not rule.matcher and rule.destination not in current_states:
                        current_states.add(rule.destination)
                        stack.append(current_state)

        return current_states
        

    def match(self, input: str):
        #follow all epsilon transitions at the beginning to get all active states
        active_states = self._get_epsilon_closure({State.START})

        for char in input: #consume one character at a time

            if not active_states:
                return False

            next_states = set() #create a new set to avoid iterating and motifying the same set (which will result in undefined behaviour)

            #match all possible rules
            for state in active_states:
                if state in self.adjency_dict:
                    for rule in self.adjency_dict[state]:
                        if rule._transition(char) != State.DEAD:
                            next_states.add(rule.destination)

            #follow again all epsilon transitions
            active_states = self._get_epsilon_closure(next_states)

        return any(state == State.END for state in active_states) #if there exists either one state which is the end state the patter match

         

if __name__ == "__main__":
    graph = NFA()
    graph.add_rule(Rule(State.START, State.START)) #epsilon transition
    graph.add_rule(Rule(State.START, "Q1", "1"))
    graph.add_rule(Rule("Q1", "Q2", "0"))
    graph.add_rule(Rule("Q1", "Q2", "1"))
    graph.add_rule(Rule("Q2", State.END, "1"))
    graph.add_rule(Rule("Q2", State.END, "0"))
    print(graph.match("000000100"))

    # while True:
    #     string = input()
    #     print(graph.match(string))


