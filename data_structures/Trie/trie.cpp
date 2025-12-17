#include "tires.h"
#include "compressed_trie.h"
#include <vector>

using namespace std; 

int main ()
{
    StandardTries trie; 
    std::vector<std::string> words = { "cico", "cicoria", "cicore", "cicorato" };
    for (const auto& w : words) trie.insert(w);
    // auto root = tries.Root(); 
    trie.print(); 

    

    CompressedTrie trie2;
    std::vector<std::string> words2 = { "cico", "cicoria", "cicore", "cicorato" };
    for (const auto& w : words2) trie2.insert(w);
    trie2.print();

}