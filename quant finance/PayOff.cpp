#include "PayOff.h"
#include <iostream>

//PayOffCall
double PayOffCall::operator() (const double& S) const
{
    return std::max(S-K, 0.0); 
}

//PayOffPut
double PayOffPut::operator() (const double& S) const
{
    return std::max(K-S, 0.0); 
}

//PayOffDigital 
double PayOffDigitalCall::operator() (const double& S) const
{
    if((S-K)>=0) 
        return 1.0; 
    else        
        return 0.0; 
}

double PayOffDigitalPut::operator() (const double& S) const
{
    if((K-S)>=0) 
        return 1.0; 
    else        
        return 0.0; 
}

//PayOffDoubleDigital 
double PayOffDoubleDigitalCall::operator() (const double& S) const
{
    if (S>= D && S<=U)
        return 1.0; 
    
    else
        return 0.0;     
}

double PayOffDoubleDigitalPut::operator() (const double& S) const 
{
    if (S<= D || S>= U)
        return 1.0; 
    else    
        return 0.0; 
}


int main ()
{
    PayOff* p = new PayOffCall(100); 

    std::cout << (*p)(150); 
}