from enum import Enum
from nfa import NFA, State


class TokenType(Enum):
    ATOM = 'a'
    ESCAPE = '\\'
    OPEN_PAR = '('          
    CLOSE_PAR = ')'    
    STAR = '*'
    PLUS = '+'
    UNION = '|'
    QUESTION = '?'


class Token:
    def __init__(self, value: str, type: TokenType):
        self.value = value
        self.type = type

    def __repr__(self):
        return f"Token(value={self.value!r}, type={self.type!r})"


class RuleType(Enum):
    UNION="UNION"
    QUESTION="QUESTION"
    PLUS="PLUS"
    STAR="STAR"
    CONCAT="CONCAT"

#define the nodes of the AST

class UnionRUle:
    def __init__(self, left, rigth = None): 
        self.type = RuleType.UNION
        self.left = left 
        self.rigth = rigth

    def __repr__(self):
        return f"UnionRUle(left={self.left!r}, right={self.rigth!r})"


class QuestionRule:
    def __init__(self, rule): 
        self.type = RuleType.QUESTION
        self.rule = rule 

    def __repr__(self):
        return f"QuestionRule(rule={self.rule!r})"


class PlusRule:
    def __init__(self, rule): 
        self.type = RuleType.PLUS
        self.rule = rule 

    def __repr__(self):
        return f"PlusRule(rule={self.rule!r})"


class StarRule:
    def __init__(self, rule): 
        self.type = RuleType.STAR
        self.rule = rule 

    def __repr__(self):
        return f"StarRule(rule={self.rule!r})"


class ConcatRUle:
    def __init__(self, left, rigth = None): 
        self.type = RuleType.CONCAT
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
        self._state_index = 0 #auto incrementing index to assign to nfa states
        self.nfa: NFA = None


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
            case '|' | '(' | ')' | '*' | '+':
                token_type = TokenType(curr_char)

            case '\\':
                self.input_pos += 1 #consume the escape token
                curr_char = input[self.input_pos]
                token_type = TokenType.ATOM

            case _ :
                token_type = TokenType.ATOM

        self.input_pos += 1 
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

        rule = self._parse_union(input)
        return rule


    def _parse_union(self, input: str):
        left = self._parse_quantifier(input)

        while  (next_char := self._peek(input)) and next_char == '|':
            self._get_token(input)
            rigth = self._parse_concat(input)  
            left = UnionRUle(left, rigth)
            
        return left


    def _parse_quantifier(self, input: str):
        left = self._parse_concat(input)

        while (next_char := self._peek(input)) and next_char in "?*+":
            token = self._get_token(input)

            match(token.type):
                case TokenType.PLUS:
                    left = PlusRule(left) 

                case TokenType.STAR:
                    left = StarRule(left)

                case TokenType.QUESTION:
                    left = QuestionRule(left)

            if (next_char := self._peek(input)) and next_char not in ")|?*+":
                rigth = self._parse_concat(input)
                left = ConcatRUle(left, rigth)

        return left


    def _parse_concat(self, input: str):
        left  = self._get_token(input)

        if left.type == TokenType.OPEN_PAR:
            left = self._parse_union(input)

            if self._get_token(input).type != TokenType.CLOSE_PAR:
                raise Exception("Invalid regex pattern, missing closing )")

        while (next_char := self._peek(input)) and next_char not in ")|?*+":

            if next_char == '(':
                self._get_token(input)
                right = self._parse_union(input)
                left = ConcatRUle(left, right)

                if self._get_token(input).type != TokenType.CLOSE_PAR:
                    raise Exception("Invalid regex pattern, missing closing )")
            else:
                rigth = self._get_token(input)
                left = ConcatRUle(left, rigth)

        return left


    def _build_nfa(self, parsed_regex_expression):

        match(parsed_regex_expression.type):

            case RuleType.UNION:
                nfa = self._build_nfa(parsed_regex_expression.left)
                self._state_index = nfa.union(self._build_nfa(parsed_regex_expression.rigth), self._state_index)
                return nfa

            case RuleType.CONCAT:
                nfa = self._build_nfa(parsed_regex_expression.left)
                self._state_index = nfa.concat(self._build_nfa(parsed_regex_expression.rigth), self._state_index)
                return nfa

            case RuleType.QUESTION:
                nfa: NFA = self._build_nfa(parsed_regex_expression.rule)
                nfa.question()
                return nfa

            case RuleType.PLUS:
                nfa: NFA = self._build_nfa(parsed_regex_expression.rule)
                nfa.plus()
                return nfa

            case RuleType.STAR:
                nfa: NFA = self._build_nfa(parsed_regex_expression.rule)
                self._state_index =  nfa.star(self._state_index)
                return nfa

            case _:
                return NFA(parsed_regex_expression.value)


    def match(self, pattern: str, string: str):
        if not self.nfa:
            self.input_len = len(pattern)
            parsed_regex = self.parse_regex(pattern)
            print(parsed_regex)

            if self.parse_regex:
                self.nfa = self._build_nfa(parsed_regex)
                return self.nfa.match(string)

            else:
                raise Exception("provided invalid regex expression")

        else:
            self.nfa.match(string)

if __name__ == "__main__":
    pattern = r"\aa(a|b)"
    # pattern = r"(\aa)+a|b"
    # pattern = r"((\aa)+a)*|b"
    text = "aaa"
    # input = "a|b*"
    re = Regex()
    print(re.match(pattern, text))