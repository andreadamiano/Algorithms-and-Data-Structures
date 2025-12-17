#include <iostream>
#include <map>
#include <string>
#include <list>

template <typename K, typename V> 
class Map
{
    private:
        
        class Entry
        {
            private:
                K key; 
                V value;
            
            public:
                Entry(const K& _key = K(), const V& _value = V()) : key(_key), value(_value) {}
                
                const K&  getKey() const {return key; }
                const V& getValue() const {return value; }
                void setKey(const K& _key) {key = _key; }
                void setValue(const V& _value) {value = _value; }   
        }; 

        std::list<Entry> list; 


    public: 

        class Iterator
        {
            private:
                typename std::list<Entry>::iterator it;  
            
            public:
                Iterator(std::list<Entry>::iterator _it): it(_it) {}

                Entry& operator* () {return *it;} 
                Entry* operator->() {return &*it; }
                Iterator& operator++() {++it; return *this; }
                Iterator& operator--() {--it; return *this; }
                bool operator==(const Iterator& other) {return it == other.it ; }
                bool operator!=(const Iterator& other) {return it != other.it ; }

                friend class Map; 
                
        }; 

        int size() const; 
        bool empty() const;
        Iterator find(const K& key) const;
        Iterator put(const K& key, const V& value); 
        void erase(const K& key);
        void erase (const Iterator& it);  
        Iterator begin() {return Iterator(list.begin()); }
        Iterator end() {return Iterator(list.end()); } 
}; 

template <typename K, typename V>
int Map<K, V>::size() const
{
    return list.size(); 
}

template <typename K, typename V>
bool Map<K, V>::empty() const
{
    return list.empty(); 
} 

template <typename K, typename V>
Map<K, V>::Iterator Map<K, V>::find(const K& key) const 
{
    for (auto it = list.begin(); it!= list.end(); ++it)
    {
        if (it->getKey() == key)
            return Iterator(it);
    }
    return end(); 
}

template <typename K, typename V>
Map<K, V>::Iterator Map<K, V>::put(const K& key, const V& value) 
{
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        if (it->getKey() == key)
        {
            it->setValue(value); 
            return Iterator(it); 
        }
    }

    list.push_back(Entry(key, value)); 
    return Iterator(--list.end()); 
}

template <typename K, typename V>
void Map<K, V>::erase(const K& key)
{
    for (auto it = list.begin() ; it != list.end(); ++it)
    {
        if (it->getKey() == key)
        {
            list.erase(it); 
        }
    }
}

template <typename K, typename V>
void Map<K, V>::erase(const Iterator& it)
{
    list.erase(it.it); 
}

int main ()
{
    Map<int, int> map; 
    // Map<int, int>::Entry entry (10, 20); 

    map.put(10,20); 
    map.put(11,21); 
    map.put(12,22); 
    map.put(13,23); 

    auto it = map.begin(); 
    map.erase(it); 

    for (it = map.begin(); it != map.end(); ++it)
        std::cout << it->getKey() << " "; 

}

// int main ()
// {
//     std::map<std::string, int > map; 

//     map.insert({"ciao", 1}); 

//     auto it = map.find("ciao"); 
//     std::cout << "first " << it->first << "second " << it->second; 
// }