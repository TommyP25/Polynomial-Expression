#include "LinkedList.h"
#include <ostream>
#include <string>

// Overload
LinkedList::LinkedList(Node *h){
   head = new Node(h->getCoef(), h->getExp());
   Node *current = head, *prev = head;
   h = h->getNext();
        
      while (h != NULL) {
         current = new Node(h->getCoef(), h->getExp());
         prev->setNext(current);
         prev = current;
         h = h->getNext();
      }
   
}

// Sort function
void LinkedList::sortList() {
    Node *sortedHead = NULL, *current = head;
    // Go through linked list
    while(current){
        Node *nextNode = current -> getNext(); 
        bool expFlag = false;
        // if head is valid, check the value of the exponent in the head
        if(sortedHead) {
            expFlag = (sortedHead -> getExp() <= current -> getExp());
        }
        // If not valid make move node to head
        if(!sortedHead || expFlag) {
            current -> setNext(sortedHead);
            sortedHead = current;
        }else{
            Node *temp = sortedHead;
            while (temp -> getNext()) {
                // Look through list to see if there is a larger node
                bool moveExpFlag = (temp -> getNext() -> getExp() <= current -> getExp());
                // If current exponent is smaller break out loop and swap
                if (moveExpFlag){
                    break;
                }
                temp = temp -> getNext();
            }
            // Swap nodes
            current -> setNext(temp -> getNext());
            temp -> setNext(current);
        }
        // Move to next node
        current = nextNode;
    }
    // Make sorted list to given Linked List
    head = sortedHead;
}

// Returns pointer to node of given list
Node* LinkedList::operator[](int index) const {
    Node* newNode = head;
    // For loop to go to node to reach desired index
    for(int i = 0; i < index && newNode; i++){
        newNode = newNode -> getNext();
    }
    return newNode;
}

// Prints out the linked list
std::ostream& operator<<(std::ostream& os, LinkedList& list){
    Node* curr = list.head;
    
    // Look at first term, if coef is negative print term with negative sign
    if(curr->getCoef() < 0){
        os << "-" << curr;
    }else{
        // Else just print term
        os << curr;
    }
    // Move onto next term
    curr = curr -> getNext();
    // While loop to go through linked list
    while(curr != nullptr){
        // add space since there is space between addition and minus sign
        os << " ";
        // If coef is neg, we subtract else add
        if(curr->getCoef() < 0){
            os << "- " << curr;
        }else{
            os << "+ " << curr;
        }
        // Move on to next term in LinkedList
        curr = curr -> getNext();
    }
    return os;
}

// Add node to end of linked list
LinkedList& LinkedList::operator+=(Node* node){
    // If linked list empty make node head
    if(head == NULL){
        head = node;
    // Else traverse to end of linked list and add node
    }else{
        Node* temp = head;
        while(temp->getNext() != NULL){
            temp = temp->getNext();
        }
        temp->setNext(node);
    }
    return *this;
}