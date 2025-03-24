#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>


struct SaleRecord
{
    std::string date; 
    std::string product; 
    int quantity;
    double price;
};


std::vector<SaleRecord> read_csv(const std::string& filename)
{
    std::vector<SaleRecord> records; // Create a vector of SaleRecord objects
    std::fstream file (filename, std::ios::in); // Open the file

    if (file) //if the file was opened
    {
        std::string line; 
        std::getline(file, line); //skip the header

        while (std::getline(file, line))
        {
            std::stringstream ss (line); // std::stringstream is a stream class to operate on strings (it is used to read from a string)
            SaleRecord record;

            std::string quantity_str, price_str;

            std::getline(ss, record.date, ';'); // Read the date
            std::getline(ss, record.product, ';'); // Read the product
            std::getline(ss, quantity_str, ';'); // Read the quantity
            std::getline(ss, price_str, ';'); // Read the price

            record.quantity = std::stoi(quantity_str); // std::stoi is used to convert a string to an integer
            record.price = std::stod(price_str); // std::stod is used to convert a string to a double

            records.push_back(record); // Add the record to the vector 
            std::cout << record.date << " " << record.product << " " << record.quantity << " " << record.price << std::endl; // Print the record
        }
        


        file.close(); // Close the file
    }

    return records; // Return the vector of SaleRecord objects
}

int main ()
{
    auto sales = read_csv("file.csv"); //auto is used to automatically deduce the type of the variable from its initializer

    std::unordered_map<std::string, double> total_sales; // Create an hash map , the key is a string and the value is a double

    for (const auto& sale : sales) // range-based for loop
    {
        total_sales[sale.product] += sale.quantity * sale.price; // Calculate the total sales for each product
    }


    std::cout << "Total sales by product:" << std::endl; // Print a message

    for (const auto& [product, total] : total_sales) // range-based for loop with structured bindings
    {
        std::cout << product << ": " << total << std::endl; // Print the product and the total sales
    }
}