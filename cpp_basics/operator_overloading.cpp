#include <iostream>
#include <string>

class Passenger 
{
    private:
        std::string name ; 
        std::string mealPref ; 
        bool isFreqFlyer ; 
        int freqFlyerNo ; 

    public:
        Passenger(const std::string& _name, const std::string& _mealPref, const bool _isFreqFlyer, const int _freqFlyerNo)  : name(_name), mealPref(_mealPref), isFreqFlyer(_isFreqFlyer), freqFlyerNo(_freqFlyerNo) {}

        //operator overloading
        bool operator==(const Passenger& other) const ;
        friend std::ostream& operator<<(std::ostream& os, const Passenger& p); 

}; 

bool Passenger::operator==(const Passenger& other) const
{
    return name == other.name
    && mealPref == other.mealPref
    && isFreqFlyer == other.isFreqFlyer
    && freqFlyerNo == other.freqFlyerNo;
}

std::ostream& operator<<(std::ostream& os, const Passenger& p)
{
    os << p.name << " " << p.mealPref << " " << p.isFreqFlyer << " " << p.freqFlyerNo; 
    return os ;  
}

int main ()
{
    Passenger x("Andrea", "Vegan", true, 10); 
    Passenger y("Andrea", "Vegan", true, 10); 

    std::cout << (x == y ) << "\n"; 

    std::cout << x; 
}