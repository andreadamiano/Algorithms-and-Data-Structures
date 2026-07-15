from typing import Optional
from collections import defaultdict

class State:
    START = "START"
    END = "END"
    DEAD = "DEAD"

class Rule:
    
    def __init__(self, source, destination, matcher: Optional[str] = None, pop: Optional[str] = None, push: Optional[str] = None):
        self.source = source
        self.destination = destination
        self.matcher = matcher
        self.pop = pop
        self.push = push

    def _transition(self, input, top) -> bool:
        """Transition to the next state only when the character is matched and also the top of the stack"""
        return self.destination if (not self.matcher or input == self.matcher) and (not self.pop or top == self.pop) else State.DEAD

class PDA:
    """
    In a PDA in order to transition to the next state 3 conditions must be mathced:
    1) The current state must match the rule's source
    2) The input character must match the rules's matcher
    3) The top of the stack must match the rule's pop 
    """

    def __init__(self):
        self.adjency_dict: dict[State, list[Rule]] = defaultdict(list)

    def add_rule(self, rule: Rule):
        self.adjency_dict[rule.source].append(rule)

    def _get_epsilon_closure(self, current_states: set[(State, tuple)]) -> set:
        """A state is defined by a tuple of a state name and the tuple of the stack elements, to keep track of every possible combinations of the states and stacks"""
        stack = list(current_states)

        while stack:
            current_state, current_stack = stack.pop()

            if current_state in self.adjency_dict:
                for rule in self.adjency_dict[current_state]:
                    if not rule.matcher:
                        top = current_stack[-1] if current_stack else None
                        if not rule.pop or rule.pop == top: #check if the top of the stack matches the expected pop 
                            
                            #change the stack according to the rule
                            new_stack = list(current_stack)
                            if rule.pop: new_stack.pop()
                            if rule.push: new_stack.append(rule.push)

                            new_state = (rule.destination, tuple(new_stack)) #convert the stack to a tuple to make it immutable
                            if new_state not in current_states:
                                current_states.add(new_state)
                                stack.append(new_state)

        return current_states

    def match(self, input):
        initial_stack = ()  #mark the top of the stack with a placeholder
        active_states = self._get_epsilon_closure({(State.START, initial_stack)})

        for char in input: #consume a character 
            next_states = set() #create a new set to avoid modifying the set while iterating over it  

            if not active_states:
                return False

            for current_state, current_stack in active_states:
                if current_state in self.adjency_dict:
                    for rule in self.adjency_dict[current_state]: #find a matching rule to transition to the next state
                        
                        #epsilon rules dont consume input
                        if rule.matcher is None:
                            continue

                        top = current_stack[-1] if current_stack else None
                        if rule._transition(char, top) != State.DEAD:
                            new_stack = list(current_stack)
                            if rule.pop: new_stack.pop()
                            if rule.push: new_stack.append(rule.push)
                            next_states.add((rule.destination, tuple(new_stack)))

            #follow again all epsilon transitions
            active_states = self._get_epsilon_closure(next_states)

        return any(state == State.END for state, stack in active_states) #if there exists either one state which is the end state the patter match



if __name__ == "__main__":
    graph = PDA()
    graph.add_rule(Rule(State.START, "Q1", None, None, "$")) 
    graph.add_rule(Rule("Q1", "Q1", "0", None, "0")) 
    graph.add_rule(Rule("Q1", "Q2", "1", "0", None))
    graph.add_rule(Rule("Q2", "Q2", "1", "0", None))
    graph.add_rule(Rule("Q2", State.END, None, "$", None))

    print(graph.match("000111")) 