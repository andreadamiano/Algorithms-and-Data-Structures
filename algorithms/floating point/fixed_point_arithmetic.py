SCALAR_FACTOR = 100
SHIFT = 10

def fixed_point_division(a: int, b: int):
    """Use an implicit fixed scaling factor"""
    return a * SCALAR_FACTOR // b

def convert_float_fixed_point(result: int):
    return result / SCALAR_FACTOR

def fixed_point_binary(a: int, b: int):
    return (a << SHIFT) // b

def convert_float_fixed_point_binary(result: int):
    return result / (2 **SHIFT)

if __name__ == "__main__":
    result = fixed_point_division(2, 3)
    print(result)
    print(convert_float_fixed_point(result))    
    result = fixed_point_binary(2, 3)
    print(result)
    print(convert_float_fixed_point_binary(result))

    #rational arithmetic
    #use rational notation instead of computing the floating point result
    #ex: check if the provided number is less than 0.5
    num = input()
    parts = num.split("/")
    numerator = int(parts[0])
    denominator = int(parts[1])
    if (numerator * 2 < denominator):
        print("The number is less then 0.5")
    else:
        print("The number is more then 0.5")