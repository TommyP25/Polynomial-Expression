#ifndef NODE_H
#define NODE_H
#include <string>

class Node
{
private:
    double coefficient;
    int exponent;
    Node *next = nullptr;
public:
    // Constructors
    Node();
    Node(double, int);
    
    // Accessors
    double getCoef() const {return coefficient;}
    int getExp() const {return exponent;}
    Node *getNext() const {return next;}
    
    // Mutators
    void setCoef(double coef){coefficient = coef;}
    void setExp(int expo){exponent = expo;}
    void setNext(Node *nex){next = nex;}
    
    // << overload operator
    friend std::ostream& operator<<(std::ostream& os, const Node* n);

};

#endif