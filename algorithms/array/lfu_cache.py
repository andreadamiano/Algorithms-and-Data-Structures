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
        return top

    def pop_key(self, key):
        return self._remove_node(self.dict[key])

    def empty(self):
        return len(self.dict) == 0

    def top(self):
        return self.head.next if not self.empty() else None
    
    def put(self, key, value):
        if key in self.dict:
            self._remove_node(self.dict[key])

        self.dict[key] = (node := Node(key, value))
        self._append(node)


class LFUCache:

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.use_counter = defaultdict(int)
        self.cache = defaultdict(OrderedDict)  #this will store a sorted-dict of frequencies containing a OrderedDict of key-value pair 
        self.head = Node(0, 0)
        self.tail = Node(0, 0)
        self.head.next = self.tail
        self.tail.prev = self.head

    def empty(self):
        return len(self.cache) == 0
    
    def _append(self, node: Node):
        self.tail.prev.next = node
        node.prev = self.tail.prev
        node.next = self.tail
        self.tail.prev = node
        
    
    def _remove_node(self, node: OrderedDict):
        pass

    def _top(self):
        return self.head.next if not self.empty() else None
    
    def _pop(self):
        if self.empty():
            return None
        
        top: OrderedDict = self.head.next

        if len(top) > 0: #if there are more then one element that have the least frequency remove the least recent one
            return top.pop()

        self.head.next = top.next
        top.next.prev = self.head
        top.next = None
        top.prev = None
        self.cache[top.top().key] = None #delete the OrderDict from the cache
        return top

    def get(self, key: int):
        node = self.cache[self.use_counter[key]].pop_key(key)
        self.use_counter[key] += 1
        (ordered_dict := self.cache[self.use_counter[key]]).put(node.key, node.value)
        self._append(ordered_dict)
        return node

    def put(self, key: int, value: int):

        if key in self.cache or len(self.cache) + 1 >= self.capacity:  #if the key is already present or there are no more slots , remove the key from its current slot
            self._pop()  # pop the least frequent node

        self.use_counter[key] += 1
        (ordered_dict := self.cache[self.use_counter[key]]).put(key, value)
        self._append(ordered_dict)



if __name__ == "__main__":
    lru = LFUCache(3)
    lru.put(1, 1)
    lru.put(2, 2)
    lru.put(3,3)
    lru.get(1)
    lru.put(4, 4)