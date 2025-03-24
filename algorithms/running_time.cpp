#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <chrono>
#include <random>
#include <fstream>


//algorithm to test 
void Sorting(std::vector<int> array)
{
    std::sort(array.begin(), array.end()); //sort the array 
}

//measure computational time 
template <typename Func>
double measureTime (Func func, std::vector<int>& array)
{
    auto start = std::chrono::steady_clock::now(); //get starting time 
    func(array); //call the function 
    auto end  = std::chrono::steady_clock::now(); //get end time 
    std::chrono::duration<double> elapsed = end - start; 
    return elapsed.count(); //count return the value in seconds 
}


void runningExperiments()
{ 
    std::vector<std::pair <int, double>> results; 

    //generate a random number
    std::random_device rd; //generates non-deterministic a single random numbers that will be used a seed(true randomness using hardware entropy)
    std::mt19937 gen(rd()); //pseudo-random number generator seeded using the true random generator 

    //test algorithm for different input size 
    for (int n = 1000; n <= 100000; n*=10)
    {
        std::vector<int> array(n); //create an array with n elements 
        std::uniform_int_distribution<> dis(1, n); //defines a uniform distribution between 1 and n 
        for (int& num : array)
        {
            num = dis(gen); //genrate a ranodm number inside the defined range 
        }

        //measure time (over 3 runs for satability)
        double totalTime = 0.0; 
        for (int i = 0; i <3; i++)
        {
            totalTime += measureTime(Sorting, array); 
        }

        double avgTime = totalTime /3.0;

        results.emplace_back(n, avgTime);  
    }

    //save results into a CSV file 
    std::ofstream file ("performances.csv"); //create a csv file 
    file << "n, time" << std::endl;     
    for (const auto& [n, t] : results)
    {
        file << n << "," << t << std::endl; 
    }

    //close file 
    file.close(); 


}


int main ()
{
    runningExperiments(); 
}   