#include <iostream>
#include <vector>
#include <list>
#include <string>

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
                K& getKey() const {return key; }
                V& getValue() const {return value; }

                Entry(const K& _key = K(), const V& _value = V()) : value(_value), key(_key) {}

        };  

        //define a type aliases
        using Bucket = std::list<Entry>;
        using BucketArray = std::vector<Bucket>;
        using EntryIt = typename Bucket::iterator;
        using BucketIt = typename BucketArray::iterator;

        int n; 
        H hash; //hash comparator                                                                        
        BucketArray array; 

    public:
        class Iterator
        {
            private:
                BucketIt bit; //bucket iterator
                EntryIt eit;  //entry iterator (in case of collision)
                const BucketArray* ba; //bucket array

            public:
                Iterator(const BucketArray* _array, const BucketIt& _bit, const EntryIt& _eit = EntryIt()) : ba(_array), bit(_bit), eit(_eit) {}
                Entry& operator* () const {return * eit; } //return the element of the bucket 
                bool operator== (const Iterator& other) const; 
                Iterator& operator++() ; 
                
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

    protected:
        Iterator finder(const K& key); 
        Iterator inserter(const Iterator& it, const Entry& entry); 
        void eraser (const Iterator& it); 
        int MAD (const size_t& hash, const int& a, const int & b) {return (hash*a+b) % n;}

        static void nextEntry(Iterator& it) {++it.eit;}
        static bool endBucket(const Iterator& it) {return it.eit == it.bit->end(); }

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
HashMap<K, V, H>::Iterator& HashMap<K, V, H>::Iterator::operator++()
{
    ++eit; //next entry in the bucket 

    if (endBucket(*this))
    {
        ++bit; //next bucket 

        while (bit != ba->end() && bit->empty())
        {
            ++bit; //find non-empty bucket 

            if (bit == ba->end())
                return *this; 

            eit = bit->begin(); //initialize new entry iterator 
        } 
    }
    return *this;
}

template <typename K, typename V, typename H>
HashMap<K, V, H>::Iterator HashMap<K, V, H>::begin()
{
    if (empty())  //if the HashMap is empty 
        return end();

    BucketIt bit = array.begin(); 

    while(bit->empty())
        ++bit; //get the first non-empty bucket 

    return Iterator(this, bit, bit->begin()); 

}

template <typename K, typename V, typename H>
HashMap<K, V, H>::Iterator HashMap<K, V, H>::finder(const K& key)
{
    int index = MAD(hash(key), 31, 17); //generate hash code and convert into an index using the compressor 
}


class HashCode
{
    public:
        static constexpr size_t offset = 14695981039346656037ULL; //large prime number
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
    HashCode hash; 
    std::cout << hash("ciao come va") << "\n"; 
    std::cout << hash(1243253.34543) << "\n"; 
}