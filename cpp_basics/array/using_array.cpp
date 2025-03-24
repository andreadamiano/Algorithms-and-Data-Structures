#include <iostream>
#include <string>

std::string names [] {"Andrea", "Janelle", "Matteo", "Giuseppe", "Astrid", "Leonardo", "Jenny", "Jaleca", "Jessica", "Alessia"};


class Exception 
{
    public:     
        Exception(const std::string& message) : message(message) {}

        std::string getMessage() const {return message; }


    private:
        std::string message; 
};

class GameEntry
{
    public: 
        GameEntry(int score = 0, const std::string& name = "") : score(score), name(name) {}
        // GameEntry::GameEntry(const GameEntry& entry): score(entry.score), name(entry.name) {} //copy constructor 

        //accessory function to access private data 
        std::string getName() const {return name;}
        int getScore() const {return score;}

        //operator overloading
        GameEntry& operator= (const std::string& string)
        {
            if (string == "NULL")
            {
                score = 0; 
                name = ""; 
            }

            return *this; 
        }
    
    private:
        int score;
        std::string name; 
};


class Scores
{
    public:
        Scores(int maxEntries = 10);
        ~Scores();

        //accessory function to add or delete an element to the array 
        void add (const GameEntry& entry); 
        GameEntry remove(int i);

        GameEntry& operator[] (int i)
        {
            return entries[i];
        }

        int getNumEntries() {return numEntries;}
        int getmaxEntries() {return maxEntries;}

        


    private:
        int maxEntries;  //max number of entries 
        int numEntries;  //actual number of entries 
        GameEntry* entries; //array of game entries
};


Scores::Scores(int maxEntries) : maxEntries(maxEntries), numEntries (0)
{
    entries = new GameEntry[maxEntries]; //allocate a dynamic array 
}

Scores::~Scores()
{
    delete[] entries; 
}

void Scores::add (const GameEntry& entry) //add a GameEntry to the array 
{
    int newScore = entry.getScore(); 
    if (numEntries == maxEntries) //if the array is full
    {
        if(newScore <= entries[maxEntries-1].getScore()) //the array is ordered from biggest score to lowest score
            return; //entry not big enough 
    }
    else numEntries++;  //increase the number of entry 

    //add the entry in order 
    int i = numEntries-2; //start form the second to last 
    while (i >=0  && newScore > entries[i].getScore())
    {
        entries[i+1] = entries[i]; //move the old entry to the right 
        i--; 
    }

    entries[i+1] = entry; //place the new entry 

}


GameEntry Scores::remove(int i)
{
    if((i>=maxEntries) || (i<0))
        throw Exception("index out of bound"); 
    GameEntry entry = entries[i]; //save the GameEntry to remove 
    entries[i] ="NULL";

    for (int j =i+1; j<maxEntries; j++ )
    {
        entries[j-1] = entries[j]; 
    }
    numEntries--; 
    return entry; 
}

std::ostream& operator<< (std::ostream& os, GameEntry& entry)
{
    os << "Name: " << entry.getName() << " " << "Score: " << entry.getScore();
    return os; 
}


// Scores::remove(int i)
// {

// }

int main ()
{
    Scores scores (10); //define a new array of GameEntries of size 10 

    for (int i = 0; i<10; i++) //create 10 game entries 
    {
        GameEntry entry (i*2, names[i]);
        scores.add(entry); 
    }

    for (int i=0; i<10; i++)
    {
        std::cout<< scores[i] << std::endl;
    }
    std::cout << "Number of entries: " << scores.getNumEntries() << std::endl; 
    std::cout << "Max entries; " << scores.getmaxEntries() << std::endl; 


    std::cout << "Remove an entry" << std::endl; 
    try
    {
        GameEntry removedEntry = scores.remove(9);
        for (int i=0; i<10; i++)
        {
            std::cout<< scores[i] << std::endl;
        }
        std::cout << "Removed entry: " << removedEntry << std::endl; 
    }
    catch (const Exception e)
    {
        std::cout << e.getMessage() << std::endl;
    }
    std::cout << "Number of entries: " << scores.getNumEntries() << std::endl; 
    std::cout << "Max entries; " << scores.getmaxEntries() << std::endl; 
}