#include <iostream>
#include <vector>
#include <string>


template <typename K, typename V, typename C> 
class OrderedMap 
{

    static constexpr int DEF_CAPACITY = 100; 

    private:
        class Entry 
        {
            private:
                K key; 
                V value; 
            
            public:
                Entry (const K& _key = K(), const V& _value = V()) : key(_key) , value(_value) {}
                const K& getKey() const {return key; }
                const V& getValue() const {return value; }
                void setValue(const V& _value) {value = _value; }
        };  

        std::vector<Entry> vector; //vector of entry
        C isLess; //comparator functor 

    public:
        class Iterator
        {
            private:    
                std::vector<Entry>::iterator it; 

            public:
                Iterator(const std::vector<Entry>::iterator& _it) : it(_it) {}

                Entry& operator* () {return *it; }
                Iterator& operator++ () {++it; return *this; }
                Iterator& operator-- () {--it; return *this; }
                bool operator== (const Iterator& other) const {return it == other.it;}
                bool operator!=(const Iterator& other) const {return it != other.it; }
                Entry* operator -> () {return &*it; }

                friend class OrderedMap; 

        }; 


        OrderedMap(int capacity = DEF_CAPACITY) {vector.reserve(capacity); } //preallocate memory without adding values to the vector  
        Iterator firstEntry(const K& key) {return vector[0]; }
        Iterator lastEntry(const K& key) {return vector[vector.size()-1]; }
        Iterator ceilingEntry(const K& key); 
        Iterator floorEntry(const K& key); 
        Iterator lowerEntry(const K& key); 
        Iterator higherEntry(const K& key);
        Iterator insert(const K& key, const V& value);  
        Iterator find(const K& key); 
     
        Iterator end()  {return Iterator(vector.end()); }
        Iterator begin()  {return Iterator(vector.begin()); }     
}; 

template <typename K, typename V, typename C> 
OrderedMap<K, V, C>::Iterator OrderedMap<K, V, C>::find(const K& key) 
{
    int low(0); 
    int high (vector.size() -1); 

    while (low <= high)
    {
        int mid = low + (high - low)/2 ; 

        const Entry& e = vector.at(mid); 

        if (e.getKey() == key)
            return Iterator(vector.begin() + mid); //return the iterator of the entry  
        
        else if (isLess(e.getKey(), key))
        {
            low = mid + 1;  
        }
        else    
            high = mid-1; 
    }

    return end(); //if no key matches return end iterator 
}

template <typename K, typename V, typename C> 
OrderedMap<K, V, C>::Iterator OrderedMap<K, V, C>::insert(const K& key, const V& value)
{
    //binary search to find the correct position 
    int low(0); 
    int high (vector.size() -1); 
    int pos = high+1; 

    while (low <= high)
    {
        int mid = low + (high - low)/2 ; 
        const Entry& e = vector.at(mid); 

        if (e.getKey() == key) //exact key found 
        {
            vector[mid].setValue(value); 
            return Iterator(vector.begin()+mid); 
        }
        
        else if (isLess(e.getKey(), key))
        {
            low = mid + 1;  
        }
        else    
        { 
            pos = mid; //potential candidate
            high = mid-1; 
        }
    }

    auto it = vector.begin() + pos; 
    vector.insert(it, Entry(key, value)); 
    return it; 
}

template <typename K, typename V, typename C> 
OrderedMap<K, V, C>::Iterator OrderedMap<K, V, C>::ceilingEntry(const K& key)
{
    int low(0); 
    int high (vector.size() -1); 
    Iterator result = end(); 

    while (low <= high)
    {
        int mid = low + (high - low)/2 ; 
        const Entry& e = vector.at(mid); 

        if (e.getKey() == key)
            return Iterator(vector.begin() + mid); //exact match found 
        
        else if (isLess(e.getKey(), key))
        {
            low = mid + 1;  
        }
        else    
        { 
            result = Iterator(vector.begin()+mid); //potential candidate
            high = mid-1; 
        }
    }

    return result; //if no key matches return end iterator return the smaller value bigger than key
}

template <typename K, typename V, typename C> 
OrderedMap<K, V, C>::Iterator OrderedMap<K, V, C>::floorEntry(const K& key)
{
    int low(0); 
    int high (vector.size()-1); 
    Iterator result = end(); 

    while (low <= high)
    {
        int mid = low + (high - low)/2 ; 
        const Entry& e = vector.at(mid); 

        if (e.getKey() == key)
            return Iterator(vector.begin() + mid); //exact match found 
        
        else if (isLess(e.getKey(), key))
        {
            result = Iterator(vector.begin()+mid); //potential candidate
            low = mid + 1;  
        }
        else    
            high = mid-1; 
    }

     

    return result; //if no key matches return end iterator return the bigger value smaller than key
}

template <typename K, typename V, typename C> 
OrderedMap<K, V, C>::Iterator OrderedMap<K, V, C>::higherEntry(const K& key)
{
    int low(0); 
    int high (vector.size() -1); 
    Iterator result = end(); 

    while (low <= high)
    {
        int mid = low + (high - low)/2 ; 
        const Entry& e = vector.at(mid); 
        
        if (isLess( key, e.getKey()))
        {
            result = Iterator(vector.begin()+mid); //potential candidate
            high = mid-1; 
        }
        else 
        { 
            low = mid + 1; 
        }
    }

    return result; //if no key matches return end iterator return the smaller value bigger than key
}

template <typename K, typename V, typename C> 
OrderedMap<K, V, C>::Iterator OrderedMap<K, V, C>::lowerEntry(const K& key)
{
    int low(0); 
    int high (vector.size()-1); 
    Iterator result = end(); 

    while (low <= high)
    {
        int mid = low + (high - low)/2 ; 
        const Entry& e = vector.at(mid); 
        
        if (isLess(e.getKey(), key))
        {
            result = Iterator(vector.begin()+mid); //potential candidate
            low = mid + 1;  
        }
        else    
            high = mid-1; 
    }

     

    return result; //if no key matches return end iterator return the bigger value smaller than key
}



template <typename K = int>
class Comparator 
{
    public:
        bool operator() (const K& first , const K& second)
        {
            return first < second; 
        }
};

int main ()
{
    OrderedMap<int, std::string, Comparator<int>> map; 

    map.insert(5, "bene"); 
    map.insert(5, "?"); 
    map.insert(4, "io"); 
    map.insert(3, "stai"); 
    map.insert(2, "come"); 
    map.insert(1, "ciao"); 

    for (auto it = map.begin(); it != map.end(); ++it)
        std::cout << it->getValue() << " "; 
    
    std::cout << "\n" ;

    
    std::cout << map.ceilingEntry(4)->getValue() << "\n"; 
    std::cout << map.lowerEntry(4)->getValue() << "\n"; 

    std::cout << map.floorEntry(4)->getValue() << "\n"; 
    std::cout << map.higherEntry(4)->getValue() << "\n"; 

    std::cout << map.find(4)->getValue() << "\n"; 
    

}