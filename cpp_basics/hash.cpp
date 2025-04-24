#include <iostream>
#include <string>
#include <functional>

int main ()
{
    std::hash<std::string> hash_string; 
    std::cout << hash_string("ciao come stai?"); 
}

// #include <iostream>
// #include <string>
// #include <functional>

// int main() {
//     std::hash<std::string> hasher;

//     std::string str1 = "hello";
//     std::string str2 = "world";

//     size_t hash1 = hasher(str1);
//     size_t hash2 = hasher(str2);

//     std::cout << "Hash of '" << str1 << "': " << hash1 << std::endl;
//     std::cout << "Hash of '" << str2 << "': " << hash2 << std::endl;

//     if (hash1 == hash2) {
//         std::cout << "Collision detected!" << std::endl;
//     } else {
//         std::cout << "No collision." << std::endl;
//     }

//     return 0;
// }