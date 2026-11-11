from collections import defaultdict

def print_human(dictionary):
    for key, value in dictionary.items():
        print(f"{key}: {value}", sep=" ")

def max_score(nums: list[int]):
    max_num = max(nums)
    nums_len = len(nums)
    index = nums_len // 2
    nums_set = set(nums)
    sieve = defaultdict(list)
    sieve_human = defaultdict(list)
    result = 0
    item_indices = defaultdict(list)

    #save the indices of the items that share the same value
    for i, num in enumerate(nums):
        item_indices[num].append(i)
    
    #sieve of Eratostene
    for i in range(2, max_num+1):
        curr = i
        while curr <= max_num:
            if curr in nums_set:
                sieve[i].extend(item_indices[curr])
                sieve_human[i].append(curr)
                
            curr += i

    # print(sieve)
    # print_human(sieve_human)

    used = set()
    for bucket_index, bucket in reversed(sieve.items()):
        bucket_len= len(bucket)
        if bucket_len < 2:
            continue
        
        tmp1 = None
        tmp2 = None
        
        for i in range(bucket_len-1, -1, -1):
            item = bucket[i]

            if tmp1 == None and item not in used:
                tmp1 = item

            elif tmp2 == None and item not in used: 
                tmp2 = item

            if tmp1 != None and tmp2 != None:
                print(f"{tmp1}-{tmp2}:{bucket_index}:{i}")
                result += index * bucket_index
                index -= 1
                used.add(tmp1)
                used.add(tmp2)
                tmp1 = None
                tmp2 = None

    while index:
        result += index
        index -= 1

    return result
            

if __name__ == "__main__":
    nums = [1,2,3,4,5,6]
    nums = [3,4,6,8]
    # nums = [5,5]
    # nums = [10,8]
    # nums = [171651,546244,880754,412358]
    # nums = [889509,644676,621999,606262,412720,678593]
    # nums = [5987,402328,821723,898577,860342,929227,984046,776475]
    nums = [995853,58850,504472,912272,382454,597688,581332,209547]
    # nums = [281692,114808,836017,655153,193578,361154,304386,72893]
    # nums = [327161,405335,360021,441366,834880,197174,270974,114045,265771,943529]
    # nums = [679690,746157,308799,476790,736757,337644,520612,496785,119738,24783]
    # nums = [773274,313112,131789,222437,918065,49745,321270,74163,900218,80160,325440,961730]
    # nums = [977470,977470,977470,977470,977470,977470,977470,977470]
    print(max_score(nums))