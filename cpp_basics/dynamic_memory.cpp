#include <iostream>
#include <string>

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
    // return 0;


    int *p = new int  [10];

    for (int i=0; i<10 ; i++)
    {
        p[i] = i;
        std::cout << p[i] << std::endl;
    }

    delete [] p;
}