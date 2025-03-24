#include <iostream>
#include <list>

template <typename E, typename C>
class PriorityQueue
{
    private:
        std::list<E> list; 
        C isLess; //comparator functor 

    public:

        class Iterator
        {
            private:
                std::_List_iterator<E> it; 
                
            public:
                E& operator* () {return *it;}
                void operator++() {++it; }
                void operator-- () { --it;}
                bool operator !=(const Iterator& other) {return it != other.it;}
                bool operator ==(const Iterator& other) {return it == other.it;}
                Iterator(const std::_List_iterator<E>& it) : it(it) {}

        };

        int size() const; 
        bool isEmpty() const; 
        void insert (const E& element) ; 
        const E& min() const; 
        void removeMin(); 
        Iterator begin() {return Iterator(list.begin());}
        Iterator end() {return Iterator(list.end());}
}; 

template <typename E, typename C>
int PriorityQueue<E,C>::size() const 
{
    return list.size(); 
}

template <typename E, typename C>
bool PriorityQueue<E,C>::isEmpty() const
{
    return list.empty(); 
} 

template <typename E, typename C>
void PriorityQueue<E,C>::insert(const E& element) 
{
    auto it = list.begin(); 
    while(it != list.end() && !isLess(element, *it))
        ++it; 

    list.insert(it, element); 
} 

template <typename E, typename C>
const E& PriorityQueue<E, C>::min() const 
{
    return list.front();
}

template <typename E, typename C>
void PriorityQueue<E, C>::removeMin() 
{
    list.pop_front(); 
}

//comparator 
template <typename E>
class Comparator
{
    public:
        bool operator() (const E& first, const E& second)
        {
            return first<second; 
        }
};

int main ()
{
    PriorityQueue<int, Comparator<int>> priority; 

    priority.insert(100);
    priority.insert(40);
    priority.insert(200);
    priority.insert(6);
    priority.insert(4);

    for (auto it = priority.begin(); it != priority.end(); ++it)
        std::cout << *it << "\n"; 
}