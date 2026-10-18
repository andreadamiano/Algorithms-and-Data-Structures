def arrest_elephants(m, k, tests):
    """brute force bitmask solution"""
    n = len(tests)

    for mask in range(0, (1<<n)): #the generated mask can increase the score of the ith elefant by 1 

        for i in range(0, n-k+1):
            max_test = 0
            max_num = 0

            #test every sliding window
            for j in range(i, i+k):
                current_test = tests[j] + ((mask >> j) & 1)

                if current_test > max_test:
                    max_num = 1
                    max_test = current_test
                elif current_test == max_test:
                    max_num += 1
                

            if max_num >= m: #invalidate the currente window
                break
        
        if max_num < m:
            return mask.bit_count()
    
    return -1

            

    pass 
if __name__ == "__main__":
    m = 2
    k = 3
    tests = [1, 3, 1, 2, 1]

    m = 3
    k = 3
    tests = [7, 7, 7, 8, 8]

    # k = 3
    # m = 1
    # tests = [1, 3, 1, 2]
    print(arrest_elephants(m, k, tests))