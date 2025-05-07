#include "tires.h"

using namespace std; 

int main ()
{
    StandardTries tries; 
    string word("ciao"); 
    string word2 ("ciai"); 
    string word3("cico"); 
    
    tries.insert(word);
    tries.insert(word2); 
    tries.insert(word3); 

    // auto root = tries.Root(); 

    tries.print(); 

    

}