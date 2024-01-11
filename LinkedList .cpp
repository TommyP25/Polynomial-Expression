#include "LinkedList.h"
#include <ostream>
#include <string>

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

void LinkedList::reverse() {
    if (head != NULL) {
        Node *h = head;
        Node *prev = NULL, *next = NULL;
        while (h != NULL) {
            next = h->getNext();
            h->setNext(prev);
            prev = h;
            h = next;
        }
        head = prev;
    }
}

void LinkedList::sortList() {
    Node *sortedHead = NULL, *current = head;
    while (current) {
        Node *nextNode = current -> getNext(); 
        bool expFlag = false;
        if (sortedHead) {
            expFlag = (sortedHead -> getExp() >= current -> getExp());
        }
        if (!sortedHead || expFlag) {
            current -> setNext(sortedHead);
            sortedHead = current;
        } else {
            Node *temp = sortedHead;
            while (temp -> getNext()) {
                bool moveExpFlag = (temp -> getNext() -> getExp() >= current -> getExp());
                if (moveExpFlag){
                    break;
                }
                temp = temp->getNext();
            }
            current -> setNext(temp -> getNext());
            temp -> setNext(current);
        }
        current = nextNode;
    }
    head = sortedHead;
    reverse();
}

Node* LinkedList::operator[](int index) const {
    Node* newNode = head;
    for(int i = 0; i < index && newNode; i++){
        newNode = newNode -> getNext();
    }
    return newNode;
}

std::ostream& operator<<(std::ostream& os, LinkedList& list){
    Node* curr = list.head;
    if(curr->getCoef() < 0){
        os << "-" << curr;
    }else{
        os << curr;
    }
    curr = curr -> getNext();
    
    while(curr != nullptr){
        os << " ";
        if(curr->getCoef() < 0){
            os << "- " << curr;
        }else{
            os << "+ " << curr;
        }
        curr = curr -> getNext();
    }
    os << std::endl;
    return os;
}

LinkedList& LinkedList::operator+=(Node* node){
    if(head == NULL){
        head = node;
    }else{
        Node* temp = head;
        while(temp->getNext() != NULL){
            temp = temp->getNext();
        }
        temp->setNext(node);
    }
    return *this;
}