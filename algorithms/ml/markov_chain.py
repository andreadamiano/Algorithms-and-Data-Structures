from collections import defaultdict
import argparse 
import mmap
import os
import tty
import termios
import sys
import random


class Node:
    def __init__(self, parent, letter):
        self.parent = parent
        self.children: dict[chr, "Node"] = {} #fast child node retrival
        self.letter: chr = letter
        self.end_word = False


class Trie:
    def __init__(self):
        self.root = Node(None, None)

    def add_word(self, word):
        current_node = self.root
        for ch in word:
            if ch not in current_node.children:
                current_node.children[ch] = Node(current_node, ch)
            
            current_node = current_node.children[ch]

        current_node.end_word = True

    def find_words(self, prefix: str):
        current_node: Node = self.root
        words = []
        stack = [] 

        for ch in prefix:
            if ch not in current_node.children:
                return []
            
            current_node = current_node.children.get(ch)

        stack.append((current_node, prefix))
        
        while stack:
            current_node, prefix = stack.pop()

            if current_node.end_word:
                words.append(prefix)

            for ch, child in current_node.children.items():
                stack.append((child, prefix + ch))
            
        return words


class MarkovChain:
    def __init__(self):
        self.model = defaultdict(lambda: defaultdict(lambda: 1))
        self.trie = Trie()
        self.stdin_fd = sys.stdin.fileno()
        self.termios_settintgs = termios.tcgetattr(self.stdin_fd)
        tty.setraw(self.stdin_fd)

    def __del__(self):
        termios.tcsetattr(self.stdin_fd, termios.TCSADRAIN, self.termios_settintgs)
    
    def _get_stdin_char(self):
        return sys.stdin.read(1)

    def _get_word(self, map, size, index):
        word = str()
        if index >= size:
            return word, -1

        while index < size and ((ch := chr(map[index])) == ' ' or ch == '\n' or ch == '.' or ch == ',' or ch == '(' or ch == ')' or ch == '[' or ch == ']' or ch == '!' or ch == '?' or ch.isdigit() or ch == ':' or ch == ';' or ch == "'"):
            index += 1

        while index < size and ((ch := chr(map[index])) != ' ' and ch != '\n' and ch != '.' and ch != ',' and ch != '(' and ch != ')' and ch != '[' and ch != ']' and ch != '!' and ch != '?' and not ch.isdigit() and ch != ':' and ch != ';' and ch != "'"):
            word += ch
            index += 1 

        return word.lower(), index

    def train_markov_chain(self, file: str):
        with open(file, "r") as f:
            map = mmap.mmap(f.fileno(), 0, access=mmap.ACCESS_READ) #map lazily the file content into the virtual memory of the running process 

        map_size = map.size()
        
        if map_size < 1:
            print("provided file is too small")     
            os._exit(1)

        #train the markov chain on the provided file
        index = 0
        curr = ""
        prev = ""
        while True:
            
            curr, index = self._get_word(map, map_size, index)
            if index < 0:
                break

            if prev:
                self.model[str(prev)][str(curr)] += 1
                self.trie.add_word(prev)
                self.trie.add_word(curr)

            prev = curr

    def generate(self):
        prefix = str()
        prev = None
        try:
            while True:
                words = []
                ch = self._get_stdin_char()

                if ch == r'\x03' or ord(ch) == 3:
                    raise KeyboardInterrupt

                if ch == '\t': #tab pressed
                    prefix_len = len(prefix)
                    prefix = prefix.lower()

                    if not prefix and prev:
                        words = list(self.model[prev].keys())

                    if not words:
                        words = self.trie.find_words(prefix)

                    if words:
                        if prev:
                            weights = [self.model[prev][word] for word in words]
                            prev = random.choices(words, weights, k=1)[0]
                        
                        else:
                            prev = random.choice(words)
                        
                        print(f"{prev[prefix_len:]} ", end="", flush=True)
                        prefix = ""
                    
                    else:
                        print(" ", end="", flush=True)
                        prefix = ""

                elif ch == ' ':
                    prev = prefix
                    prefix = ""
                    print(ch, end="", flush=True)

                else:
                    prefix += ch
                    print(ch, end="", flush=True)


        except KeyboardInterrupt:
            os._exit(1)


    

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--file', required=True)
    args = parser.parse_args() 

    markov = MarkovChain()
    markov.train_markov_chain(args.file)
    markov.generate()