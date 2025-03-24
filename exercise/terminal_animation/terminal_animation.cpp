#include <iostream>
#include <unistd.h>  // For sleep() function

int main ()
{
    std::cout << "\033[?25l" << std::flush; // Hide the cursor

    for (int i=0; i<10; i++)
    {
        std::cout << i << "\r" << std::flush; 
        usleep(500000); // Sleep for 0.5 seconds

    }

    std::cout << "\033[?25h" << std::flush; // Show the cursor

    sleep(1);

    return 0; 

}    