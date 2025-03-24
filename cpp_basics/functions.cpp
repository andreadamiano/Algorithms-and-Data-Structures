#include <iostream>

int sum (int a, int b) {
    return a + b;
}

bool is_even(int array [], int n )
{
    int sum =0; 
    for (int i = 0; i < n; i++)
    {
       sum += array[i];
    }
    if (sum % 2 != 0)
    {
        return false;
    }
    else
    { 
        return true;
    }
}

// Function declaration (prototype)
void myFunction();

// Function definition
void myFunction() {
    std::cout << "Hello from myFunction!" << std::endl;
}

void funzione (int *a) // pass by pointer
{
    *a = 10;
    std::cout << "funzione" << std::endl;
    std::cout << *a << std::endl;
}

void funzione_2 (const int &a) // pass by reference (memory effcient)
{
    // a = 10; //the variable is const, so it cannot be modified
    std::cout << "funzione 2" << std::endl;
    std::cout << a << std::endl;
}

void modifyArray(int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        array[i] = 0;
    }
}

void print(int a)
{
    std::cout << a << std::endl;
}

void print(char a)
{
    std::cout << a << std::endl;
}

inline int max(int num, int num_2)  {return(num > num_2 ? 1 : 0);}

int main ()
{
    // int num = 10;   
    // int num_2 = 7;

    // int num_3 = sum (num, num_2);
    // std::cout << num_3 << std::endl;

    int array [] = {2, 4, 6, 8, 10};
    int n = 5;
    bool result = is_even(array, n);

    std::cout << result << std::endl;

    myFunction();  // Calling the function

    int num = 5;
    funzione(&num);

    funzione_2(num);

    std::cout << num << std::endl;

    modifyArray(array, n);
    std::cout << "printing array" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << array[i] << std::endl;
    }

    //function overloading (defining 2 functions with the same name but different parameters)
    print(5);
    print('a');


    //inline function
    int result_2 = max(10, 20);
    std::cout << result_2 << std::endl;

    

    return 0;
}
