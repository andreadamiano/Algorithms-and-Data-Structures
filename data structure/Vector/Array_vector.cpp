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

class ArrayVector : public Vector
{
    static constexpr int DEF_CAPACITY = 100; 
    public: 
        ArrayVector(int capacity = DEF_CAPACITY) : array(new E[DEF_CAPACITY]), n(0), capacity(capacity) {}
        ~ArrayVector(); 

        const E& at(int i) ; 
        void set(int i, const E& element) ; 
        void insert(int i, const E& element) ; 
        void erase (int i) ; 

    private: 
        E* array; 
        int capacity; 
        int n; 

    //utility methods
    protected:
        void resize(int new_capacity); 



}; 



ArrayVector::~ArrayVector()
{
    for (int i; i < capacity; i++)
        array[i].~E(); //calls the object destructor

    delete[] array; 
}


const E& ArrayVector::at(int i)
{
    return array[i]; 
}

void ArrayVector::set(int i ,const E& element)
{
    if (i >=n || i<0)
        throw OutofRange("error, index out of range"); 
    array[i] = element; 
}

void ArrayVector::insert(int i , const E& element)
{
    if (i >n)
        throw OutofRange("error, index out of range"); 
    
    // if ((i == capacity-1) ||(n==capacity) )
    // {
    //     resize(capacity*2); //resize vector
    // }

    for (int j = n-1; j >=i; j-- )
    {
        array[j+1] = array[j];  
    }
    array[i] = element; 
    n++; 
}

void ArrayVector::erase(int i)
{
    if (i >n)
        throw OutofRange("error, index out of range"); 

    for (int j =i+1; j<=n; j++)
        array[j-1] = array[j]; 

    n--; 
}


void ArrayVector::resize(int new_capacity)
{
    E* new_array = new E[new_capacity]; //resize array

    //copy data 
    for (int i=0; i<capacity; i++)
    {
        new_array[i] = array[i]; 
        array[i].~E(); //delete object 
    }

    delete[] array; //delete array 

    array = new_array; 
    capacity = new_capacity; 
}

int main ()
{
    Vector* vector = new ArrayVector; 

    try
    {
        vector->insert(0,1);
        vector->insert(1, 2);
        vector->insert(2,3);
        vector->set(4,100);
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