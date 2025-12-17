#include <iostream>

template <typename E>
struct Point 
{
    E x; 
    E y; 
    Point(E x, E y) : x(x), y(y) {}

    friend std::ostream& operator<< (std::ostream& os, const Point<E>& p)
    {
        os << "x: " << p.x << " y: " << p.y << "\n";
        return os; 
    }
}; 

//comparator functor 
template <typename E>
class LeftRight
{
    public: 
        bool operator() (const Point<E>& first, const Point<E>& second) const 
        {
            return first.x < second.x; 
        }

};

//comparator 
template <typename E>
class BottomTop
{
    public: 
        bool operator() (const Point<E>& first, const Point<E>& second) const 
        {
            return first.y < second.y; 
        }

};

template <typename E, typename C>
void printSmaller(const E& first, const E& second, const C& isLess )
{
    std::cout << (isLess(first, second) ? first : second); 
}

int main()
{
    Point<int> first (1,10);
    Point<int> second (3,5);
    BottomTop<int> bottomtop;
    LeftRight<int> leftright; 

    printSmaller(first, second , bottomtop);  //no need to specify the teplate argument since they are deduced 
    printSmaller(first, second , leftright); 

}