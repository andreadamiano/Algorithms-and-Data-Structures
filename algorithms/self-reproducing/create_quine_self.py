import sys

def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <filename>")

    input_file = sys.argv[1]
    content = ""
    self_len = 0

    #read the quine content
    with open(input_file, "r") as input:
        while "self" not in (self := input.readline()):
            self_len += len(self)

        self_len += len(self)

        if "self" not in self:
            print("quine must declare itself at the top: e.g self = []")
            exit(1)

        content += self.replace("]", "")
        content += f"\t{ord(']')},\n"
        content += f"{f'\t10,\n' if '\n' in self else ''}" #add an extra \n if present after the array is closed

        # read the content of the quine and add it as data in ascii
        while (ch := input.read(1)):
            content += f"\t{ord(ch)},\n"

        content += f"]\n"

        # read the content once again and add it as source 
        input.seek(self_len)
        code = input.read()
        content += code

        parts = input_file.split(".")
        with open(f"{parts[0]}_plus_self.{parts[1]}", "w") as output:
            output.write(content)


if __name__ == "__main__":
    main()