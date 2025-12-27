# def longest_decomposition(text: str):
#     result = 0
#     left = right = ""
#     for i, j in zip(text, text[::-1]):
#         left += i
#         right = j + right
#         if left == right:
#             result += 1
#             left = right = ""
    
#     return result

# def longest_decomposition(text: str, res =0):
#     """using tail recursion"""
#     n = len(text)
#     for i in range(1,n//2 +1):
#         if text[0] == text[n-i] and text[i-1] == text[n-1]:
#             if text[:i] == text[n-i:]:
#                 return longest_decomposition(text[i:n-i], res+2)
    
#     return res + 1 if text else res


def longest_decomposition(text: str, res=0):
    """dynamic programming"""
    memo = {}
    def dp(i, j):
        if i > j:
            return 0
        if i == j:
            return 1
        
        if (i, j) not in memo:
            # try all possible suffix - prefix match 
            k = 0
            tmp = 1
            while i + k < j - k:
                if text[i:i+k+1] == text[j-k:j+1]:
                    tmp = max(tmp, 2 + dp(i+k+1, j-k-1)) # find matches in the substring exluding the mathces 
                k += 1
            memo[(i, j)] = tmp
        return memo[(i, j)]
    
    return dp(0, len(text)-1)

if __name__ == "__main__":
    text = "ghiabcdefhelloadamhelloabcdefghi"
    # text = "ciaociao"
    print(longest_decomposition(text))