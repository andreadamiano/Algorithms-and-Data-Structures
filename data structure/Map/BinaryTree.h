#pragma once 

template<typename K, typename V>
struct Entry
{
    public:
        Entry(const K& _key = K{}, const V& _value = V{}) : key(_key), value(_value) {}
        const K& getKey() {return key; }
        const V& getValue() {return value; }
        void setKey(const K& _key) {key = _key; }
        void setValue(const K& _value) {key = _value; }


    private:
        K key; 
        V value; 
};

template <typename K, typename V>
class BinaryTree
{
    private:
        struct Node
        {
            Node* parent; 
            Node* left; 
            Node* right; 
            Entry<K, V> entry; 

            Node()
        }; 

        Node* root; 

    public:

        class Iterator
        {
            
        }; 

        void addRoot(); 

}; 


template <typename K, typename V>
void BinaryTree<K, V>::addRoot()
{
    root = new Node()
}