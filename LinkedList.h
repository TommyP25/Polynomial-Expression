#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <string>

class Node;

class LinkedList
{
private:
  Node *head = NULL;
  int size = 0;
    
public:
    // Constructors
    LinkedList(){head = NULL;};
    LinkedList(Node*);
    
    // Destructor
    ~LinkedList(){delete head;};
    
    // Accessors
    Node* getHead() const {return head;}
    int getSize() const {return size;}
    
    // Mutators
    void setHead(Node* h){head = h;}

    // Sort
    void sortList();
    
    // Overload operators
    Node* operator[](int) const ;
    friend std::ostream& operator<<(std::ostream&, LinkedList& h);
    LinkedList& operator+=(Node* node);
};

#endif