#include "text_comprehension.h"

using namespace std; 

int main ()
{
    string text ("ciao come stai tutto bene ?"); 

    Compression compressor(text); 
    std::string encoded_text =  compressor.Encode(); 

    std::cout << "Encoded text:\n" << encoded_text; 
    std::cout << "\nBinary text:\n";  
    for(char& ch: text)
    {
        std::bitset<8> bits(ch);
        std::cout << bits; 
    }

    std::cout << "\nDecoded text: " << compressor.Decode(encoded_text) << "\n"; 
}