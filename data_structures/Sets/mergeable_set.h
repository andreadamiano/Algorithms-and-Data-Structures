#pragma once

#include <map>

template<typename T>
class Set
{
    private:
        std::map<T, T> map; 
        
    public:
        class Iterator
        {   
            private:
                typename std::map<T, T>::iterator it; 

            public:
                const T& operator*()const {return it->first; }
                Iterator(std::map<T, T>::iterator _it) : it(_it) {}
                Iterator operator++();
                Iterator operator--(); 
                bool operator!=(const Iterator& other) const; 
        }; 

        Set() {}
        Iterator begin() {return Iterator(map.begin()); }
        Iterator end() {return Iterator(map.end()); }

        Iterator insert(const T& element); 
        Iterator find(const T& element); 
        void erase(const T& element); 
        void Union(const Set& other); 
        void IntersectMerge (const Set& other); 
        void SubtractMerge (const Set& other); 
}; 

template <typename T>
Set<T>::Iterator Set<T>::insert(const T& element)
{
    auto it = map.find(element); 

    if (it !=map.end())
        return Iterator(it); 

    else
    {
        auto result = map.insert({element, element}); //return a std::pair (the first one is the iterator)
        return Iterator(result.first);
    }

}

template <typename T>
Set<T>::Iterator Set<T>::find(const T& element)
{
    
    if (auto it = map.find(element))
        return Iterator(it); 

    else
       return Iterator(map.end()); 
}

template <typename T>
Set<T>::Iterator Set<T>::Iterator::operator++()
{
    
    ++it; 
    return *this; 
}

template <typename T>
Set<T>::Iterator Set<T>::Iterator::operator--()
{
    
    --it; 
    return *this; 
}

template <typename T>
bool Set<T>::Iterator::operator!=(const Set<T>::Iterator& other) const
{
    return it != other.it; 
}

template <typename T>
void Set<T>::erase(const T& element)
{
    map.erase(element); 
}

template <typename T>
void Set<T>::Union(const Set& other)
{
    for (auto it = other.map.begin(); it != other.map.end(); ++it) 
    {
        map.insert({it->first, it->first});
    }
}

template <typename T>
void Set<T>::IntersectMerge(const Set& other)
{
    std::map<T, T> newMap; 
    auto it_map = map.begin(); 
    auto it_other = other.map.begin(); 

    while (it_map != map.end() && it_other != other.map.end())
    {
        if (*it_map < *it_other)
        {
            ++it_map; 
            continue;
        }

        else if (*it_map == *it_other)
        {
            newMap.insert(*it_map++);
            ++it_other;
        }

        else
        {
            ++it_other; 
            continue;
        }

    }

    map = newMap; 
    
}

template <typename T>
void Set<T>::SubtractMerge(const Set& other)
{
    auto it_map = map.begin(); 
    auto it_other = other.map.begin(); 
    std::map<T, T> newMap; 

    while (it_map != map.end() && it_other != map.end())
    {
        if (*it_map < *it_other)
        {
            newMap.insert(*it_map++); //*it_map return a std::pair
        }
        else if (*it_map++ == *it_other++)
            ;
        else
            ++it_other; 
    }
    
    map = newMap; 
}