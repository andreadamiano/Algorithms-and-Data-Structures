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
    QUESTION = '?'


class Token:
    def __init__(self, value: str, type: TokenType):
        self.value = value
        self.type = type


class RuleType(Enum):
    UNION="UNION"
    QUESTION="QUESTION"
    PLUS="PLUS"
    STAR="STAR"
    CONCAT="CONCAT"

#define the nodes of the AST

class UnionRUle:
    def __init__(self, left, rigth = None): 
        self.rule_type = RuleType.UNION
        self.left = left 
        self.rigth = rigth

    def __repr__(self):
        return f"UnionRUle(left={self.left!r}, right={self.rigth!r})"


class QuestionRule:
    def __init__(self, rule): 
        self.rule_type = RuleType.QUESTION
        self.rule = rule 

    def __repr__(self):
        return f"QuestionRule(rule={self.rule!r})"


class PlusRule:
    def __init__(self, rule): 
        self.rule_type = RuleType.PLUS
        self.rule = rule 

    def __repr__(self):
        return f"PlusRule(rule={self.rule!r})"


class StarRule:
    def __init__(self, rule): 
        self.rule_type = RuleType.STAR
        self.rule = rule 

    def __repr__(self):
        return f"StarRule(rule={self.rule!r})"


class ConcatRUle:
    def __init__(self, left, rigth = None): 
        self.rule_type = RuleType.CONCAT
        self.left = left 
        self.rigth = rigth

    def __repr__(self):
        return f"ConcatRUle(left={self.left!r}, right={self.rigth!r})"


class Regex:
    """
    Parses regex expressions and converts them into nfa.
    """
    
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


    def parse_regex(self, input: str):
        """
        Parse regex expression and build the corresponding AST.
        Operator precedence from highest to lowest:
            - escape (\)
            - paranthesis ()
            - kleene star (*), plus (+), question mark (?)
            - concatenation (implicit operator)
            - union (|)
        The idea is to descent the hierarchy from the lowest precedence operators and bubble up as we finished parsing higher level operators
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

    
    def _build_nfa(self, parsed_regex_expression):
        pass 


    def match(self, pattern: str, string: str):
        parsed_regex = self.parse_regex(pattern)
        nfa: NFA = self._build_nfa(parsed_regex)
        nfa.match(string)

if __name__ == "__main__":
    pattern = r"\aa|b"
    text = "aa"
    # input = "a|b*"
    re = Regex()
    re.match(pattern, text)