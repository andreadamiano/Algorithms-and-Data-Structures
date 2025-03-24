#include <iostream>
#include <string>

template <typename T>
class Vector
{
    public:

        //base constructor
        Vector(int capacity=10); 

        //copy construcor
        Vector (const Vector& v): capacity(v.capacity)
        {
            array = new T [capacity];

            for (int i=0; i < capacity; i++)
            {
                array[i] = v[i];
            }

        }

        //destructor
        ~Vector()
        {
            delete[] array; 
        }

        
        //operator overloading 
        T& operator[] (int i)
        {
            index = i;
            return array[i];
        }

        T& operator= (const Vector& v)
        {
            if (this != &v)
            {
                delete [] array ; //delete old array 
                capacity = v.capacity;
                array = new T [capacity];

                for (int i =0; i< capacity; i++)
                {
                    array[i] = v[i];
                }
            }
            return *this;
        }

        friend std::ostream& operator<< <T>(std::ostream& os, const Vector<T>& v); // <T> after the name function specifies to the compiler that its a template function

        int getCapacity() {return capacity;}

    private:
        T* array; 
        int capacity; 
        int index; 
}; 

template <typename T>
Vector<T>::Vector(int capacity) : capacity(capacity)
    {
        array = new T [capacity];
    }


template <typename T>
std::ostream& operator<<(std::ostream &os, const Vector<T> &v)
{
    os << v[v.index];
    // Check if the index is within bounds
    // if (index >= 0 && index < v.capacity)
    // {
    //     os << v.array[index];
    // }
    // else
    // {
    //     os << "Index out of range";
    // }

    return os;
}

int main ()
{
    Vector<int> v (3); //instance of template class 
    Vector<std::string> v2 (4);

    for (int i=0; i<3; i++)
    {
        v[i] = i;
        v2[i] = "i";
        // std::cout << v[i] << std::endl;
        // std::cout << v2[i] << std::endl;
    }

    std::cout << v[1] << std::endl;

    // std::cout << v << std::endl;


    //template arguments 
    Vector<Vector<int> > array_of_vector (2);

    std::cout << array_of_vector[0].getCapacity() << std::endl;


    //access ellement of a 2d array 
    array_of_vector[0][0] = 34;
    std::cout <<  array_of_vector[0][0] << std::endl; 
 
}