#include <iostream>

int main ()
{
    // int num = 10;
    // int num_2 = 7; 

    // if (num > num_2)
    // {
    //     std::cout << "true" << std::endl;
    // }
    // else
    // {
    //     std::cout << "false" << std::endl;
    // }


    // char command; 
    // std::cin >> command;

    // switch (command) {
    //     case 'w':
    //         std::cout << "up" << std::endl;
    //         break; // Exit the switch after handling this case
    //     case 'a':
    //         std::cout << "left" << std::endl;
    //         break; 
    //     case 's':
    //         std::cout << "down" << std::endl;
    //         break; 
    //     case 'd':
    //         std::cout << "right" << std::endl;
    //         break; 
    //     default:
    //         std::cout << "invalid command" << std::endl;
    //         break;
    // }

    // int i = 4; 
    // while (i) {
    //     std::cout << i << std::endl;
    //     i--;
    // }

    // do {
    //     std::cout << i++ << std::endl;
    //     // i++;
    // } while (i < 4);

    int array [10]; 
    for (int i = 0; i < 10; i++) {
        if (i == 5) {
            continue; // Skip the rest of the loop
        }
        if (i == 5) {
            break; // Exit the loop
        }
        array[i] = i;
        std::cout << array[i] << std::endl;
    }
    // std::cout << i << std::endl; // Error: i is not defined outside the loop

    std::cout << "printing array" << std::endl;
    for (int i =0; i<10; i++)
    {

        std::cout << array[i] << std::endl;
    }

}