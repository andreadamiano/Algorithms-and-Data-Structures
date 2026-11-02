#include <iostream>
#include <fstream>

int main ()
{
    //read a file all at once 
    std::ifstream file ("file.txt", std::ios::in | std::ios::ate); //open file, std::ios::ate flag is used to set the position of the file pointer to the end of the file
    std::string filecontent; // Create a string variable to store the content of the file

    if (file)
    {
        //get size of the file 
        std::streampos size = file.tellg(); // Get the position of the file pointer (std::streampos is the type telig returns)
        std::cout << "Size of the file: " << size << " bytes" << std::endl; // Print the size of the file


        //allocate memory to store the content of the file
        filecontent.resize(size); // Resize the string variable to store the content of the file

        //move the file pointer to the beginning of the file
        file.seekg(0, std::ios::beg); // Move the file pointer to the beginning of the file (position 0 from the begiinning of the file)

        //read the content of the file
        file.read(&filecontent[0], size); // Read the content of the file and store it in the string variable
        //read requires the address of the first element of the string variable, which is obtained by using the address-of operator (&)

        std::cout << filecontent << std::endl; // Print the content of the file

        file.close(); // Close the file
    }
}