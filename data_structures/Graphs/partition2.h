#pragma once 
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

template <typename T> 
class Partition
{
    private:
        struct CustomHAsh
        {
            std::hash<std::string> hasher; 

            size_t operator() (const std::string& string) const
            {
                return hasher(string);
            }
        };
        struct Position
        {
            T element; 
            std::shared_ptr<Position> set; 
            size_t size; 
            Position(const T& _element) : element(_element) {}
        };

        std::unordered_map<T, std::shared_ptr<Position>, CustomHAsh> positions; 

    public:
        bool isRoot(const std::shared_ptr<Position> p) {return p->set == p;  }
        std::shared_ptr<Position> Union(std::shared_ptr<Position> A, std::shared_ptr<Position> B);  
        std::shared_ptr<Position> find(const std::string& string); 
        std::shared_ptr<Position> find(std::shared_ptr<Position> p); 
        std::shared_ptr<Position> makeSet(const T& element); 
}; 


template< typename T>
std::shared_ptr<typename Partition<T>::Position> Partition<T>::Union(std::shared_ptr<typename Partition<T>::Position> A, std::shared_ptr<typename Partition<T>::Position> B)
{   
    auto rootA = find(A); 
    auto rootB = find(B); 

    //if they are already part of the same set 
    if (rootA == rootB)
        return rootA; 

    //ensure that the rootA points to the bigger tree 
    if (rootA->size < rootB->size) {
        std::swap(rootA, rootB);
    }

    rootB->set = rootA; 
    rootA->size += rootB->size; 

    return rootA; 
}

template<typename T>
std::shared_ptr<typename Partition<T>::Position> Partition<T>::find(const std::string& string)
{
    //get position 
    auto it = positions.find(string); 
    if (it == nullptr)
        return nullptr; 

    return find(it->second); 
}


template<typename T>
std::shared_ptr<typename Partition<T>::Position> Partition<T>::find(std::shared_ptr<Position> p)
{
    //this will flatten the tree 
    if (isRoot(p))
        return p; 

    p->set = find(p->set); 
    return p->set; 
}

template <typename T> 
std::shared_ptr<typename Partition<T>::Position> Partition<T>::makeSet(const T& element)
{
    std::shared_ptr<Position> p = std::make_shared<Position>(element); 
    p->set = p; //circular reference for the root 
    p->size = 1; 

    //save position
    positions[element] = p; 
    return p; 
}

