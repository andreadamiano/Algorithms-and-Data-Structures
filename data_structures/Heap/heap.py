import heapq

heap = []  # Regular list
heapq.heappush(heap, 5)  # heap = [5]
heapq.heappush(heap, 2)  # heap = [2, 5]   - 2 is parent, 5 is left child
heapq.heappush(heap, 8)  # heap = [2, 5, 8] - 2 (parent), 5 (left), 8 (right)
heapq.heappush(heap, 1)  # heap = [1, 2, 8, 5] - Reorganized to maintain heap property

print(heap)