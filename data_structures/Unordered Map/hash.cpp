#include <iostream>
#include <string>

//hashing string 
size_t PolynomialHash (std::string&& string)
{
    const size_t alpha (31); //prime constant for better distribution  
    size_t hash (0); 

    for (char ch: string)
        hash = hash * alpha +  static_cast<int> (ch); 
    
    return hash; 
}

size_t CyclicShiftHash (std::string&& string )
{
    size_t hash(0); 
    for (char ch: string)
    {
        hash = (hash << 5) | (hash >> (32-5)); //shift bits to the left by 5 positions, the bits tp the right end will wrap around returning to the left side 
        hash += static_cast<int> (ch); 
    }

    return hash; 
}

//hashing floating points 

size_t HashCode(const char* array , int len)
{
    size_t hash (0); 
    for (int i=0; i< len; ++i)
    {
        hash = (hash << 5) | (hash >> (32-5)); 
        hash += static_cast<int> (array[i]); 
    }

    return hash; 
}

size_t HashFloating (const float& num)
{
    int len = sizeof(num); //number of bytes 
    const char* array = reinterpret_cast<const char *> (&num); //convert the float into an array of char 

    return HashCode(array, len);  
}


//compression function (map the hash to a specified range)

int DivisionCompression (const size_t& hash, int N)
{
    int index = hash % N; 

    return index; 
}

//multiply add and divide 
int MAD(const size_t& hash, int N)
{
    int a =31; 
    int b = 17; 
    int index = (hash*a+b) % N; 

    return index; 
}

int main()
{
    //hash generation
    size_t hash = PolynomialHash("ciao"); 
    std::cout << "ciao Hash: " <<  hash  << "\n";
    std::cout << "ocia Hash: " << PolynomialHash("ocia")  << "\n";

    std::cout << "ciao Hash: " <<  CyclicShiftHash("ciao")  << "\n";
    std::cout << "ocia Hash: " << CyclicShiftHash("ocia")  << "\n";

    float num (10.5f); 
    std::cout << "hashing a float " << HashFloating(num) << "\n"; 

    //compression
    std::cout << "division compression " << DivisionCompression(hash, 101) <<"\n"; //a prime N help reduce collision by spreding out the distibution of hash values 
    std::cout << "MAD compression " << MAD(hash, 101) << "\n"; //a prime N help reduce collision by spreding out the distibution of hash values 
    
}


// #include <iostream>
// #include <string>
// #include <cstdint> // For uint8_t (8-bit int)

// void DebugPolynomialHash(const std::string& str, uint8_t a) {
//     uint8_t hash = 0; // 8-bit hash (overflows at 256)
//     std::cout << "Hash steps for \"" << str << "\" (a=" << (int)a << "):\n";

//     for (char ch : str) {
//         uint8_t prev_hash = hash;
//         hash = hash * a + static_cast<uint8_t>(ch);
        
//         // Print each step
//         std::cout << "  '" << ch << "' (ASCII " << (int)ch << "): "
//                   << (int)prev_hash << " * " << (int)a << " + " << (int)ch 
//                   << " = " << (int)(prev_hash * a) << " (before overflow) " 
//                   << (int)hash << " (after overflow)\n";
//     }
//     std::cout << "Final hash: " << (int)hash << "\n\n";
// }

// int main() {
//     // Test with a=31 (prime) and a=32 (bad, even)
//     DebugPolynomialHash("hi", 31);
//     DebugPolynomialHash("hi", 32);
//     return 0;
// }