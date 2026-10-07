def quine():
    self = """def quine():
    self = \\"\\"\\"?\\"\\"\\"
    
    for ch in self:
            if ord(ch) == 92:
                continue
    
            elif ord(ch) != 63:
                print(ch, end="")
    
            else:
                for ch in self:
                    if ord(ch) == 92:
                        print(f"{chr(92)}{chr(92)}", end="")
    
                    else:
                        print(ch, end="")

quine()"""

    for ch in self:
        if ord(ch) == 92:
            continue

        elif ord(ch) != 63:
            print(ch, end="")

        else:
            for ch in self:
                if ord(ch) == 92:
                    print(f"{chr(92)}{chr(92)}", end="")

                else:
                    print(ch, end="")

quine()