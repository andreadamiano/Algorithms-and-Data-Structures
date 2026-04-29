import re

class Parser:
    def __init__(self, json_str):
        self.cursor = -1
        self.json_str = json_str
        self.tokens = self._tokenize()

    def consume(self) -> str:
        self.cursor += 1
        if self.cursor >= len(self.tokens):
            raise Exception("Cannot consume no more tokens")
        return self.tokens[self.cursor]

    def _tokenize(self):
        return [token for token in re.split(r"(\s+|[-+*/=(),])" , json_str) if token.strip()]

    def peek(self):
        return self.tokens[self.cursor+1]
    
    def _parse_dict(self) -> dict:
        result = dict()
        self.consume()
        
        while self.peek() != "}":
            key = self._parse_alphanumeric()
            next = self.consume()

            if next != ":":
                raise Exception("Invalid json format")

            next = self.peek()

            #TODO centralize parsing logic , make a multiplexer function
            if next == "{":
                value =self._parse_dict()
            elif next == "[":
                value = self._parse_list()
            else:
                value = self._parse_alphanumeric()

            result[key] = value

            while self.peek() == ",":
                self.consume()

        self.consume()
        return result


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
        token = self.peek()

        if token == "{":
            return self._parse_dict()

        elif token == "[":
            return self._parse_list()
        else:
            raise Exception("Invalid json format")





if __name__  == "__main__":
    json_str = """
    {
        'key1' : 'Andrea', 
        'key2' : {
            'key1' : 1,
            'key2' : 2,
        }
        'key3' : 'Janelle',
    }
    """
    parser = Parser(json_str)
    result = parser.parse()

    print(result)

