def bubble(array: list):
    n = len(array)
    for i in range(n, -1, -1):
        for j in range(1, i):
            prec, succ = array[j-1], array[j]

            if prec > succ:
                array[j-1], array[j] = succ, prec

if __name__ == "__main__":
    array = [9, 4, 1, 7, 89, 13 ,45, 6, 21]
    bubble(array)
    print(array)