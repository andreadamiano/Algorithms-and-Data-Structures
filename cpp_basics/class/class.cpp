#include <iostream>
class Counter 
{
    private:
        int count; 

    public:
        Counter() //default constructor (initialize the counter to 0, no return type)
        {
            count = 0;
        }
        int get_counter()
        {
            return count;
        }
        void increment()
        {
            count++;
        }
}; 


class Passenger { // Full definition before member function implementation
    public:

         enum class MealType {
            VEGETARIAN,
            NON_VEGETARIAN,
            VEGAN,
            GLUTEN_FREE
        };


        // default constructor 
        Passenger()
        {
            name = "Unknown";
            isFreqFlyer = false;
            freqFlyerNo = "None";
        }
        Passenger(const std::string& nm, bool isFF, const std::string& ffn = "None") // constructor with given arguments 
        {
            name = nm;
            isFreqFlyer = isFF;
            freqFlyerNo = ffn;
        }

        //the previous initiliazation can be done with the following syntax (which is more efficient)
        Passenger(const std::string& nm, bool isFF, const std::string& ffn = "None") : name(nm), isFreqFlyer(isFF), freqFlyerNo(ffn) {}


        Passenger(const Passenger& p) // copy constructor
        {
            name = p.name;
            isFreqFlyer = p.isFreqFlyer;
            freqFlyerNo = p.freqFlyerNo;
        }

        bool isFrequentFlyer() const; // is this a frequent flyer?
        // make this a frequent flyer
        void makeFrequentFlyer(const std::string& newFreqFlyerNo);
        // . . . other member functions
    private:
        std::string name; // passenger name
        //MealType mealPref; // meal preference
        bool isFreqFlyer; // is a frequent flyer?
        std::string freqFlyerNo; // frequent flyer number
};


// Implementation of Passenger member functions
bool Passenger::isFrequentFlyer() const 
{
    return isFreqFlyer;
};

void Passenger::makeFrequentFlyer(const std::string& newFreqFlyerNo) 
{
    isFreqFlyer = true;
    freqFlyerNo = newFreqFlyerNo;
};


class destructor 
{
    private :
        int* data;
        int num;
    public:
        destructor(int num); 
        ~destructor(); // destructor
};


destructor::destructor(int num) : num(num)
{
    data = new int[num];  // dynamically allocate an array of integers
}

destructor::~destructor() //it should be written when the class dynamically allocates memory
{
    delete[] data; // delete the array
}

int main ()
{
    Counter c;
    std::cout << c.get_counter() << std::endl;
    c.increment();
    std::cout << c.get_counter() << std::endl;

    return 0;
}


class Vector 
{
    private:
        int num; 
        int* data;
    
    public:
        Vector(int n); // constructor
        Vector(const Vector& v); // copy constructor
        ~Vector(); // destructor

        // Assignment operator
        Vector& operator=(const Vector& v);
}; 


Vector::Vector(int n) : num(n)
{
    data = new int[n]; // dynamically allocate an array of integers
}

Vector::Vector(const Vector& v) : num(v.num)
{
    data = new int[num]; // dynamically allocate an array of integers
    for (int i = 0; i < num; i++)
    {
        data[i] = v.data[i]; // copy the data
    }
}

Vector::~Vector()
{
    delete[] data; // delete the array
}

Vector& Vector::operator=(const Vector& v)
{
    if (this != &v) { // Avoid self-assignment
        delete[] data; // Delete old array
        num = v.num; // Copy the size

        // Allocate new array and copy data
        data = new int[num];
        for (int i = 0; i < num; i++)
        {
            data[i] = v.data[i]; // Copy the data
        }
    }
    return *this; // Return the current object to support chained assignments
}


int main ()
{
    Vector v1(10); // create a vector of size 10
    Vector v2(v1); // create a copy of v1 (calls the copy constructor)
    Vector v3 = v1; // create a copy of v1 (calls the copy constructor)

    v2 = v1; // use the assignment operator
    return 0;
}


class Class 
{
    private: 
        int num {12};
    
    public:
        friend std::ostream& operator<<(std::ostream& out, const Class& c)
        {
            out << c.num;
            return out;
        }
};



int main ()
{
    Class c;
    std::cout <<c << std::endl;
}


friendship

class Vector 
{
    private:
        double coord[3];
        friend class Matrix; // Matrix is a friend of Vector

    public:
        
};

class Matrix
{
    private:
        double elem[3][3];
    
    public: 
        Vector multiplication(const Vector& v)
        {
            Vector result;
            for (int i =0; i<3; i++)
            {
                for (int j=0; j<3; j++)
                {
                    result.coord[i] += elem[i][j] * v.coord[j];
                }
            }
            return result;
        }
};



nested classes
class Book
{
    public:
        class Author
        {
            public:
                std::string name;
                std::string email;
        };
};


int main ()
{
    Vector v;
    Matrix m;
    Vector result = m.multiplication(v);
}