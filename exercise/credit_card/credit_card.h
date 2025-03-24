#ifndef CREDIT_CARD_H
#define CREDIT_CARD_H

#include <string>
#include <iostream>

class CreditCard 
{
    private:
        std::string  number;
        std::string  name;
        int limit; 
        double balance;

    public:
        CreditCard(const std::string& num, const std::string& nm, int lim, int bal = 0);
        std::string getNumber() const {return number;}  //const menas that the function does not modify the object
        std::string getName() const {return name;} 
        double getBalance() const {return balance;}
        int getLimit() const {return limit;}


        bool chargeIt(double price); //check if the charge is possible
        void makePayment(double payment); //make a payment



};

std::ostream& operator<<(std::ostream& out, const CreditCard& c); //overload the << operator

#endif