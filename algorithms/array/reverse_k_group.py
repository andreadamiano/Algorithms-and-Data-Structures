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
    
def build_linked_list(list: list):
    dummy = ListNode(0)
    current = dummy
    for item in list:
        node = ListNode(item)
        current.next = node
        current = current.next

    return dummy.next

def reverse_k_group(head: ListNode, k: int):
    dummy = ListNode(None, head)
    post_window = head
    pre_window = dummy
    end_node = start_node = temp_node = None
    index = 1

    while post_window is not None:
        start_node = post_window
        while index < k +1 and post_window:
            end_node = post_window
            post_window = post_window.next
            index += 1

        if index < k+1:
            return dummy.next
        
        #reverse sliding window
        next_node = start_node.next
        pointer_node = start_node
        while pointer_node != end_node:
            temp_node = next_node #save next and next next to enable traversing the singel linked list 
            next_node = next_node.next
            temp_node.next = pointer_node
            pointer_node = temp_node

        #reconnect reverse sliding window to linked list
        start_node.next = post_window
        pre_window.next = end_node
        pre_window = start_node
        index = 1
        

    return dummy.next


if __name__ == "__main__":
    #create linked list 
    linked_list = build_linked_list([1,2,3,4,5]) 
    k = 2
    print(reverse_k_group(linked_list, k))