def parse_boolean(expression: str):
    n = len(expression)
    curr_index = 0

    def parse_and():
        nonlocal curr_index
        result = True

        if expression[curr_index] != "(":
            return None

        curr_index += 1        
        while expression[curr_index] != ")":
            if expression[curr_index] == "f":
                curr_index += 1
                result = False
            
            elif expression[curr_index] == "&":
                curr_index += 1
                result = result if parse_and() else False

            elif expression[curr_index] == "|":
                curr_index += 1
                result = result if parse_or() else False 

            elif expression[curr_index] == "!":
                curr_index += 1
                result = result if parse_not() else False 
            
            else:
                curr_index += 1

        curr_index += 1 
        return result


    def parse_or():
        nonlocal curr_index
        result = False

        if expression[curr_index] != "(":
            return False

        curr_index += 1        
        while expression[curr_index] != ")":
            if expression[curr_index] == "t":
                curr_index += 1
                result = True
            
            elif expression[curr_index] == "&":
                curr_index += 1
                result = result if not parse_and() else True

            elif expression[curr_index] == "|":
                curr_index += 1
                result = result if not parse_or() else True 
            
            elif expression[curr_index] == "!":
                curr_index += 1
                result = result if not parse_not() else True 

            else:
                curr_index += 1
        
        curr_index += 1 
        return result
    
    def parse_not():
        nonlocal curr_index
        result = False

        if expression[curr_index] != "(":
            return None
        
        curr_index += 1        
        while expression[curr_index] != ")":
            if expression[curr_index] == "&":
                curr_index += 1
                result = not parse_and()

            elif expression[curr_index] == "|":
                curr_index += 1
                result = not parse_not()

            elif expression[curr_index] == "f":
                curr_index += 1
                result = True
            
            elif expression[curr_index] == "t":
                curr_index += 1
                result = False
            
            elif expression[curr_index] == "!":
                curr_index += 1
                result = not parse_not()
            
            else:
                curr_index += 1
            
        curr_index += 1
        return result


    while curr_index < n:

        if expression[curr_index] == "&":
            curr_index += 1
            result = parse_and()
        
        elif expression[curr_index] == "|":
            curr_index += 1
            result = parse_or()
        
        elif expression[curr_index] == "!":
            curr_index += 1
            result = parse_not()

        elif expression[curr_index] == "f":
            return False
        
        elif expression[curr_index] == "t":
            return True

        else:
            curr_index += 1


    return result






def parse_boolean(expression: str) -> bool:
    """Stripped down version"""
    curr_index = 0
    n = len(expression)

    def parse_expr() -> bool:
        nonlocal curr_index
        char = expression[curr_index]
        curr_index += 1

        #base cases
        if char == 't':
            return True
        if char == 'f':
            return False

        #save current operator
        operator = char
        
        #skip opening (
        curr_index += 1 
        
        #gather all inner parsed operands 
        operands = []
        while expression[curr_index] != ')':
            if expression[curr_index] == ',':
                curr_index += 1
            else:
                operands.append(parse_expr())
                
        #skip closing )
        curr_index += 1 

        #evaluate operator expression
        if operator == '&':
            return all(operands)
        elif operator == '|':
            return any(operands)
        elif operator == '!':
            return not operands[0]

    return parse_expr()

    
if __name__ == "__main__":
    expression = "&(|(f))"
    expression = "|(f,t,t)"
    expression = "!(&(f,t))"
    expression = "!(f)"
    expression = "|(&(t,f,t),!(t))"
    expression = "!(!(!(!(&(&(&(&(f),&(!(t),&(f),|(f)),&(!(&(f)),&(t),|(f,f,t))),|(t),&(!(t),!(|(f,f,t)),!(&(f)))),!(&(|(f,f,t),&(&(f),&(!(t),&(f),|(f)),&(!(&(f)),&(t),|(f,f,t))),&(t))),&(&(&(!(&(f)),|(t),&(!(t),!(|(f,f,t)),!(&(f)))),!(|(f,f,t)),&(t,t,f)),&(f),&(&(t),&(!(t),!(|(f,f,t)),!(&(f))),|(f,f,t))))))))"
    print(parse_boolean(expression))