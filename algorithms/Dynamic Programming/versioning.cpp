#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cassert>

template <typename T>
std::vector<std::vector<int>> lcs(std::vector<T> &A, std::vector<T> &B)
{
    size_t size_a = A.size(); 
    size_t size_b = B.size(); 
    std::vector<std::vector<int>> dp(size_a + 1, std::vector<int>(size_b + 1, 0));
    
    for (int i = 1; i <= size_a; ++i)
    {
        for (int j = 1; j <= size_b; ++j)
        {
            if (A[i-1] == B[j-1])
                dp[i][j] = dp[i-1][j-1] + 1; 
            else
                dp[i][j] = std::max(dp[i][j-1], dp[i-1][j]); 
        }
    }
    return dp; 
}

template <typename T>
std::vector<T> common_subsequence(std::vector<std::vector<int>> &dp, std::vector<T> &A, std::vector<T> &B)
{
    std::vector<T> cs; 
    int i = A.size();
    int j = B.size(); 

    while (i > 0 && j > 0)
    {
        if (A[i-1] == B[j-1])
        {
            cs.emplace_back(A[i-1]); 
            --i; 
            --j;
        }
        else if (dp[i-1][j] > dp[i][j-1])
            --i; 
        else
            --j; 
        

    }
    std::reverse(cs.begin(), cs.end());
    return cs; 
}


// int main ()
// {
//     std::string a = "ciao come va?";
//     std::string b = "ciao come"; 
//     std::vector<char> A(a.begin(), a.end());
//     std::vector<char> B(b.begin(), b.end());

//     auto dp = lcs(A, B); 
    
//     for (size_t i = 0; i < dp.size(); ++i)
//     {
//         for (size_t j = 0; j < dp[i].size(); ++j)
//             std::cout << dp[i][j] << ' ';
//         std::cout << '\n';
//     }

//     auto cs = common_subsequence(dp, A, B); 
//     for (size_t i = 0; i < cs.size(); ++i)
//         std::cout << cs[i]; 
// }

template <typename T>
void versioning(std::vector<T> &cs, std::vector<T> &fileA, std::vector<T> &fileB)
{
    int indexA = 0; 
    int indexB = 0; 
    for (auto line : cs)
        {
            while (fileA[indexA] != line)
            {
                std::cout << "\x1b[31m - " << fileA[indexA] << "\n\x1b[0m";
                ++indexA; 
            }
            while (fileB[indexB] != line)
            {
                std::cout << "\x1b[32m + " << fileB[indexB] << "\n\x1b[0m";
                ++indexB; 
            }
            assert(fileA[indexA] == fileB[indexB]);
            std::cout << fileB[indexB] << "\n"; 
            ++indexA; 
            ++indexB; 
        }

        //print remaining lines 
        while (indexA < fileA.size())
        {
            std::cout << "\x1b[31m - " << fileA[indexA] << "\n\x1b[0m";
            ++indexA; 
        }
        while (indexB < fileB.size())
        {
            std::cout << "\x1b[32m + " << fileB[indexB] << "\n\x1b[0m";
            ++indexB; 
        }
}


std::vector<std::string> read_file(const std::string &name)
{
    std::ifstream file(name); 
    std::string line; 
    std::vector<std::string> content; 

    if (file.is_open())
    {   
        while (std::getline(file, line))
        {
            content.push_back(line); 
        }
        file.close(); 
        return content; 
    }
    else
    {
        std::cout << "Failed to open file: " + name + "\n"; 
        exit(-1); 
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage: <filename1> <filename2>\n"; 
        exit(-1); 
    }

    std::vector<std::string> fileA = read_file(argv[1]); 
    std::vector<std::string> fileB = read_file(argv[2]); 

    auto dp = lcs(fileA, fileA);
    auto cs = common_subsequence(dp, fileA, fileB); 
    versioning(cs, fileA, fileB); 
    
    
}