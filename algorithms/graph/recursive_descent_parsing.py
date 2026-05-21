import re

class Parser:
    def __init__(self, json_str):
        self.cursor = 0
        self.tokens = self._tokenize(json_str)

    def consume(self) -> str:
        if self.cursor >= len(self.tokens):
            raise Exception("Cannot consume no more tokens")
        
        token = self.tokens[self.cursor]
        self.cursor += 1
        return token

    def _tokenize(self, json_str):
        return [token for token in re.split(r"(\s+|[-+*/=(),])" , json_str) if token.strip()]

    def peek(self):
        return self.tokens[self.cursor]
    
    def _parse_dict(self) -> dict:
        result = dict()
        self.consume()
        
        while self.peek() != "}":
            key = self._parse_alphanumeric()
            next = self.consume()

            if next != ":":
                raise Exception("Invalid json format")

            next = self.peek()
            result[key] = self._parse_value(next)

            while self.peek() == ",":
                self.consume()

        self.consume()
        return result
    
    def _parse_value(self, value):
        if value == "{":
            return self._parse_dict()
        elif value == "[":
            return self._parse_list()
        else:
            return self._parse_alphanumeric()


    def _parse_list(self) -> list:
        pass

    def _parse_alphanumeric(self) -> str:
        current = self.consume()
        if current.isdigit():
            try:
                return int(current)
            except Exception:
                return float(current)
        else:
            return str(current)
        
    def parse(self)-> dict | list | None:
        token = self.peek() #peek to decide which rule to follow 

        if token == "{":
            return self._parse_dict()

        elif token == "[":
            return self._parse_list()
        else:
            raise Exception("Invalid json format")

