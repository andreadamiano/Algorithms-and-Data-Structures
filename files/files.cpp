#include <iostream>
#include <fstream> // For file I/O
#include <string> // For string class

int main ()
{
    // std::ifstream file ("file.txt"); //object of class ifstream (input file stream) to read from file.txt and file is opened immediately

    // if (file.is_open()) // Check if the file is open
    // {
    //     std::cout << "File is open" << std::endl; // Print a message
    // }
    // else
    // {
    //     std::cout << "Unable to open file" << std::endl; // Print an error message
    // }


    //second method 
    // std::ifstream file; 
    // file.open("file.txt");

    // //check if file is open
    // if (file.is_open())
    // {
    //     std::cout << "File is open" << std::endl; // Print a message
    // }
    // else
    // {
    //     std::cout << "Unable to open file" << std::endl; // Print an error message
    // }


    //open and read file
    std::fstream file ("file.txt", std::ios::in); //object of class fstream (file stream) to read from file.txt 

    //the flags std::ios::in are used to open the file in read mode
    //the flags std::ios::out are used to open the file in write mode
    //the flags std::ios::app are used to open the file in append mode (all data is written to the end of the file)

    //std::ios::in | std::ios::out are used to open the file in read and write mode
    //it performs bitwise OR operation on the flags (since 0000 0001 represents std::ios::in and 0000 0010 represents std::ios::out)
    //std::ios::is = std::fstream::in


    //lettura di un file 
    // std::string line; // Create a string variable to store each line of the file
    // file  >> line; //read the first word of the file and store it in the variable line

    // if (file.fail())
    // {
    //     std::cout << "Unable to read file" << std::endl; // Print an error message
    // }
    // else
    // {
    //     std::cout << line << std::endl; // Print the line
    // }


    std::string line;
    //read an entire line 
    while(std::getline(file, line))
    {
        std::cout << line << std::endl; // Print the line
    }

    //close the file
    file.close();


    //open file in write mode 

    std::ofstream file2 ("file2.txt", std::ios::out); //object of class ofstream (output file stream) to write to file2.txt

    //write to file
    file2 << "Hello, World!" << std::endl; // Write a string to the file

    //close the file
    file2.close();


    //open file in append mode
    std::fstream file3 ("file.txt", std::ios::app); //object of class fstream (file stream) to write to file.txt in append mode

    //append 
    file3 << "Hello, World!" << std::endl; // Write a string to the file

    //close the file
    file3.close();


}