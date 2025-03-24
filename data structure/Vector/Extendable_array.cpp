#include <iostream>
#include <vector>


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


using E = int; 

class ExtendableVector  
{
    static constexpr int DEF_CAPACITY = 0; 
    public: 
        ExtendableVector(int capacity = DEF_CAPACITY) : capacity(capacity), n(0), array(new E[capacity]), f(0) {}; //default constructor 
        ExtendableVector(const ExtendableVector& vector); ///copy constructor 
        ~ExtendableVector(); //destructor 
        int size() const; 
        bool empty() const; 
        E& at(int i) const ; 
        void erase (int i);
        void insert (int i , const E& element); 

        //operator overloading 
        E& operator [] (int i); 
        const ExtendableVector& operator= (const ExtendableVector& vector); 

    private: 
        int n; 
        int capacity; 
        E* array;  
        int f; 

    protected:
        void reserve (int N);  //reserve at least N spots 

}; 

ExtendableVector::~ExtendableVector()
{
    delete [] array; //it will call each elements destructor 
}

//copy constructor 
ExtendableVector::ExtendableVector(const ExtendableVector& vector) : capacity(vector.capacity), n(vector.n), f(vector.f), array(nullptr)
{
    if (capacity)
    {
        array = new E[capacity]; //allocate memory on the heap 

        for (int i =0; i < n; i++) 
        {
            array[(f+i)%capacity] = vector.array[(i+f)%capacity]; //copy elements of the vector 
        }

    }
} 

//assignment operator 
const ExtendableVector& ExtendableVector::operator= (const ExtendableVector& vector )
{
    if (this != &vector)//check i'm not copying the object on himself 
    {
        E* newArray = nullptr; 
        
        if (vector.capacity)
        {
            newArray = new E[vector.capacity]; //allocate memory on the heap 

            for (int i =0; i < vector.n; i++)
            {
                newArray[(vector.f+i)%vector.capacity] = vector.array[(vector.f +i)%vector.capacity]; //copy elements into new vector 
            }
                
        }

        delete[] array; //deallocate old array 

        array = newArray; 
        capacity = vector.capacity; 
        f = vector.f; 
        n = vector.n; 
    }

    return *this; //return the newly created object 
}


int ExtendableVector::size() const 
{
    return n; 
}

bool ExtendableVector::empty() const
{
    return n==0; 
}

E& ExtendableVector::at(int i) const 
{
    if (i<0 ||i>=n)
        throw OutofRange("error, index out of range"); 
    return array[(f+i)%capacity]; 
}

E& ExtendableVector::operator[] (int i)
{
    return array[(f+i)%capacity]; 
}

void ExtendableVector::erase(int i)
{
    //check index is in range 
    if (i<0 ||i>n)
        throw OutofRange("error, index out of range"); 

    if(i==0)
    {
        f = (f+1)%capacity; 
    }
    else if (i ==n)
    {

    }
    else 
    {
        if (i<n/2)
        {
            for (int j =i; j>0; j--)
                array[(f+j)%capacity] = array[(f+j-1)%capacity];  //move elements to the right 

            f = (f+1)%capacity; //move front one step to the right 
        }
        else 
        {
            for (int j=0; j<n; j--) //move elements to the left 
                array[(f+j)%capacity] = array[(f+j+1)%capacity]; 
        }
    }
    n--; 
}

void ExtendableVector::reserve(int N)
{
    if (N<=capacity) //check if N already exceeed capacity 
        return; 
    
    //visualizing 
    // std::cout << "resizing" << "\n"; 

    E* newArray = new E[N]; //allocate memroy on the heap

    for (int i =0; i<n; i++)
    {
        newArray[(f+i)%capacity] = array[(f+i)%capacity]; 
    }

    //check if old array was empty 
    if (array != nullptr)
        delete[] array; //deallocate old array 

    array = newArray; 
    capacity = N; 
}


void ExtendableVector::insert(int i, const E& element)
{
    if (i<0 || i>n)
        throw OutofRange("error, index out of range"); 
    if (n>=capacity)
        reserve(std::max(i+1, capacity*2)); //increase capaciy of the array

    if (i==0)
    {
        f= (f-1+capacity)%capacity; 
        array[f]= element; 
    }
    else if (i ==n)
    {
        array[(f+n)%capacity] = element; 
    }
    else
    {
        if (i<=n/2)
        {
            f = (f-1+capacity)%capacity; 
            for (int j=0; j<i; j++) //move elements to the left
                array[(f+j)%capacity]= array[(f+j+1)%capacity]; 

            array[(f+i)%capacity] = element; 

        }
        else
        {
            for (int j=n; j>i; j--)
                array[(f+j)%capacity] = array[(f+j-1)%capacity]; 
            
            array[(f+i)%capacity] = element; 
        }
    }

    n++; 
}



// int main ()
// {
//     ExtendableVector vector; 

//     try
//     {
//         vector.insert(0,1);
//         vector.insert(1, 2);
//         vector.insert(2,3);
//         vector.insert(3,4); 
//     }catch(OutofRange& error)
//     {
//         std::cout << error.getError();
//     }

//     //visualize 
//     for(int i=0; i<4; i++)
//     {
//         std::cout << vector.at(i) << "\n"; 
//     }
// }

//stl vector 
int main()
{
    std::vector<int> vector (100); 

    try
    {
        std::cout << vector.at(1000); 
    }catch(std::out_of_range& error)
    {
        std::cout << error.what(); 
    }
}