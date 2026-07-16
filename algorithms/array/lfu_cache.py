from collections import defaultdict

class Node:

    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.prev = None
        self.next = None

class OrderedDict:

    def __init__(self):
        self.dict = {}
        self.head = Node(0, 0)
        self.tail = Node(0, 0)
        self.head.next = self.tail
        self.tail.prev = self.head
        self.elements = 0

    def __len__(self):
        return self.elements

    def _remove_node(self, node: Node):
        node.prev.next = node.next
        node.next.prev = node.prev
        self.elements -= 1
        self.dict[node.key] = None
        return node

    def _append(self, node: Node):
        self.tail.prev.next = node
        node.prev = self.tail.prev
        node.next = self.tail
        self.tail.prev = node
        self.elements += 1
    
    def empty(self):
        return self.elements == 0
    
    def pop(self):
        if self.empty():
            return None
        
        top: Node = self.head.next
        self.head.next = top.next
        top.next.prev = self.head
        top.next = None
        top.prev = None
        self.dict[top.key] = None
        self.elements -= 1
        return top.value

    def pop_key(self, key):
        return self._remove_node(self.dict[key]).value

    def top(self):
        return self.head.next if not self.empty() else None
    
    def get(self, key):
        return self.dict[key]
    
    def put(self, key, value):
        if key in self.dict:
            self._remove_node(self.dict[key])

        self.dict[key] = (node := Node(key, value))
        self._append(node)


class LFUCache:

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.use_counter = defaultdict(int) #maps keys to their frequencies
        self.cache = defaultdict(OrderedDict)  #maps frequencies with an OrderedDict object, which will keep track of the order of insertion of the items of the same frequency
        self.min_frequency = float("inf")

    def _update_min_frequency(self, key_frequency):
        if key_frequency < self.min_frequency:
            self.min_frequency = key_frequency

        #if the min frequency bin is empty increase the min frequency
        elif key_frequency == self.min_frequency and self.cache[self.min_frequency].empty():
            self.min_frequency += 1

    def empty(self):
        return len(self.cache) == 0

    def get(self, key: int):
        if key not in self.use_counter:
            return 

        #when a value is retrieved move it from a frequency slot to another incremented frequency slot
        key_frequency = self.use_counter[key]
        value = self.cache[key_frequency].pop_key(key)
        self.use_counter[key] += 1
        self.cache[key_frequency+1].put(key, value)

        #check if it was the least frequent item and if that slot is empty (in order to update the min frequency value)
        self._update_min_frequency(key_frequency)

        return value

    def put(self, key: int, value: int):
        if self.capacity == 0:
            return
        
        if key in self.use_counter:
            key_frequency = self.use_counter[key]
            self.cache[key_frequency].pop_key(key)

        elif len(self.cache) + 1 >= self.capacity:  #if there are no more slots remove the least frequent key
            value_pop = self.cache[self.min_frequency].pop()  
            self.use_counter.pop(value_pop)

        self.use_counter[key] += 1
        key_frequency = self.use_counter[key]
        self.cache[key_frequency].put(key, value)

        #check if it was the least frequent item and if that slot is empty (in order to update the min frequency value)
        self._update_min_frequency(key_frequency)



if __name__ == "__main__":
    lru = LFUCache(3)
    lru.put(1, 1)
    lru.put(2, 2)
    lru.put(3,3)

    lru.get(1)
    lru.get(2)
    lru.get(3)

    # this should remove 1 
    lru.put(4, 4)

    #test
    print(f"Value of key 1: {lru.get(1)}")
    print(f"Value of key 2: {lru.get(2)}")
    print(f"Value of key 3: {lru.get(3)}")
    print(f"Value of key 4: {lru.get(4)}")
