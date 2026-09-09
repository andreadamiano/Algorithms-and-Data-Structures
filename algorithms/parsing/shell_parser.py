from enum import Enum

class TokenType(Enum):
    ATOM = 'a'              
    PIPE = '|'              
    OPEN_PAR = '('          
    CLOSE_PAR = ')'         
    SEPARATOR = ';'         
    AND = '&'               
    REDIR_IN = '<'          
    REDIR_OUT = '>'         
    REDIR_APPEND = '+'      
    EOF = 0      

class Token:
    def __init__(self, value: str, type: TokenType):
        self.value = value
        self.type = type

    def __repr__(self):
        return f"Token(value={self.value!r}, type={self.type!r})"

class CommandType(Enum):
    EXEC="EXEC"
    REDIR="REDIR"
    LIST="LIST"
    PIPE="PIPE"
    BACK="BACK"

#define the nodes ot the AST

class ExecCommand:
    def __init__(self, command: str, args: list[str] = None): 
        self.command_type = CommandType.EXEC
        self.command = command
        self.args = args if args else []

    def __repr__(self):
        return f"ExecCommand(command={self.command!r}, args={self.args!r})"

class RedirCommand:
    def __init__(self, command: str, file: str = None):
        self.command_type = CommandType.REDIR
        self.command = command
        self.file = file
        self.mode: str = None

    def __repr__(self):
        return f"RedirCommand(command={self.command!r}, file={self.file!r}), mode={self.mode!r}"

class PipeCommand:
    def __init__(self, left: str, rigth: str = None):
        self.left = left
        self.rigth = rigth

    def __repr__(self):
        return f"PipeCommand(left={self.left!r}), rigth={self.rigth!r}"

class ListCommand:
    def __init__(self, command: str, left: str, rigth: str):
        self.command_type = CommandType.LIST
        self.command = command
        self.left = left
        self.rigth = rigth

    def __repr__(self):
        return f"ListCommand(command={self.command!r}, left={self.left!r}), rigth={self.rigth!r}"

class BackCommand:
    def __init__(self, command: str):
        self.command_type = CommandType.BACK
        self.command = command

    def __repr__(self):
        return f"BackCommand(command={self.command!r}"
    


class ShellParser:
    def __init__(self):
        self.input_pos = 0
        self.input = None

    def _get_token(self, input) -> TokenType:
        if self.input_pos == len(input):
            return None

        while (curr_char := input[self.input_pos]) == " ":
            self.input_pos += 1

        match input[self.input_pos]:
            case '|' | '(' | ')' | ';' | '&' | '>' | '<':
                token_type = TokenType(curr_char)

            case '>':
                if self._peek(input) == '>':
                    self.input_pos += 1 #move the pointer twice
                    token_type = TokenType.REDIR_APPEND

            case _ :
                token_type = TokenType.ATOM

        self.input_pos += 1
        return Token(curr_char, token_type)

    def _peek(self, input: str):
        if self.input_pos == len(input):
            return " "

        i = self.input_pos + 1
        while (curr_char := input[i]) == " ":
            i += 1

        return curr_char

    def parse_shell_commands(self, input: str):
        """
        Recursive descent parser that handles manually the operator precedence, which is from lowest to highest:
            1) background & and sequentials ; , postfix operator
            2) pipe | , infix operator
            3) redirections < > , infix operator
            4) commands and arguments , prefix operator
            5) blocks () , prefix operator

        The idea behind this recursive descent parser is to manually define parselet for each operator 
        recursing down the higher level precedence operator parselets, scanning the whole input string only once. 
        Once the higher precedence parselet have finished the recursive functions will bubble up and the lower level precedence parselet operator 
        will work on the next part of the input merging eventually with the previously parsed input
        """
        command = self._parse_line(input)
        print(command)

    def _parse_line(self, input: str):
            """
            Parses multine commands and background commands, which are postorder operators
            """
            command = self._parse_pipe(input)

            if self._peek(input) in ";&":
                token: Token = self._get_token(input)

                match token.type:

                    case TokenType.SEPARATOR:
                        self._parse_line(input)

                    case TokenType.AND:
                        command = BackCommand(command)

            return command


    def _parse_pipe(self, input: str):
        """
        Parses pipe commands, which is an inorder operator
        """
        command = self._parse_redirections(input)

        if  self._peek(input) == "|":
            self._get_token(input) #consume the pipe token
            command = PipeCommand(command) #wrap the previously parsed commmand into a pipe command to generate the AST 

            rigth = self._parse_line(input) #go back to the top to parse the rigth hand side of the pipe
            command.rigth = rigth

        return command


    def _parse_redirections(self, input: str):
        command = self._parse_exec(input)

        if  self._peek(input) in "<>":
            redir_token: Token = self._get_token(input) #consume redirect token
            command = RedirCommand(command) #wrap the previously parsed commmand into a redir command to generate the AST 
            file: TokenType = self._get_token(input)

            if not file.value or file.type != TokenType.ATOM:
                raise Exception("Missing file for redirection")

            command.file = file

            match redir_token.type:
                case TokenType.REDIR_IN:
                    command.mode = "r"

                case TokenType.REDIR_OUT:
                    command.mode = "w"

                case TokenType.REDIR_APPEND:
                    command.mode = "a"


        return command


    def _parse_exec(self, input: str):
        if (token := self._get_token(input)) == TokenType.OPEN_PAR:
            self._parse_line()

            if self._get_token(input) != TokenType.CLOSE_PAR:
                raise Exception("Invalid shell command")

        command = ExecCommand(command=token)

        while self._peek(input) == TokenType.ATOM:
            token = self._get_token(input)
            command.args.append(token)

        return command


if __name__ == "__main__":
    parser = ShellParser()

    shell_input = "a | b < c"
    # shell_input = "a | (b | c)"

    # shell_input = input()
    parser.parse_shell_commands(shell_input)


