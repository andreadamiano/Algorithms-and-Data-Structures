from enum import Enum
from nfa import NFA, State


class TokenType(Enum):
    ATOM = 'a'
    ESCAPE = '\\'
    OPEN_PAR = '('          
    CLOSE_PAR = ')'    
    START = '*'
    PLUS = '+'
    UNION = '|'

class Token:
    def __init__(self, value: str, type: TokenType):
        self.value = value
        self.type = type


class Regex:
    def __init__(self):
        self.input_pos = 0
        self.input_len = 0
        self.state_index = 0 #autoincrementing index to assign to nfastates
        self.nfa = None


    def _peek(self, input: str):
        if self.input_pos == len(input):
            return None

        i = self.input_pos
        curr_char = None
        while self.input_pos < self.input_len and (curr_char := input[i]) == " ":
            i += 1

        return curr_char


    def _get_token(self, input: str):
        if self.input_pos >= self.input_len:
            return None

        while self.input_pos < self.input_len and (curr_char := input[self.input_pos]) == " ":
            self.input_pos += 1

        match curr_char:
            case '|' | '(' | ')' | '\\' | '*' | '+':
                if curr_char == '\\':
                    self.input_pos += 1 #consume the escape token
                    curr_char = input[self.input_pos]
                    token_type = TokenType.ATOM
                
                else:
                    token_type = TokenType(curr_char)

            case _ :
                token_type = TokenType.ATOM

        return Token(curr_char, token_type)


    def match(self, pattern: str, string: str):
        nfa: NFA = self._build_nfa()
        nfa.match(string)


    def _build_nfa(self, input: str):
        """
        Parse regex expression and build the corresponding nfa.
        operator precedence from highest to lowest:
            - escape (\)
            - paranthesis 
            - kleene star (*), plus (+) 
            - concatenation (implicit operator)
            - union (|)
        """

        self._parse_union()


    def _parse_union(self, input: str):
        nfa: NFA = self._parse_concat(input)

        if  (next_char := self._peek(input)) and next_char == '|':
            self._get_token(input) #consume pipe 
            nfa_rigth = self._build_nfa(input)
            
            nfa.adjency_dict
        

    def _parse_concat(self, input: str):
        nfa: NFA = self._parse_atom(input)


    def _parse_atom(self, input: str):
        token = self._get_token(input)
        
        if not token:
            return None
        
        if token.type == TokenType.OPEN_PAR:
            self._parse_union(input)

            if self._get_token(input).type != TokenType.CLOSE_PAR:
                raise Exception("Invalid regex pattern, missing closing )")


        nfa = NFA()
        nfa.add_rule(State.START, State.END, token.value)

        return nfa

if __name__ == "__main__":
    input = r"\aa|b"
    # input = "a|b*"
    parser = 