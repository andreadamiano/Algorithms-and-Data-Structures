import re
from enum import StrEnum


class TokenType(StrEnum):
    PLUS = "PLUS"
    MINUS = "MINUS"
    MUL = "MUL"
    DIV = "DIV"
    LPAREN = "LPAREN"
    RPAREN = "RPAREN"
    NUMBER = "NUMBER"
    IDENTIFIER = "IDENTIFIER"
    ASSIGNMENT = "ASSIGNMENT"


class Token:
    def __init__(self, value):
        if not value:
            raise ValueError("Token value cannot be empty")
        self.value = value
        self.type = self._get_type()

    def _get_type(self):
        operators = {
            "+": TokenType.PLUS,
            "-": TokenType.MINUS,
            "*": TokenType.MUL,
            "/": TokenType.DIV,
            "(": TokenType.LPAREN,
            ")": TokenType.RPAREN,
            "=": TokenType.ASSIGNMENT,
        }
        if self.value in operators:
            return operators[self.value]

        if self.value.isdigit():
            return TokenType.NUMBER

        if self.value[0].isalpha():
            return TokenType.IDENTIFIER

        raise ValueError(f"Unknown token type for {self.value}")

    def __repr__(self):
        return f"Token(value={self.value}, type={self.type})"


def tokenize(text):
    return [Token(x) for x in re.split(r"(\s+|[-+*/=()])", text) if x.strip()]



class PrattParser:
    """
    Parser implementing top-down operator precedence parsing, also known as
    Pratt parsing.
    """
    tokens: list

    def __init__(self, input_text):
        self.tokens = tokenize(input_text)
        self.prefix_parselets = {}
        self.infix_parselets = {}

    def parse(self, precedence=0):
        cur_token = self.tokens.pop(0)

        prefix_parser = self.prefix_parselets.get(cur_token.type)

        if not prefix_parser:
            raise ValueError(f"Could not parse {cur_token!r} (prefix)")

        # prefix parselets signature: (parser, token):
        left = prefix_parser(self, cur_token)

        while precedence < self.get_precedence():
            cur_token = self.tokens.pop(0)
            infix_parser = self.infix_parselets.get(cur_token.type)

            if not infix_parser:
                raise ValueError(f"Could not parse {cur_token!r} (infix)")

            # infix parselets signature: (parser, left_expr, token):
            left = infix_parser(self, left, cur_token)

        return left

    def consume(self, token_type):
        if not self.tokens:
            raise ValueError(f"Expected {token_type!r} but got nothing")
        token = self.tokens.pop(0)
        if token.type != token_type:
            raise ValueError(f"Expected {token_type!r} but got {token!r}")
        return token

    def get_precedence(self):
        if not self.tokens:
            return 0
        infix_parser = self.infix_parselets.get(self.tokens[0].type)
        return infix_parser.precedence if infix_parser else 0


# Here we define the parselets that we're going to use
# in our parser:

# Prefix Parselets:
def parse_scalar(_parser, token):
    return (token.type.value, token.value)


def build_prefix_op_parselet(precedence):
    def parse_operator(parser, token):
        right = parser.parse(precedence)
        return ('UNOP_' + token.type.value, right)
    return parse_operator


def parse_group(parser, _token):
    expr = parser.parse()
    parser.consume(TokenType.RPAREN)
    return expr


# Infix Parselets:
class BinaryOperatorParselet:
    def __init__(self, precedence):
        self.precedence = precedence

    def __call__(self, parser, left, token):
        right = parser.parse(self.precedence)
        return ('OP_' + token.type.value, left, right)


# Here is where we construct our actual parser.
# It's not a grammar, but it isn't too far from one either,
# it gives a bird's-eye view of the language.
class Parser(PrattParser):
    def __init__(self, raw_tokens):
        super().__init__(raw_tokens)
        self.prefix_parselets[TokenType.IDENTIFIER] = parse_scalar
        self.prefix_parselets[TokenType.NUMBER] = parse_scalar
        self.prefix_parselets[TokenType.MINUS] = build_prefix_op_parselet(10)
        self.prefix_parselets[TokenType.PLUS] = build_prefix_op_parselet(10)
        self.prefix_parselets[TokenType.LPAREN] = parse_group

        self.infix_parselets[TokenType.ASSIGNMENT] = BinaryOperatorParselet(1)

        self.infix_parselets[TokenType.PLUS] = BinaryOperatorParselet(5)
        self.infix_parselets[TokenType.MINUS] = BinaryOperatorParselet(5)

        self.infix_parselets[TokenType.MUL] = BinaryOperatorParselet(7)
        self.infix_parselets[TokenType.DIV] = BinaryOperatorParselet(7)


if __name__ == "__main__":
    # some test inputs
    print(Parser('1 + 2 * 3').parse())
    print(Parser('1 + 2 - 3').parse())
    print(Parser('(1 + 2) * 3').parse())
    print(Parser('+ 1 + 2').parse())
    print(Parser('+ a + 22').parse())
    print(Parser('1 - 2 - 3').parse())