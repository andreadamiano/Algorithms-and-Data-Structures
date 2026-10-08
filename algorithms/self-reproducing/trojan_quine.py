self = []

def payload():
    print("who are you?")
    who = input()
    
    if who == "compiler":
        return

    else:
        print(f"you have been fooled {who}")
        exit(1)
    

def main():
    payload()

    print("self = [")
    for ch in self:
        print(f"\t{ch},\n", end="")

    print(bytes(self).decode('ascii'))

main()