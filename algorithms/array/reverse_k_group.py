class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        result = ""
        current_node = self
        while current_node:
            result += f"{current_node.val}, "
            current_node = current_node.next
        
        return result

def reverse_k_group(head: ListNode, k: int):
    post_window = head
    pre_window = ListNode(None, head)
    end_node = start_node = temp_node = None
    index = 1

    while post_window is not None:
        start_node = post_window
        while index < k +1 and post_window:
            end_node = post_window
            post_window = post_window.next
            index += 1

        if index < k+1:
            return head
        
        #reverse sliding window
        next_node = start_node.next
        pointer_node = start_node
        while pointer_node != end_node:
            temp_node = next_node
            next_node = next_node.next
            temp_node.next = pointer_node
            pointer_node = temp_node

        #reconnect reverse sliding window to linked list
        start_node.next = post_window
        pre_window.next = end_node

        #update head
        if not pre_window.val:
            head = pre_window.next
        
        pre_window = start_node
        index = 1
        

    return head


if __name__ == "__main__":
    #create linked list 
    current_node = None
    for i in range(5, 0, -1):
        current_node = ListNode(i, current_node)
    k = 2

    print(reverse_k_group(current_node, k))