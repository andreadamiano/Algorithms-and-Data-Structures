#pragma once 
#include <list>
#include <set>
#include <memory>
#include <set>

template <typename T> 
class Partition
{
    private:
        class Position; 

        class Comparator
            {
                public:
                    bool operator() (const std::shared_ptr<Position>& a, const std::shared_ptr<Position>& b) const
                    {
                        return a->element < b->element; 
                    }
            };

        using Set = std::set<std::shared_ptr<Position>, Comparator>;
        using SetIterator = typename std::list<Set>::iterator;

        struct Position
        {
            T element;
            SetIterator set;
            Position(const T& _element) : element(_element) {}
        };

        std::list<Set> partition;


    public:
        std::shared_ptr<Position> makeSet(const T& element); 
        std::shared_ptr<Position> makeSet(const std::list<T>& elements); 
        Set& Union(Set& A, Set& B);
        Set& find(std::shared_ptr<Position> p);

}; 

template <typename T> 
std::shared_ptr<typename Partition<T>::Position> Partition<T>::makeSet(const T& element)
{
    partition.emplace_back(); // add a new empty set to the end of the container 
    auto it = std::prev(partition.end()); 
    
    //create object 
    std::shared_ptr<Position> pos = std::make_shared<Position>(element); 
    pos->set = it; 
    it->insert(pos); 
    return pos; 
}

template <typename T>
std::shared_ptr<typename Partition<T>::Position> Partition<T>::makeSet(const std::list<T>& elements)
{
    partition.emplace_back(); // add a new empty set to the end of the container 
    auto it = std::prev(partition.end()); 

    for (auto& element : elements)
    {
        //create object 
        std::shared_ptr<Position> pos = std::make_shared<Position>(element); 
        pos->set = it; 
        it->insert(pos); 
    }
    return *(it->begin()); 
}


template <typename T>
typename Partition<T>::Set& Partition<T>::Union(typename Partition<T>::Set& A, typename Partition<T>::Set& B)
{
    auto& biggerSet = (A.size() > B.size()) ? A : B;
    auto& smallerSet = (A.size() < B.size()) ? A : B;

    //this will check if the set is empty , if it is it will retunr a pointer to end 
    auto it_big = biggerSet.begin() != biggerSet.end() ? (*biggerSet.begin())->set : partition.end();

    for (auto it = smallerSet.begin(); it != smallerSet.end(); ++it)
    {
        biggerSet.insert(*it);
        (*it)->set = it_big;
    }

    //remove smaller set
    partition.erase(smallerSet.begin() != smallerSet.end() ? (*smallerSet.begin())->set : partition.end());
    return biggerSet;
}

template <typename T>
typename Partition<T>::Set& Partition<T>::find(std::shared_ptr<typename Partition<T>::Position> p)
{
    return *(p->set);
}