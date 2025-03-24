#include <iostream>
#include "binaryTree.h"

using R = int; //generic type for the reuslts 

//base class that provides the scheleton of the algorithm 
class EulerTour
{
    protected:
        struct Result
        {
            R leftResult; 
            R rightResult; 
            R finalResult; 
        };

        const Tree* t; 

        int eulerTour (const Tree::Position p) const; //perform the euler tour
        virtual void visitLeft(const Tree::Position& p, Result& r) const {} 
        virtual void visitBelow(const Tree::Position& p, Result& r) const {} 
        virtual void visitRight(const Tree::Position& p, Result& r) const =0; 
        virtual void visitExternal(const Tree::Position& p, Result& r) const=0; 
        Result initResult() const {return Result(); } //return a Result object using the defualt constructor 
        int result(const Result& r) const {return r.finalResult;}

    
    public:
        void initialize (const Tree& tree) {t = &tree; }
        
};


int EulerTour::eulerTour(const Tree::Position p) const
{
    Result r = initResult(); 
    if(p.isExternal())
        visitExternal(p, r);

    else
    {
        visitLeft(p,r);
        r.leftResult = eulerTour(p.left()); 
        visitBelow(p,r); 
        r.rightResult = eulerTour(p.right()); 
        visitRight(p,r); 
    }

    return result(r); 
}

class EvaluateExpressione : public EulerTour
{
    protected: 
        void visitExternal(const Tree::Position& p, Result& r) const override {r.finalResult = (*p).element; }
        void visitRight(const Tree::Position& p, Result& r) const override {r.finalResult = (*p).operation(r.leftResult, r.rightResult);}

    public:
        void execute(Tree& t) 
        {
            initialize(t);
            std::cout << "Result: " << eulerTour(t.Root()) << "\n"; 
        }
}; 

class PrintExpression : public EulerTour
{
    protected:
        void visitLeft(const Tree::Position& p, Result& r) const override {std::cout <<"(";} 
        void visitBelow(const Tree::Position& p, Result& r) const override {(*p).print();} 
        void visitRight(const Tree::Position& p, Result& r) const override {std::cout << ")";} 
        void visitExternal(const Tree::Position& p, Result& r) const override {(*p).print();}
    
    public:
        void execute (Tree& t)
        {
            initialize(t);
            std::cout << "Epression: ";
            eulerTour(t.Root());
            std::cout << "\n";
        }

};

int main ()
{
    Tree tree;

    // Example: (3 + 5) * (7 - 2)
    tree.addChild(tree.Root(), '*', ROOT);
    tree.addChild(tree.Root(), '+', LEFT);
    tree.addChild(tree.Root(), '-', RIGHT);
    tree.addChild(tree.Root().left(), 3, LEFT);
    tree.addChild(tree.Root().left(), 5, RIGHT);
    tree.addChild(tree.Root().right(), 7, LEFT);
    tree.addChild(tree.Root().right(), 2, RIGHT);

    PrintExpression p;
    p.execute(tree);

    EvaluateExpressione e; 
    e.execute(tree); 

}
