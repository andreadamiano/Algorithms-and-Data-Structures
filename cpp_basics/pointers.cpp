#include <iostream>

int main ()
 {
  //   int a = 10;
  //   int *p = &a;

  //  std::cout << &a << std::endl;
  //  std::cout << *p << std::endl;
  //  std::cout << p << std::endl;
  //  std::cout << &p << std::endl; 

   char c = 'b';
   char* p = &c;

   std::cout << (int *) p << std::endl; //to print the address we must cast the pointer to any other type 
   std::cout << (void *) p << std::endl;
   std::cout << p << std::endl;  // char pointer are automatically dereferenced when printed to the console 
   std::cout << *p << "\n"; 

  //  int array[] = {1, 2, 3, 4, 5};
  //  int* p = array;

  //  std::cout << p << std::endl;
  //  std::cout << p[0] << std::endl;
  //  std::cout << *p << std::endl;

  //  char string[] = "ciao";

  //  int *pointer = (int *) string; 

  //  std::cout << *pointer << std::endl;


  int x = 100; 

  int* pointer_ = &x; 
  std::cout << pointer_ << "\n"; 
  std::cout << *pointer_ << "\n"; 


    
 }