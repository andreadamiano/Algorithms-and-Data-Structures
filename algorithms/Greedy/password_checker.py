from mmap import MADV_REMOVE
from collections import defaultdict
import heapq

def check(password):
    pass_len = len(password)
    min_changes  =  max(max(6 - pass_len, 0), max(pass_len - 20, 0)) #passwiord is at least 6 letters, at most 20
    consecutive_counter = 1
    counter = 0
    lowercase = False
    uppercase = False
    digit = False
    consecutives = defaultdict(lambda : 0)
    consecutives_heap = []

    for i, ch in enumerate(password):
        if i > 0 and ch == password[i-1]:
            consecutive_counter += 1

            if consecutive_counter > 2: #save sequences that have more than 3 equal letters
                consecutives[counter] = consecutive_counter

        else:
            consecutive_counter = 1
            counter += 1

        if ch.isupper():
            uppercase = True

        if ch.islower():
            lowercase = True

        if ch.isdigit():
            digit = True

    if not lowercase or not uppercase or consecutives or not digit:
        if pass_len <= 20:
            min_changes = max(min_changes, max(sum(v // 3 for v in consecutives.values()), int(not lowercase) + int(not uppercase) + int(not digit))) #get the max required changes to satisfy the strong password condition

        elif pass_len > 20:
            for consecutive_key, consecutive_item in consecutives.items():
                heapq.heappush(consecutives_heap, (consecutive_item % 3, consecutive_key)) #min heap, store the consecutive sequences ordered by their replacement cost

            remove = min_changes
            while remove and consecutives_heap:
                mod, consecutive_key = heapq.heappop(consecutives_heap)
                removed = min(mod+1, remove) #remove the required quantity to drop by one the consecutive sequence // 3
                consecutives[consecutive_key] -= removed #int are immutable objects in python!
                remove -= removed

                if consecutive_item:
                    heapq.heappush(consecutives_heap, (consecutives[consecutive_key] % 3, consecutive_key)) #append the new sequence with its new replacement cost

            min_changes += max(int(not lowercase) + int(not uppercase) + int(not digit), sum(v // 3 for v in consecutives.values()))

    return min_changes






if __name__ == "__main__":
    password = "a"
    password = "aa123"
    password = "b1111"
    password = "aaa111"
    # password = "1111111111"
    # password = "ABABABABABABABABABAB1"
    password = "bbaaaaaaaaaaaaaaacccccc"
    # password = "aaaabbbbccccddeeddeeddeedd"
    # password = "FFFFFFFFFFFFFFF11111111111111111111AAA"
    password = "QQQQQ"
    print(check(password))