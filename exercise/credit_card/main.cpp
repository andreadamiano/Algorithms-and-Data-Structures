#include <iostream>
#include "credit_card.h"
#include <vector>


void testCard()
{
    std::vector<CreditCard*> wallet (10); //dynamic array of 10 CreditCard objects

    //allocate 3 new CreditCard objects
    wallet[0] = new CreditCard ("5391 0375 9387 5309", "John Bowman", 2500);
    wallet[1] = new CreditCard ("3485 0399 3395 1954", "John Bowman", 3500);
    wallet[2] = new CreditCard ("6011 4902 3294 2994", "John Bowman", 5000);

    //make some charges
    for (int i =1; i <=16; i++)
    {
        wallet[0]->chargeIt(double(i));
        wallet[1]->chargeIt(2*i);
        wallet[2]->chargeIt(double(3*i));
    }

    std::cout << "Card payments: " << std::endl;
    for (int i = 0; i<3; i++)
    {
        std::cout << *wallet[i] << std::endl;
    }


    for (int i=0; i<3; i++)
    {
        // std::cout << *wallet[i] << std::endl;
        while (wallet[i]->getBalance() > 100.0)
        {
            wallet[i]->makePayment(100.0);
            std::cout << "Credi card number " << wallet[i]->getNumber() << " made a payment of 100.0" << std::endl;
            std::cout << "New balance: " << wallet[i]->getBalance() << std::endl;
        }

        delete wallet[i]; //deallocate the memory
    }


}

int main ()
{
    testCard();
    return EXIT_SUCCESS;
}