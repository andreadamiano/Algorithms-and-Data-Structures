def partition(array, left, right):
    pivot = right
    index = left

    for i in range(left, right):
        if array[i] < array[pivot]:
            array[i], array[index] = array[index], array[i]
            index += 1
    
    array[index], array[pivot] = array[pivot], array[index] 
    
    return index

def quick_sort(array, left, right):
    if left > right:
        return
    
    index = partition(array, left, right)

    quick_sort(array, left, index-1)
    quick_sort(array, index+1, right)


if __name__ == "__main__":
    array = [3, 45, 5, 2, 7, 13, 10]
    quick_sort(array, 0, len(array)-1)
    print(array)