from collections import deque

def ladder_lenght(beginWord, endWord, wordList):
    #use bfs to find the shortest path
    wordList = set(wordList)
    queue = deque([[beginWord, 1]]) #add first noe to the queue 

    while(queue):
        word, length = queue.popleft()
        if word == endWord:
            return length
        
        #add child to the queue 
        for i in range(len(word)):
            for c in "abcdefghijklmnopqrstuvz":
                if (next := word[:i] + c +word[i+1:]) in wordList:
                    wordList.remove(next)
                    queue.append([next, length+1])

    return 0


if __name__ == "__main__":
    beginWord = "hit" 
    endWord = "cog" 
    wordList = ["hot","dot","dog","lot","log","cog"]
    print(ladder_lenght(beginWord, endWord, wordList))