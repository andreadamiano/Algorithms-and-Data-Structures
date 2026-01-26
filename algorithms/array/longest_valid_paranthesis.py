def longestValidParentheses(s):
    ls = len(s)
    stack = [-1]
    max_len = 0 

    for i in range(ls):
        char = s[i]
        if char == "(":
            stack.append(i)

        elif char == ")":
            stack.pop()
            if not stack:
                stack.append(i)

            else: 
                current_len = i - stack[-1]  # stack[-1] store the index of the last unmatched parenthesis 
                max_len = max(max_len, current_len)
    
    return max_len


if __name__ == "__main__":
    s = "()))"
    # s = "(()"
    # s = "(())"
    # s = ""
    # s = "()(()"
    # s = "()(())"
    # s = ")()())"
    # s = "(()()"
    print(longestValidParentheses(s))