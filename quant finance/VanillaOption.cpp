#ifndef VANNILLA_OPTION_CPP
#define VANNILLA_OPTION_CPP


#include <iostream>
#include "VanillaOption.h"
#include <cmath>

void VanillaOption::init() 
{
    K = 100.0; 
    r = 0.05; //5% interest rate 
    T = 1.0;  // 1 year until maturity
    S = 100.0; //option is at the money, since spot price equals to strike price 
    sigma = 0.2;  //volatility is 20%
}

void VanillaOption::copy(const VanillaOption& option)
{
    K = option.K ; 
    r = option.r; 
    T = option.T;
    S = option.S;
    sigma = option.sigma;  
}

VanillaOption::VanillaOption()
{
    init();
}


VanillaOption::VanillaOption(double& K, double& r, double& T, double& S, double& sigma) : K(K), r(r), T(T), S(S), sigma(sigma) {}

VanillaOption& VanillaOption::operator=(const VanillaOption& option)
{
    if (this != &option)
        return *this; 
    
    else
    {
        copy(option); 
        return *this; 
    }
}

VanillaOption::VanillaOption(const VanillaOption& option)
{
    copy(option); 
}

VanillaOption::~VanillaOption()
{
    //empty, no memory allocated on the heap 
}

double VanillaOption::getK() const {return K; }
double VanillaOption::getr() const {return r; }
double VanillaOption::getS() const {return S; }
double VanillaOption::getT() const {return T; }
double VanillaOption::getsigma() const {return sigma; }


double VanillaOption::N(double& X)
{
    return 0.5 * (1.0 + erf(x * M_SQRT1_2));  // M_SQRT1_2 = 1/√2
}

double VanillaOption::call_price() const 
{
    double sigma_sqrt_T = sigma * sqrt(T);
    double d1 = (log(S/K) +(r+sigma*sigma*0.5)*T) / (sigma_sqrt_T); 
    double d2 = d1 - sigma_sqrt_T; 
    
    return S*N(d1) - K*exp(-r*T) * N(d2); 
}

double VanillaOption::put_price() const 
{
    double sigma_sqrt_T = sigma * sqrt(T);  
    double d1 = (log(S/K) +(r+sigma*sigma*0.5)*T) / (sigma_sqrt_T); 
    double d2 = d1 - sigma_sqrt_T;      
    
    return K * exp(-r*T)*N(-d2) - S*N(-d1); 
}


#endif 