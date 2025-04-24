#ifndef PAYOFF_H
#define PAYOFF_H

#include <algorithm>

class PayOff
{
    public:
        PayOff() {} 
        virtual ~PayOff() {}
        
        virtual double operator() (const double& S) const =0; //pure virtual operator overload (which turn the class into a functor)
}; 

class PayOffCall : public PayOff
{   
    private:
        double K; //strike price 

    public:
        PayOffCall(const double& _K) : K(_K) {}
        virtual ~PayOffCall() {}
        virtual double operator() (const double& S) const ; //not pure virtual anymore
}; 

class PayOffPut : public PayOff
{
    private:
        double K; //strike price 

    public:
        PayOffPut(const double& _K) : K(_K) {}
        virtual ~PayOffPut () {} 

        virtual double operator() (const double& S) const; 
};

class PayOffDigitalPut : public PayOff
{
    private:
        double K; //strike price 

    public:
        PayOffDigitalPut(const double& _K) : K(_K) {}
        virtual ~PayOffDigitalPut () {}

        virtual double operator() (const double& S) const; 
};


class PayOffDigitalCall : public PayOff
{
    private:
        double K; //strike price 

    public:
        PayOffDigitalCall(const double& _K) : K(_K) {}
        virtual ~PayOffDigitalCall (); 

        virtual double operator() (const double& S) const; 
};

class PayOffDoubleDigitalCall : public PayOff
{   
    private:
        double U;   //upper strike price 
        double D;  //lower strike price 

    public:
        PayOffDoubleDigitalCall(const double& _U, const double& _D) : U(_U), D(_D) {}
        virtual ~PayOffDoubleDigitalCall() {} 

        virtual double operator() (const double& S) const; 
}; 

class PayOffDoubleDigitalPut : public PayOff
{   
    private:
        double U;   //upper strike price 
        double D;  //lower strike price 

    public:
        PayOffDoubleDigitalPut(const double& _U, const double& _D) : U(_U), D(_D) {}
        virtual ~PayOffDoubleDigitalPut(); 

        virtual double operator() (const double& S) const; 
}; 

#endif 