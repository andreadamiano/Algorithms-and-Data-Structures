class Node:
    def __init__(self, parent, letter):
        self.parent = parent
        self.children: dict[chr, "Node"] = {}
        self.letter: chr = letter
        self.end_word = False

class Trie:
    def __init__(self):
        self.root = Node(None, None)
        

    def add_word(self, word: str):
        current_node = self.root
        for ch in word:
            if ch not in current_node.children:
                current_node.children[ch] = Node(current_node, ch)
            current_node = current_node.children.get(ch)
        current_node.end_word = True
        

def dfs(x, y, lx, ly, current_node: Node, board, words_found, word):
    if x < 0 or y < 0 or x >= lx or y >= ly:
        return False
    
    if board[y][x] == "*":
        return False
    
    if board[y][x] in current_node.children:
        current_node = current_node.children.get(board[y][x])
        word += board[y][x]
    else:
        return False
    
    if current_node.end_word:
        board[y][x] = "*"
        words_found.add(word)
        if not current_node.children:
            return True

    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    for dx, dy in directions:
        result = dfs(x+dx, y+dy, lx, ly, current_node, board, words_found, word)

        if result:
            board[y][x] = "*"
            return True

    return False



def find_words(board, words):
    trie = Trie()
    for word in words:
        trie.add_word(word)

    lx = len(board[0])
    ly = len(board)
    words_found = set()
    for y in range(ly):
        for x in range(lx):
            dfs(x, y, lx, ly, trie.root, board, words_found, "")

    return words_found


if __name__ == "__main__":
    board = [
    ["a","b","c","d"],
    ["s","a","a","t"],
    ["a","c","k","e"],
    ["a","c","d","n"]
    ],
    words = ["bat","cat","back","backend","stack"]
    print(find_words(board[0], words))
    
    for row in board[0]:
        print(row)

