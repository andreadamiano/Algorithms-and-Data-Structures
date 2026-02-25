def fully_justify(words, maxWidth):
    result = []
    n = len(words)
    window_start = window_end= 0

    while window_start < n:
        win_len = 0
        while window_end < n and len(words[window_end]) + win_len + (window_end - window_start) <= maxWidth:
            win_len += len(words[window_end])
            window_end += 1

        len_spaces = maxWidth - win_len
        space_block = len_spaces // (window_end - window_start -1) if window_end - window_start -1 > 0 else len_spaces
        extra_spaces = len_spaces % (window_end -window_start -1) if window_end - window_start -1 > 0 else 0
        
        #construct a line
        line = ""

        if window_end == n:
            for j in range(window_start, window_end):
                line += f"{words[j]}" +  (" " if j < window_end-1 else "")
            line += " " * (maxWidth - len(line))


        else:
            for j in range(window_start, window_end):
                line += words[j]

                if j < window_end -1 or len(line) < maxWidth:
                    len_space = space_block + (1 if extra_spaces else 0)
                    line += " " * (len_space)
                    if extra_spaces:
                        extra_spaces -= 1

        result.append(line)
        window_start = window_end
        win_len = 0

    return result


if __name__ == "__main__":
    # words = ["This", "is", "an", "example", "of", "text", "justification."]
    # words = ["What","must","be","acknowledgment","shall","be"]
    words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"]
    words = ["ask","not","what","your","country","can","do","for","you","ask","what","you","can","do","for","your","country"]
    maxWidth = 16
    # maxWidth = 20
    result = fully_justify(words, maxWidth)
    for row in result:
        print(row)