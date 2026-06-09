
def kth(n, k):

    def get_height(curr_num):
        "Traverse level by level the tree and get the current height of each level"
        
        curr_height = 0
        right_bounder = curr_num + 1

        while curr_num <= n:
            curr_height += min(right_bounder, n+1) - curr_num
            curr_num *= 10
            right_bounder *= 10

        return curr_height


    curr_steps = 1
    curr_num = 1
    
    while curr_steps < k:
        height = get_height(curr_num)

        if curr_steps + height > k:
            curr_num *= 10
            curr_steps += 1

        else:
            curr_steps += height 
            curr_num += 1

    return curr_num
 



if __name__ == "__main__":
    n = 13
    n = 100
    k = 2
    k = 10
    print(kth(n, k))