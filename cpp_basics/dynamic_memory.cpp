#include <iostream>
#include <string>
#include <memory>

struct Passenger {
    std::string name;
    std::string mealPref;
    bool isFreqFlyer;
    std::string freqFlyerNo;
};

int main() {
    // Passenger *p = new Passenger; // Allocate memory on the heap

    // p->name = "Pocahontas";
    // p->mealPref = "REGULAR";
    // p->isFreqFlyer = false;
    // p->freqFlyerNo = "NONE";

    // std::cout << "Passenger: " << p->name << std::endl;

    // delete p; // Free the allocated memory

    //using smart poiinters 
    // std::unique_ptr<Passenger> p = std::make_unique<Passenger> (); //create a new Passenger object on the heap and return a smart pointer 

    // p->name = "Pocahontas";
    // p->mealPref = "REGULAR";
    // p->isFreqFlyer = false;
    // p->freqFlyerNo = "NONE";

    // std::cout << "Passenger: " << p->name << std::endl;

    // // No need to manually delete; memory is automatically freed when 'p' goes out of scope
    // return 0;

    int *p = new int  [10];

    for (int i=0; i<10 ; i++)
    {
        p[i] = i;
        std::cout << p[i] << std::endl;
    }

    delete [] p;
}