#pragma once 

#include <iostream>
#include <string>
#include <fstream>

using namespace std; 

class Serializable 
{
    //serializable class 
    private:
        string name; 
        int age; 

    public:
        Serializable(const string& _name, int _age): name(_name) , age(_age) {}
        string getName() {return name; }
        int getAge() {return age; }

        void serialize(const string& filename); 
        void deserialize(const string& fiename); 

}; 


void Serializable::serialize(const string& filename)
{
    ofstream file(filename); 
    if (!file.is_open())
    {
        cerr << "Error: failed to open file" << endl; 
        return; 
    }

    //serialize each component one by one and add to a buffer  
    size_t nameLen = name.size();
    file.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    file.write(name.c_str(), nameLen);
    file.write(reinterpret_cast<const char*>(&age), sizeof(age));

    file.close();
    cout << "Object serialized successfully" << endl;
}


void Serializable::deserialize(const string& filename)
{
    ifstream file(filename); 
    if (!file.is_open())
    {
        cerr << "Error: failed to open file" << endl; 
        return; 
    }

    // Deserialize name length
    size_t nameLen = 0;
    file.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    if (!file) {
        cerr << "Error: failed to read name length" << endl;
        return;
    }

    // Deserialize name string
    std::string tempName(nameLen, '\0');
    //file.read() expect a pointer to a char buffer 
    file.read(&tempName[0], nameLen);
    if (!file) {
        cerr << "Error: failed to read name string" << endl;
        return;
    }
    name = tempName;

    // Deserialize age
    file.read(reinterpret_cast<char*>(&age), sizeof(age));
    if (!file) {
        cerr << "Error: failed to read age" << endl;
        return;
    }
}   

