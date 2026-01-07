#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdint>  // For uint32_t

template <typename K, typename V, typename H>
class HashMap 
{
    static constexpr int DEF_CAPACITY = 101; 

    private:

        class Entry
        {
            private:
                K key; 
                V value; 

            public:
                const K& getKey() const {return key; }
                const V& getValue() const {return value; }
                void setValue (const V& _value) {value = _value; } 

                Entry(const K& _key = K(), const V& _value = V()) : value(_value), key(_key) {}

        };  

        //define a type aliases
        using Bucket = std::list<Entry>;
        using BucketArray = std::vector<Bucket>;
        using EntryIt = typename Bucket::iterator;
        using BucketIt = typename BucketArray::iterator;

        int n; //n of entries 
        H hash; //hash comparator                                                                        
        BucketArray array; //bucket array

    public:
        class Iterator
        {
            private:
                BucketIt bit; //bucket iterator
                EntryIt eit;  //entry iterator (in case of collision)
                const BucketArray* ba; //bucket array

            public:
                Iterator(const BucketArray& _array, const BucketIt& _bit, const EntryIt& _eit = EntryIt()) : ba(&_array), bit(_bit), eit(_eit) {}
                Entry& operator* () const {return * eit; } //return the element of the bucket 
                bool operator== (const Iterator& other) const; 
                bool operator!= (const Iterator& other) const; 
                Iterator& operator++() ; 
                Entry* operator-> () {return &(*eit); }

                
                friend class HashMap; 

        }; 

        HashMap(int capacity = DEF_CAPACITY) : n(0) , array(capacity) {}
        int size() const {return n; }
        bool empty() const {return size() == 0;} 
        Iterator find(const K& key); 
        Iterator put(const K& key, const V& value); 
        void erase (const K& key); 
        void erase (const Iterator& it); 
        Iterator begin();
        Iterator end() {return Iterator(array, array.end());}

    public:
        //utility functions 
        Iterator finder(const K& key); 
        Iterator inserter(const Iterator& it, const Entry& entry); 
        void eraser (const Iterator& it); 

        //compressor
        static constexpr uint32_t MAD_a = 2654435761; // Large 32-bit prime
        static constexpr uint32_t MAD_b = 7; // Small odd number 
        int MAD (const size_t& hash) {return (hash * MAD_a + MAD_b) % array.size();} 

        static void nextEntry(Iterator& it) {++it.eit;} //get the next entry of the bucket 
        static bool endBucket(const Iterator& it) {return it.eit == it.bit->end(); } //check if the iterator is a the end of the bucket 

}; 

template <typename K, typename V, typename H>
bool HashMap<K, V, H>::Iterator::operator== (const Iterator& other) const
{
    if (ba != other.ba || bit != other.bit)
        return false; 

    else if (bit == ba->end()) //assumes ba == other.ba
        return true; 
    else 
        return eit == other.eit; 
}

template <typename K, typename V, typename H>
bool HashMap<K, V, H>::Iterator::operator!= (const Iterator& other) const
{
    return !(*this == other);
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator& HashMap<K, V, H>::Iterator::operator++()
{ 
    ++eit; //next entry in the bucket

    if (endBucket(*this))
    {
        ++bit; //next bucket 

        while (bit != ba->end() && bit->empty())
            ++bit; //find non-empty bucket 

        if (bit == ba->end())
            return *this; 

        eit = bit->begin(); //initialize new entry iterator 
    }
    
    return *this;
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::begin()
{
    if (empty())  //if the HashMap is empty 
        return end();

    BucketIt bit = array.begin(); 

    while(bit->empty())
        ++bit; //get the first non-empty bucket 

    return Iterator(array, bit, bit->begin()); 

}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::finder(const K& key)
{
    int index = MAD(hash(key)); //generate hash code and convert into an index using the compressor 
    auto bit = array.begin() + index; //get the iterator of the bucket where the entry will be inserted 

    Iterator it(array, bit, bit->begin()); //cretae iterator 

    while(!endBucket(it) && (*it).getKey() != key)
        nextEntry(it); 
    
    return it; 
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::find(const K& key)
{
    Iterator it = finder(key); 

    if(endBucket(it))
        return end(); 
    
    else 
        return it; 
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::inserter(const Iterator& it, const Entry& entry)
{
    auto eit = it.bit->insert(it.eit, entry); 
    n++; 

    return Iterator(array, it.bit, eit); 
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::put(const K& key, const V& value)
{
    auto it = finder(key); //find the entry at key position 

    if (endBucket(it))
        return inserter(it, Entry(key, value)); 
    
    else
    {    
        it.eit->setValue(value); 
        return it; 
    }

}

template <typename K, typename V, typename H>
void HashMap<K, V, H>::eraser (const Iterator& it)
{
    it.bit->erase(it.eit); 
    n--; 
}

template <typename K, typename V, typename H>
void HashMap<K, V, H>::erase (const K& key)
{
    auto it = finder(key); 

    if (endBucket(it))
        throw std::runtime_error("error: the entry doesn't exist");  
    
    else
        eraser(it); 
}

template <typename K, typename V, typename H>
void HashMap<K, V, H>::erase (const Iterator& it)
{
    eraser(it); 
}


class HashCode
{
    public:
        // #define OFFSET 14695981039346656037ULL  //alternative 
        static constexpr size_t offset = 14695981039346656037ULL; //large prime number (ULL stands for unsigned long long, 64 bit integer) (ULL is used to force the liter to be a 64 bit unsigned long long , the literal is the number used to be assigned to the type)
        static constexpr size_t alpha = 1099511628211ULL; //another large prime number 

        size_t operator() (const char* array, int len)
        { 
            size_t hash (offset);

            for (int i=0; i< len; ++i)
            {  
                hash ^= static_cast<unsigned char> (array[i]); 
                hash *= alpha;  
            }
            return hash; 
        }

        //specialization for strings
        size_t operator() (const std::string& string)
        {
            return (*this)(string.c_str(), string.length()); 
        }

        //specialization for floating point numbers 
        size_t operator() (const float& num)
        {
            // Handle -0.0 and +0.0 equality
            if (num == 0.0f) 
                return 0;

            return (*this) (reinterpret_cast<const char*> (&num),  sizeof(num)); 
        }

        size_t operator() (const double& num)
        {
            if (num == 0.0f) 
                return 0;

            return (*this) (reinterpret_cast<const char*> (&num),  sizeof(num)); 
        }

        //specialization for num
        size_t operator() (const int& num)
        {
            return (*this)(reinterpret_cast<const char*> (&num),  sizeof(num));
        }
        
        
}; 

int main ()
{
    HashMap<std::string, int, HashCode> map(101); 

    map.put("ciao", 1); 
    map.put("come", 2); 
    map.put("stai", 3); 
    map.put("?", 4); 

    std::cout << "load factor: " << 4.0/101.0 << "\n"; 
    for (auto it = map.begin(); it != map.end(); ++it)
        std::cout << "value " << it->getValue() << " index " << map.MAD(HashCode()(it->getKey())) << "\n"; 


}