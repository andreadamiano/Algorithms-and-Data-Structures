#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm> // Include for std::find


std::vector<char> getUniqueLetters(const std::vector<std::vector <char> >& addends, const std::vector <char> & result) {
    std::vector<char> unique_letters;  

    // Combine all the strings into a single string
    std::string combined; 

    for (const auto& str : addends) 
    {
        combined.append(str.begin(), str.end());
    }
    combined.append(result.begin(), result.end());


    // Convert the combined string into a set (which automatically removes duplicates)
    std::set<char> unique_set(combined.begin(), combined.end());


    // Convert the set into a vector
    unique_letters = {unique_set.begin(), unique_set.end()}; 

    return unique_letters; 
}


std::vector<std::vector<char> > addends {{'s', 'e', 'n', 'd'}, {'m', 'o', 'r', 'e'}}; 
std::vector<char> result {'m', 'o', 'n', 'e', 'y'}; 
std::vector<char> unique_letters = getUniqueLetters(addends, result); 
std::vector<std::unordered_map<char, int> > solutions; 
int count =0; 


int getNumber (std::vector<char>& word, std::unordered_map<char, int>& map)
{
    int num =0;  
    for (char ch : word)
    {
        num = num * 10 + map.at(ch);
    }

    return num; 
}


bool isSolution(std::unordered_map<char, int> map)
{
    //check if the left-most digit is a zero 
   if (map.at(addends[0][0]) == 0 || map.at(addends[1][0]) == 0 || map.at(result[0]) == 0)
        return false;

    int sum = getNumber(addends[0], map) + getNumber(addends[1], map); 
    if (sum == getNumber(result, map))
        return true; 
    
    return false; 
}


//this function will generate all passible permutations of the 9 digits 
std::vector<std::unordered_map<char, int> > PuzzleSolve(int k , std::vector<char>& S, std::vector<char>& U)
{
    //create a copy of U to iterate over (since U gets modified in the loop)
    std::vector<char> elements (U.begin(), U.end()); 
    count ++; 


    for (auto e : elements)
    {
        auto it = std::find(U.begin(), U.end(), e); //find iterator 
        U.erase(it); //eliminate the element at a specific position 
        S.push_back(e); 
        if (k == 1) 
        {
            //once a permutation has been determined map all digits to the corresponding letters 
            std::unordered_map<char, int> map; 
            for (int i=0; i<unique_letters.size(); i++)
            {
                map[unique_letters[i]] = S[i] - '0'; //convert ascii value into int 
            }

            if (isSolution(map))
                solutions.push_back(map); //add solution 
            
        }
        else 
        {
            PuzzleSolve(k-1, S, U); 
        }

        //restore state for the other recursions
        S.pop_back();
        U.insert(it, e); 
        
    }

    return solutions; 
}



int main ()
{
    std::vector<char> U {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    std::vector<char> S;   

    int k = static_cast<int>(unique_letters.size());
    auto solutions = PuzzleSolve(k, S, U); 

    //nunmber of solutions found 
    std::cout << "n of solutions: " << solutions.size() << std::endl; 

    std::cout << "tot number of recursions: " << count << "\n";


    //print solutions
    for (int i = 0; i< solutions.size(); i++)
    {
        for (auto elements : solutions[i])
        {
            std::cout << elements.first << "-->" << elements.second << std::endl; 
        }
    }

}