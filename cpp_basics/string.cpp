#include <iostream>

int main ()
{
    char string [] = "ciao";
    char string_2 []= {'c', 'i', 'a', 'o', '\0'};
    // char *string_3 = "ciao comeva";

    std::string string_4 = "ciao ";
    std::string string_5 = "come va";

    std::cout << string << std::endl;
    std::cout << string_2 << std::endl;
    // std::cout << string_3 << std::endl;

    std::cout << string_4 + string_5 << std::endl;

    if (string_4 == string_5)
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }


}