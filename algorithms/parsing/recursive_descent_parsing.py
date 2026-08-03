import re

class Parser:
    def __init__(self):
        self.cursor = 0
        self.tokens = None

    def consume(self) -> str:
        if self.cursor >= len(self.tokens):
            raise Exception("Cannot consume no more tokens")
        
        token = self.tokens[self.cursor]
        self.cursor += 1
        return token

    def _tokenize(self, json_str):
        return re.findall(r'"(?:\\.|[^"\\])*"|[\{\}\[\]:,]|true|false|null|-?\d+(?:\.\d+)?(?:[eE][+-]?\d+)?', json_str)

    def peek(self):
        return self.tokens[self.cursor]
    
    def _parse_dict(self) -> dict:
        result = dict()
        self.consume() #consume opening {
        
        while self.peek() != "}":
            key = self._parse_alphanumeric()
            next = self.consume() #consume :

            if next != ":":
                raise Exception("Invalid json format")

            next = self.peek()
            result[key] = self._parse_value(next)

            separator = self.peek()

            if separator == ",":
                self.consume()
            elif separator != "}":
                raise Exception("Invalid json format")

        self.consume() #consume closing }
        return result
    
    def _parse_value(self, value):
        if value == "{":
            return self._parse_dict()
        elif value == "[":
            return self._parse_list()
        else:
            return self._parse_alphanumeric()


    def _parse_list(self) -> list:
        result = list()
        self.consume() #consume opening [
        
        while next := self.peek() != "]":
            value = self._parse_value(next)
            result.append(value)

            delimiter = self.peek()

            if delimiter == ",":
                self.consume() #consume ,
            elif delimiter != "]":
                raise Exception("Invalid json format")

        self.consume() #consume closing ]
        return result

    def _parse_alphanumeric(self) -> str:
        current = self.consume()
        if current.isdigit():
            try:
                return int(current)
            except Exception:
                return float(current)
        elif current.startswith('"') and current.endswith('"'):
            return str(current.strip('"'))
        else:
            raise Exception("invalid json format")
        
    def parse(self, json_str: str)-> dict | list | None:
        self.tokens = self._tokenize(json_str) #split the json string into tokens
        token = self.peek() #peek to decide which rule to follow 

        if token == "{":
            return self._parse_dict()

        elif token == "[":
            return self._parse_list()
        else:
            raise Exception("Invalid json format")


if __name__ == "__main__":
    # json_str = """
    # {
    #     "chiave" : "valore",
    #     "," : ,
    # }
    # """

    json_str = """
        [
            "item1" , "item2"
        ]
        """

    parser = Parser()
    result = parser.parse(json_str)
    print(result)