#ifndef VANILLA_OPTION_H
#define VANILLA_OPTION_H

class VanillaOption
{
    private:
        double K; //strike price 
        double r; //risk-free rate 
        double T; //maturity time 
        double S; //underlying asset price 
        double sigma; //volatility of the underlying asset

        void init(); 
        void copy(const VanillaOption& option); 

    public: 
        VanillaOption(); //default constructor
        VanillaOption(double& K, double& r, double& T, double& S, double& sigma); //paremeter constructor 
        VanillaOption(const VanillaOption& option); //copy constructor 
        VanillaOption& operator=(const VanillaOption& option); //assignment operator 
        virtual ~VanillaOption(); //destructor 

        //selectors 
        double getK() const; 
        double getr() const; 
        double getT() const; 
        double getS() const; 
        double getsigma() const; 

        //option price calculator 
        double call_price() const; 
        double put_price() const; 
    
    protected:
        double N(double& X); 
    
};    



#endif