#include <iostream>

int main ()
 {
   //  int a = 10;
   //  int *p = &a;

   // std::cout << &a << std::endl;
   // std::cout << *p << std::endl;
   // std::cout << p << std::endl;
   // std::cout << &p << std::endl; 

   // char c = 'a';
   // char* p = &c;

   // std::cout << (int *) p << std::endl;
   // std::cout << (void *) p << std::endl;
   // std::cout << p << std::endl;

   int array[] = {1, 2, 3, 4, 5};
   int* p = array;

   std::cout << p << std::endl;
   std::cout << p[0] << std::endl;
   std::cout << *p << std::endl;

   char string[] = "ciao";

   int *pointer = (int *) string; 

   std::cout << *pointer << std::endl;





    
 }