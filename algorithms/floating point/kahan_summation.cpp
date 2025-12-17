#include <vector>
#include <iostream>

double kahanSum(std::vector<double> &fa)
{   
    double sum = 0.0;

    // Variable to store the error
    double c = 0.0;

    // Loop to iterate over the array
    for(double f : fa) 
    {
        double y = f - c;
        double t = sum + y; 
        
        // Algebraically, c is always 0
        // when t is replaced by its
        // value from the above expression.
        // But, when there is a loss,
        // the higher-order y is cancelled
        // out by subtracting y from c and
        // all that remains is the
        // lower-order error in c
        c = (t - sum) - y; 
        sum = t;
    }
    return sum;
}

double sum(std::vector<double> &fa)
{
    double sum = 0.0;

    // Loop to find the sum of the array
    for(double f : fa) 
    {
        sum = sum + f;
    } 
    return sum;
} 

int main()
{
    std::vector<double> no(10);
        for(int i = 0; i < 10; i++)
        {
            no[i] = 0.1;
        }
    
        // Comparing the results
        std::cout << "Normal sum: " << sum(no) << " \n";
        std::cout << "Kahan sum: " << kahanSum(no);
}