#include <iostream>
#include <list>
#include <vector>

using E = int; 

template <typename E, typename C> 
class PriorityQueue
{
    private:
        std::list<E> list;  //sorted list 
        C isLess; 

    public: 

        class Position
        {
            private:
                std::_List_iterator<E> it; 
                
            public:
                E& operator* () {return *it;}
                void operator++() {++it; }
                void operator-- () { --it;}
                bool operator !=(const Position& other) {return it != other.it;}
                bool operator ==(const Position& other) {return it == other.it;}
                Position(const std::_List_iterator<E>& it) : it(it) {}

                friend class PriorityQueue; 

        };


        Position begin() {return Position(list.begin()); }
        Position end() {return Position(list.end()); }
        int size() const {return list.size(); }
        bool empty() const  {return list.empty(); }
        const E& min() const {return list.front(); }
        Position insert (const E& element); 
        void removeMin() {list.pop_front(); }
        void remove (const Position& p); //remove a generic position 
        Position replace(const Position& p, const E& element); 


}; 

template <typename E, typename C>
PriorityQueue<E, C>::Position PriorityQueue<E, C>::insert(const E& element)
{

    auto it = list.begin(); 
    while (it != list.end() && isLess(element, *it))
        ++it; 
    
        list.insert(it, element);

    return Position(--it); 
}

template <typename E, typename C>
void PriorityQueue<E, C>::remove (const Position& p)
{
    list.erase(p.it); 
}

template <typename E, typename C>
PriorityQueue<E, C>::Position PriorityQueue<E, C>::replace(const Position& p, const E& element)
{
    list.erase(p.it); 
    return insert(element); //insert and return a position object 
}

class Comparator
{
    public:
        bool operator() (const E& first, const E& second)
        {
            return first < second; 
        }
};

int main ()
{
    PriorityQueue<int, Comparator> q; 

    std::vector<std::pair<int, PriorityQueue<int, Comparator>::Position>> vector; 

    auto pos  = q.insert(0); 
    q.insert(1); 
    q.insert(2); 
    q.insert(3); 
    q.insert(4); 
    q.insert(5); 
    q.insert(6); 
    q.insert(7); 

    for (auto it = q.begin(); it != q.end(); ++it)
        std::cout << *it << " "; 

    std::cout << "\nafter replacing pos\n"; 
    q.replace(pos, 8); 

    for (auto it = q.begin(); it != q.end(); ++it)
        std::cout << *it << " "; 


    std::cout << "\nafter removing pos\n"; 
    q.remove(pos); 

    for (auto it = q.begin(); it != q.end(); ++it)
        std::cout << *it << " "; 
}