#include <iostream>
#include <iomanip> // for std::setw, std::setfill

int main() {
    int number = 0x44332211; // A number we can easily recognize in hex

    unsigned char* byte_ptr = reinterpret_cast<unsigned char*>(&number);

    for (int i=0; i < sizeof(number); ++i)
    {
        int byte = static_cast<int> (byte_ptr[i]);
        std::cout << "byte in hex format: " << std::hex << byte << "\n"; 

        std::string buffer; 
        for (int i = 7; i >=0; --i)
        {
            //get single bit 
            char bit = (byte >> i) & 1; 
            buffer.push_back(bit + '0'); //'0' to convert the numbe in a char literal
        }
        std::cout << "\tsingle bits: " << buffer <<"\n"; 
    }


    return 0;
}