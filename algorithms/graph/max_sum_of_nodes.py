def max_sum(nums, k, edges):
    """ 
   This is presented as a graph problem, but we can optimize it by treating it as an array problem due to 3 key properties:
    
    1) Reversibility of XOR
    2) The tree is connected
    2. Path Propagation: If we want to flip two arbitrary nodes (u, v) anywhere 
    in the tree, we can flip every edge along the unique path connecting them. 
    The intermediate nodes will be XORed twice (effectively canceling out), 
    leaving only the two chosen endpoints flipped
    """
    delta = [(num ^ k) - num for num in nums] #compute the delta between the potential new value obtained and the current vaulue
    result = sum(nums)

    #be greedy, xor the values with the biggest delta first
    delta.sort(reverse=True)

    for i in range(0, len(nums), 2):
        if i == len(nums) -1:
            break
        
        path_delta = delta[i] + delta[i+1]

        if path_delta > 0:
            result += path_delta
    
    return result


if __name__ == "__main__":
    nums = [2,3]
    k = 7
    edges = [[0,1]]
    print(max_sum(nums, k, edges))