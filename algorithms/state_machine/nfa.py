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
        self._adjency_dict: dict[State, list[Rule]] = defaultdict(list)
        self._state_rule: dict[State, list[Rule]] =  defaultdict(dict) #efficien lookup of rules given a state

    def add_rule(self, source, destination, matcher: str = None) -> Rule:
        rule = Rule(source, destination, matcher)
        self._adjency_dict[rule.source].append(rule)

        self._state_rule[source][(source, destination)] = rule
        self._state_rule[destination][(source, destination)] = rule

        return rule

    def _get_epsilon_closure(self, current_states: set[State]):
        """Use DFS to get the set of all reacheable states"""
        stack: list[State] = list(current_states)

        while stack:
            current_state = stack.pop()
            
            if current_state in self._adjency_dict:
                for rule in self._adjency_dict[current_state]:
                    if not rule.matcher and rule.destination not in current_states:
                        current_states.add(rule.destination)
                        stack.append(rule.destination)

        return current_states


    def union(self, nfa: "NFA", left, right):
        #remove starting nodes
        self._adjency_dict[left] = self._adjency_dict[State.START]
        old_start_list = self._adjency_dict.pop(State.START)
        self._adjency_dict.update(nfa._adjency_dict)
        self._adjency_dict[right] = self._adjency_dict[State.START]
        self._adjency_dict.pop(State.START)

        #add epsilon transitions
        self.add_rule(State.START, right)
        self.add_rule(State.START, left)

        #update state rule mapping 
        for state, rules in nfa._state_rule.items():
            if state == State.START:
                state = right

            for key, rule in rules.items():
                if key[0] == State.START:
                    rule.source = right
                    key = (right, key[1])

                elif key[1] == State.START:
                    rule.destination = right
                    key = (key[0], right)
                    
                self._state_rule[state][key] = rule
        
        for rule in old_start_list:
            rule = self._state_rule[rule.source].pop((State.START, rule.destination))
            rule = self._state_rule[rule.destination].pop((State.START, rule.destination))
            rule.source = left
            self._state_rule[left][(left, rule.destination)] = rule
            self._state_rule[rule.destination][(left, rule.destination)] = rule


    def star(self, new):
        #remove ending states and connect every ending rule back to the old start via epsilon transitions
        for key, rule in self._state_rule[State.END].items().copy():
            rule.destination = new #change the rule
            self._state_rule[State.END].pop((rule.source, State.END)) #remove the end state from the mapping 
            self._state_rule[new][rule.source, rule.destination] = rule #add the rule to the new rule mapping
            self._state_rule[rule.source].pop((rule.source, State.END)) #remove the source state from the mapping
            self._state_rule[rule.source][(rule.source, rule.destination)] = rule #add the source state to the new rule mapping
            self.add_rule(new, State.START) #connect the renamed state back to the old starting state
            new += 1

        #remove starting state and make it an ending node
        self._adjency_dict[State.END] = self._adjency_dict[State.START]
        self._adjency_dict.pop(State.START)

        #update state rule mapping
        for key, rule in self._state_rule[State.START].items():
            new_key =key
            if key[0] == State.START: 
                new_key[0] == State.END
                rule.source = State.END #change the rule

            elif key[1] == State.START:
                new_key[1] == State.END
                rule.destination = State.END #change the rule
                            
            self._state_rule[State.START].pop(key) #remove the start state from the old rule mapping 
            self._state_rule[State.END][new_key] = rule #add the rule to the old start rule mapping
        

    def match(self, input: str):
        #follow all epsilon transitions at the beginning to get all active states
        active_states = self._get_epsilon_closure({State.START})

        for char in input: #consume one character at a time

            if not active_states: #prune early
                return False

            next_states = set() #create a new set to avoid iterating and modifying the same set (which will result in undefined behaviour)

            #match all possible rules
            for state in active_states:
                if state in self._adjency_dict:
                    for rule in self._adjency_dict[state]:

                        #epsilon rules dont consume input
                        if rule.matcher is None:
                            continue

                        if rule._transition(char) != State.DEAD:
                            next_states.add(rule.destination)

            #follow again all epsilon transitions
            active_states = self._get_epsilon_closure(next_states)

        return any(state == State.END for state in active_states) #if there exists either one state which is the end state the patter match

         
if __name__ == "__main__":
    # graph = NFA()
    # graph.add_rule(State.START, State.START) #epsilon transition
    # graph.add_rule(State.START, "Q1", "1")
    # graph.add_rule("Q1", "Q2", "0")
    # graph.add_rule("Q1", "Q2", "1")
    # graph.add_rule("Q2", State.END, "1")
    # graph.add_rule("Q2", State.END, "0")
    # print(graph.match("000000100"))

    nfa1 =NFA()
    nfa1.add_rule(State.START, 1, "a")
    nfa1.add_rule(1, State.END, "a")

    nfa2 = NFA()
    nfa2.add_rule(State.START, State.END, "b")

    nfa1.union(nfa2, 2, 3)
    nfa1.star(4)




