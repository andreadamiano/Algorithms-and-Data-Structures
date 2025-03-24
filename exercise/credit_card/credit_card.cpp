#include "credit_card.h"

CreditCard::CreditCard(const std::string& num, const std::string& nm, int lim, int bal): number(num), name(nm), limit(lim), balance(bal) {}

bool CreditCard::chargeIt(double price)
{
    if (balance + price > double(limit)) //casting to avoid implicit conversion
    {
        return false;
    }
    else 
    {
        balance += price;
        return true;
    }
}

void CreditCard::makePayment(double payment)
{
    balance-= payment;
}

std::ostream& operator << (std::ostream& out, const CreditCard& c)
{
    out << "Number: " << c.getNumber() << std::endl;
    out << "Name: " << c.getName() << std::endl;
    out << "Balance: " << c.getBalance() << std::endl;
    out << "Limit: " << c.getLimit() << std::endl;
    return out;
}

