#include <unordered_map>

template<typename T>
class Set
{
    private:
        std ::unordered_map<T, T> hash_map;
        
    public:
        class Iterator
        {   
            private:
                typename std::unordered_map<T, T>::iterator it; 

            public:
                const T& operator*()const {return it->first; }
                Iterator(std::unordered_map<T, T>::iterator _it) : it(_it) {}
                Iterator operator++();
                Iterator operator--(); 
                bool operator!=(const Iterator& other) const; 
        }; 

        Set() {}
        Iterator begin() {return Iterator(hash_map.begin()); }
        Iterator end() {return Iterator(hash_map.end()); }

        Iterator insert(const T& element); 
        Iterator find(const T& element); 
        void erase(const T& element); 
}; 

template <typename T>
Set<T>::Iterator Set<T>::insert(const T& element)
{
    auto it = hash_map.find(element); 

    if (it !=hash_map.end())
        return Iterator(it); 

    else
    {
        auto result = hash_map.insert({element, element}); //return a std::pair (the first one is the iterator)
        return Iterator(result.first);
    }

}

template <typename T>
Set<T>::Iterator Set<T>::find(const T& element)
{
    
    if (auto it = hash_map.find(element))
        return Iterator(it); 

    else
       return Iterator(hash_map.end()); 
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
    hash_map.erase(element); 
}