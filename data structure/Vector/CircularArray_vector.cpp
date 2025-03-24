#include <iostream>

#include <iostream>

using E = int; 
class RuntimeException
{
    public: 
        RuntimeException(const std::string& error) : error(error) {}
        std::string getError() const {return error;}

    private:
        std::string error; 
};

class VectorEmpty: public RuntimeException
{
    public: 
        VectorEmpty(const std::string& error) : RuntimeException(error) {}
};

class OutofRange: public RuntimeException
{
    public: 
        OutofRange(const std::string& error) : RuntimeException(error) {}
};



class Vector 
{
    public:
        virtual const E& at(int i) =0; 
        virtual void set(int i, const E& element) =0; 
        virtual void insert(int i, const E& element) =0; 
        virtual void erase (int i) =0; 
}; 

class CircularArrayVector : public Vector
{
    static constexpr int DEF_CAPACITY = 100; 
    public: 
        CircularArrayVector(int capacity = DEF_CAPACITY) : array(new E[DEF_CAPACITY]), n(0), capacity(capacity), f(0) {}
        ~CircularArrayVector(); 

        const E& at(int i) ; 
        void set(int i, const E& element) ; 
        void insert(int i, const E& element) ; 
        void erase (int i) ; 

    private: 
        E* array; 
        int capacity; 
        int n; 
        int f ; //index of the first element of the circluar array 
}; 



CircularArrayVector::~CircularArrayVector()
{
    for (int i=0; i < capacity; i++)
        array[(f+1)%capacity].~E(); //calls the object destructor

    delete[] array; 
}


const E& CircularArrayVector::at(int i)
{
    return array[(i+f)%capacity]; 
}

void CircularArrayVector::set(int i ,const E& element)
{
    if (i >=n || i<0)
        throw OutofRange("error, index out of range"); 
    array[(i+f)%capacity] = element; 
}

void CircularArrayVector::insert(int i , const E& element)
{
    if (i >n  || i<0)
        throw OutofRange("error, index out of range"); 

    if(i==0) //worse case insertion in the first element 
    {
        //change front 
        f =(f-1+capacity)%capacity; 
        array[f] = element; 
    }

    else if (i ==n) //insertion at the end 
    {
        array[(f+n)%capacity] = element; 
    }

    else //mid insertion
    {
        if(i <= n/2) //insertion in the first half (shift everything to the left)
        {
            f = (f-1+capacity)%capacity; 
            for (int j=0; j<i; j++)
                array[(f+j)%capacity]= array[(f+j+1)%capacity]; 
            
            array[(f+i)%capacity] = element; 
        }
        else //second half (shift everything to the right)
        {
            for (int j=n; j>i; j--)
                array[(f+j)%capacity] = array[(f+j-1)%capacity]; 
            
            array[(f+i)%capacity] = element; 
        }
    }
    n++;

}

void CircularArrayVector::erase(int i)
{
    if (i >n)
        throw OutofRange("error, index out of range"); 


    if (i==0)
    {
        f = (f+1) %capacity; 
    }
    else if (i==n)
    {
        //no action needed beyond decrementing n 
    }

    else
    {
        if(i<i/2) //move everything to the right
        {
            for (int j=i; j>0; j--)
                array[(f+j)%capacity] = array[(f+j-1)%capacity]; 
            
            f = (f+1)% capacity; //move front to the right 
        }
        else //move everything to the left 
        {
            for (int j=0; j<n; j++)
                array[(f+j)%capacity] = array[(f+j+1)%capacity]; 
        }
    }
    n--; 
}


int main ()
{
    Vector* vector = new CircularArrayVector; 

    try
    {
        vector->insert(0,1);
        vector->insert(1, 2);
        vector->insert(2,3);
    }catch(OutofRange& error)
    {
        std::cout << error.getError();
    }

    //visualize 
    for(int i=0; i<3; i++)
    {
        std::cout << vector->at(i) << "\n"; 
    }
}