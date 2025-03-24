#include <iostream>


class Progression
{
    protected:
        long first;
        long current; 
        virtual long firstValue();
        virtual long nextValue();

    public:
        Progression(long first =0): first (first), current (first) {};
        virtual ~Progression() {}; //empty destructor
        void printProgression(int n);   //print the first n values
};

void Progression::printProgression(int n)
{
    //print the first value
    std::cout << firstValue() << " " << std::endl;

    for (int i=1; i<n; i++)
    {
        std::cout << nextValue() << " "  << std::endl;
    }
}

long Progression::firstValue()
{
    current = first; 
    return current;
}


long Progression::nextValue()
{
    return ++current; //return current + 1
}


class AritmeticProgression : public Progression
{
    protected:
        long increment; 
        long nextValue() override;

    public: 
        AritmeticProgression(long first, long increment): Progression(first), increment(increment) {};
        ~AritmeticProgression() override {};

};


long AritmeticProgression::nextValue()
{
    return current += increment;
}


class GeometricProgression: public Progression
{
    protected: 
        long base; 
        long nextValue() override;
    
    public:
        GeometricProgression(long initial, long base=2): Progression(initial), base(base) {};
        ~GeometricProgression() override {};
};

long GeometricProgression::nextValue()
{
    current*=base; 
    return current;
}


class FibonacciProgression: public Progression
{
    protected:
        long second; 
        long previous; 
        long firstValue () override;
        long nextValue () override;
    public:
        FibonacciProgression(long first=0, long second=1) : Progression(first), second (second) , previous (second -first) {};
        ~FibonacciProgression() {}; 

};

long FibonacciProgression::nextValue()
{
    // long temp = previous; 
    // previous = current; 
    // current  += temp; 
    // return current; 

    long temp = current; 
    current +=previous; 
    previous= temp; 
    return current; 
}

long FibonacciProgression::firstValue()
{
    current = first;
    previous = second -first; 
    return current;
}

int main ()
{
    Progression* p [3];

    p[0] = new Progression(1);
    p[1] = new AritmeticProgression(5, 3);
    p[2] = new GeometricProgression(2, 2);
    p[3] = new FibonacciProgression (0,1);

    std::cout << "Progression: " << std::endl;
    p[0]->printProgression(10);

    std::cout << "Aritmetic Progression: " << std::endl;
    p[1]->printProgression(10);

    std::cout << "Geometric Progression: " << std::endl;
    p[2]->printProgression(10);

    std::cout << "Fibbonacci Progression: " << std::endl;
    p[3]->printProgression(10);


    for (int i =0; i<4; i++)
    {
        delete p[i]; 
    }
}