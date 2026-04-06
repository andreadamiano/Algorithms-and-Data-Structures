import heapq

class ListNode:
    def __init__(self, val: int = 0, next: "ListNode" = None):
        self.val = val
        self.next = next

    def __str__(self):
        current = self
        buffer = ""
        while current:
            buffer += f"{current.val}"
            current = current.next

        return buffer

def build_k_lists(lists: list[list]) -> list[ListNode]:
    result = []
    for list in lists:
        previous_node: ListNode = None
        for val in list:
            node = ListNode(val)

            if previous_node:
                previous_node.next = node
            else:
                result.append(node)

            previous_node = node

    return result


def merge_k_list(lists: list[list]) -> ListNode:
    heap = []

    # add each head of the list to  a min heap
    for index, node in enumerate(lists):
        if node:
            heapq.heappush(heap, (node.val, index, node))

    dummy = ListNode(0)
    current = dummy

    while heap:
        value, index, node = heapq.heappop(heap)

        current.next = node # connect current with next node
        current = node # hop to the next element of the linked list

        if node.next:
            heapq.heappush(heap, (node.next.val, index, node.next))


    return dummy.next 



if __name__ == "__main__":
    lists = [[1,4,5],[1,3,4],[2,6]]
    lists = build_k_lists(lists)
    print(merge_k_list(lists))