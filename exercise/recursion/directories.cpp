#include <iostream>
#include <string>
#include <vector>
#include <memory> //to use unique pointers 

class Directory 
{
    private:
        std::string name; //dir name 
        std::vector<std::string> files;  //files in the dir 
        std::vector<Directory *> subdirectories; //subdir


    public: 
        Directory(const std::string& name ) : name (name) {}
        ~Directory()
        {
            for (Directory* dir : subdirectories)
                delete dir; //delete subdirectory
        }

        //prevent copying 
        Directory(const Directory& directory) = delete; //tells the compiler to ignore this function 
        Directory& operator= (const Directory&) = delete; 


        void add_file(const std::string& file)
        {
            files.push_back(file);
        }

        //create an add a new subdirectory
        Directory* add_subdirectory (const std::string& dirname)
        {
            Directory* subdir = new Directory (dirname); 
            subdirectories.push_back(subdir); //append to vector list 
            return subdir; 
        }


        //display directory structure recursively
        void print (int depth =0) const 
        {
            //print first dir 
            std::string indent(depth *2, ' '); //the first argument indicate the number of time the character should be repeated 
            std::cout << indent << "dir: " << name << std::endl; 

            //print all the files in the current directory
            for (const std::string file : files)
            {
                std::cout << indent << "  file: " << file << std::endl; 
            }


            //recursive call to print all the subdir
            for (const auto* subdir : subdirectories)
            {
                subdir->print(depth +1); 
            }
        }
};

int main ()
{
    // Create root directory
    Directory root("Root");

    // Add files directly to root
    root.add_file("system.txt");
    root.add_file("README.md");

    // Add subdirectories with nested content
    Directory* docs = root.add_subdirectory("Documents");
    docs->add_file("resume.pdf");
    docs->add_file("taxes.xlsx");

    Directory* projects = root.add_subdirectory("Projects");
    projects->add_file("main.cpp");
    
    Directory* secret = projects->add_subdirectory("SecretProject");
    secret->add_file("passwords.txt");
    secret->add_file("notes.md");

    // Print the entire filesystem structure
    root.print();
}