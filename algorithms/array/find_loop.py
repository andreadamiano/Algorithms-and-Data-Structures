def find_loop(array):
    # cannot allocate more memory 
    # convert the array into a linked list and use 2 pointer to find the loop 
    p1 = p2 = 0

    while True:
        p1 = array[p1]
        p2 = array[array[p2]] #second pointer moves twice as fast

        if p1 == p2:
            break


    p1 = 0
    while p1 != p2:
        p1 = array[p1]
        p2 = array[p2]
        
    return p1



if __name__ == "__main__":
    array = [1,2,3,4,3]
    print(find_loop(array))