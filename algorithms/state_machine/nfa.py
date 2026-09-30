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
    
    def __init__(self, matcher = None):
        self._adjency_dict: dict[State, list[Rule]] = defaultdict(list)
        self._ends: set[Rule] = set() #efficien lookup of end rules

        if matcher:
            self.add_rule(State.START, State.END, matcher)

    def add_rule(self, source, destination, matcher: str = None) -> Rule:
        rule = Rule(source, destination, matcher)
        self._adjency_dict[rule.source].append(rule)

        if destination == State.END:
            self._ends.add(rule)

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
        """
        Matches either the current nfa or the provided nfa
        """
        #remove starting nodes
        self._adjency_dict[State.START][0].source = left
        self._adjency_dict[left] = self._adjency_dict[State.START]
        self._adjency_dict.pop(State.START)
        
        self._adjency_dict.update(nfa._adjency_dict)
        self._adjency_dict[State.START][0].source = right
        self._adjency_dict[right] = self._adjency_dict[State.START]
        self._adjency_dict.pop(State.START)

        #add epsilon transitions
        self.add_rule(State.START, right)
        self.add_rule(State.START, left)

        #update ends 
        self._ends.update(nfa._ends)

        return right + 1


    def star(self, new):
        """
        Matches 0 or more of the current nfa
        """
        #remove ending states and connect every ending rule back to the old start via epsilon transitions
        for rule in self._ends.copy():
            rule.destination = new #change the rule
            self._ends.remove(rule)
            rule = self.add_rule(new, State.END) #connect the renamed state back to the old starting state
            new += 1

        #remove starting state and make it an ending node
        self._adjency_dict[State.START][0].source = State.END

        self._adjency_dict[State.END] = self._adjency_dict[State.START]
        self._adjency_dict.pop(State.START)

        #add new starting state
        self.add_rule(State.START, State.END)

        return new


    def concat(self, nfa: "NFA", new):
        """
        Concatenate the ending state of the current nfa with the provided nfa
        """
        #add nfa adjency dict 
        nfa_start = new
        dfa_start_rule_old = nfa._adjency_dict.pop(State.START)[0]
        self._adjency_dict.update(nfa._adjency_dict)
        nfa._adjency_dict[State.START].append(dfa_start_rule_old) #restore starting state of the other nfa

        #connect end states to the starting state of the provided nfa via epsilon transition
        new += 1
        for rule in self._ends.copy():
            rule.destination = new
            self._ends.remove(rule)
            self.add_rule(rule.destination, nfa_start) #add epsilon transition from the previous end of the current nfa with the old start of the provided nfa 

        #add back the old tart of the other nfa
        self.add_rule(nfa_start, dfa_start_rule_old.destination, dfa_start_rule_old.matcher)

        #update ends 
        self._ends.update(nfa._ends)

        return new 


    def plus(self, new):
        """
        Matches one or more of the current nfa
        """
        self.add_rule(State.END, State.START) #add a new rule connecting the start via an epsilon transition to allow more matches

    def question(self):
        """
        Matches 0 or 1 of the current nfa 
        """
        self.add_rule(State.START, State.END) #add a new rule connecting the end via an epsilon transition to allow zero matches


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

    nfa3 = NFA()
    nfa3.add_rule(State.START, 6, "a")
    nfa3.add_rule(7, State.END, "a")
    nfa3.add_rule(6, 7)

    nfa4 = NFA('e')

    # nfa1.union(nfa2, 2, 3)
    # nfa1.star(4)
    # nfa3.concat(nfa1, 8)
    new = nfa1.plus(2)
    new = nfa1.union(nfa2, new, new+1)
    nfa1.concat(nfa4, new)
    # nfa1.union(nfa4, 2, 3)
    nfa1.question()
    print(nfa1.match("bb"))


