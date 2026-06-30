class Node:
    def __init__(self, parent, letter):
        self.parent = parent
        self.children: dict[chr, "Node"] = {} #fast child node retrival
        self.letter: chr = letter
        self.end_word = False
        self.score = 0

class Trie:
    def __init__(self):
        self.root = Node(None, None)

    def add_word(self, word):
        current_node = self.root
        for ch in word:
            if ch not in current_node.children:
                current_node.children[ch] = Node(current_node, ch)
            
            current_node = current_node.children[ch]
            current_node.score += 1 #increment the score of the node

    def get_score(self, word):
        current_node = self.root
        score = 0
        for ch in word:
            current_node = current_node.children[ch]
            score += current_node.score

        return score



def sum_of_prefix_scores(words: list[str]):
    trie = Trie()
    n = len(words)
    solution = [0] * n

    #initialize trie
    for word in words:
        trie.add_word(word)

    
    for i in range(n):
        solution[i] = trie.get_score(words[i])

    return solution

    


if __name__ == "__main__":
    words = ["abc", "ab", "bc", "b"]
    print(sum_of_prefix_scores(words)) 